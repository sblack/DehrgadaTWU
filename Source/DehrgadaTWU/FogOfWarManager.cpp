// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FogOfWarViewer.h"
#include "FogOfWarLight.h"
#include "FogOfWarManager.h"

AFogOfWarManager* AFogOfWarManager::Instance;

AFogOfWarManager::AFogOfWarManager(const FObjectInitializer &FOI) : Super(FOI) {
	PrimaryActorTick.bCanEverTick = true;
	textureRegions = new FUpdateTextureRegion2D(0, 0, 0, 0, TextureSize, TextureSize);

	//15 Gaussian samples. Sigma is 2.0.
	//CONSIDER: Calculate the kernel instead, more flexibility...
	blurKernel.Init(0.0f, blurKernelSize);
	blurKernel[0] = 0.000489f;
	blurKernel[1] = 0.002403f;
	blurKernel[2] = 0.009246f;
	blurKernel[3] = 0.02784f;
	blurKernel[4] = 0.065602f;
	blurKernel[5] = 0.120999f;
	blurKernel[6] = 0.174697f;
	blurKernel[7] = 0.197448f;
	blurKernel[8] = 0.174697f;
	blurKernel[9] = 0.120999f;
	blurKernel[10] = 0.065602f;
	blurKernel[11] = 0.02784f;
	blurKernel[12] = 0.009246f;
	blurKernel[13] = 0.002403f;
	blurKernel[14] = 0.000489f;
}

AFogOfWarManager::~AFogOfWarManager() {
	if (FowThread) {
		FowThread->ShutDown();
	}
}

void AFogOfWarManager::BeginPlay() {
	Super::BeginPlay();

	Instance = this;
	bIsDoneBlending = true;
	AFogOfWarManager::StartFOWTextureUpdate();
}

void AFogOfWarManager::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	if (FOWTexture && LastFOWTexture && bHasFOWTextureUpdate && bIsDoneBlending) {
		LastFOWTexture->UpdateResourceW();
		UpdateTextureRegions(LastFOWTexture, (int32)0, (uint32)1, textureRegions, (uint32)(4 * TextureSize), (uint32)4, (uint8*)LastFrameTextureData.GetData(), false);
		FOWTexture->UpdateResourceW();
		UpdateTextureRegions(FOWTexture, (int32)0, (uint32)1, textureRegions, (uint32)(4 * TextureSize), (uint32)4, (uint8*)TextureData.GetData(), false);
		bHasFOWTextureUpdate = false;
		bIsDoneBlending = false;
		//Trigger the blueprint update
		OnFowTextureUpdated(FOWTexture, LastFOWTexture);
	}
}

void AFogOfWarManager::StartFOWTextureUpdate() {
	if (!FOWTexture) {
		FOWTexture = UTexture2D::CreateTransient(TextureSize, TextureSize);
		LastFOWTexture = UTexture2D::CreateTransient(TextureSize, TextureSize);
		int arraySize = TextureSize * TextureSize;
		TextureData.Init(FColor(0, 0, 0, 255), arraySize);
		LastFrameTextureData.Init(FColor(0, 0, 0, 255), arraySize);
		HorizontalBlurData.Init(0, arraySize);
		UnfoggedData.Init(false, arraySize);
		StaticLightData.Init(ambientLight, arraySize);
		SightData.Init(0, arraySize);
		LightData.Init(0, arraySize);
		seenThisCycleData.Init(false, arraySize);
		FowThread = new FFogOfWarWorker(this);
	}
}

void AFogOfWarManager::OnFowTextureUpdated_Implementation(UTexture2D* currentTexture, UTexture2D* lastTexture) {
	//Handle in blueprint
}

void AFogOfWarManager::RegisterFowViewer(UFogOfWarViewer* viewer) {
	FowViewers.Add(viewer);
}

void AFogOfWarManager::RegisterFowLight(UFogOfWarLight* light) {
	FowLights.Add(light);
}

void AFogOfWarManager::UpdateStaticLight(UFogOfWarLight* light, bool add)
{
	int lightTexels = SamplesPerMeter * light->lightRadius;
	FVector position = light->GetOwner()->GetActorLocation();
	FCollisionQueryParams queryParams(FName(TEXT("FOW trace SL")), false, light->GetOwner());
	//Scan
	TArray<float> scanDistSqs;
	for (int i = 0; i < light->scanPoints.Num(); i++)
	{
		FHitResult hit;
		if (GetWorld()->LineTraceSingleByChannel(hit, position, position + light->scanPoints[i], ECC_WorldStatic, queryParams))
		{
			scanDistSqs.Add((hit.ImpactPoint - position).SizeSquared());
		}
		else
		{
			scanDistSqs.Add(light->lightRadiusSq * 100 * 100);
		}
	}

	float dividend = 100.0f / SamplesPerMeter;
	uint32 halfTextureSize = TextureSize / 2;
	int posX = (int)(position.X / dividend) + halfTextureSize;
	int posY = (int)(position.Y / dividend) + halfTextureSize;
	int size = (int)TextureSize;

	for (int y = posY - lightTexels - SamplesPerMeter; y <= posY + lightTexels + SamplesPerMeter; y++)
	{
		for (int x = posX - lightTexels - SamplesPerMeter; x <= posX + lightTexels + SamplesPerMeter; x++)
		{
			//Kernel for radial light
			if (x > 0 && x < size && y > 0 && y < size)
			{
				FVector currentWorldSpacePos = FVector(
					((x - (int)halfTextureSize)) * dividend,
					((y - (int)halfTextureSize)) * dividend,
					position.Z);

				float distSq = (currentWorldSpacePos - position).SizeSquared();
				float ang = atan2f(currentWorldSpacePos.Y - position.Y, currentWorldSpacePos.X - position.X);
				if (ang < 0) ang += PI * 2;
				float angInd = ang / light->scanAngle;
				if ((int)angInd < 0)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f <"), angInd));
					UE_LOG(LogFOW, Error, TEXT("angInd %f < 0. Setting to 0."), angInd);
					angInd = 0;
				}
				else if ((int)angInd >= scanDistSqs.Num())
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("%f >"), angInd));
					UE_LOG(LogFOW, Error, TEXT("angInd %f > array size. Setting to 0."), angInd);
					angInd = 0;
				}
				float lerpedDistSq = scanDistSqs[(int)angInd] + (scanDistSqs[((int)angInd + 1) % scanDistSqs.Num()] - scanDistSqs[(int)angInd])*(fmod(angInd, 1));
				if (distSq < lerpedDistSq)
				{
					float val = sqrtf(distSq) / (light->lightRadius * 100) * light->intensity;

					if (add)
						StaticLightData[x + y*TextureSize] = 1 - (1 - StaticLightData[x + y*TextureSize])*val;
					else
						StaticLightData[x + y*TextureSize] = 1 - (1 - StaticLightData[x + y*TextureSize]) / val;
				}
			}
		}
	}
}

bool AFogOfWarManager::GetIsBlurEnabled() {
	return bIsBlurEnabled;
}

void AFogOfWarManager::UpdateTextureRegions(UTexture2D* Texture, int32 MipIndex, uint32 NumRegions, FUpdateTextureRegion2D* Regions, uint32 SrcPitch, uint32 SrcBpp, uint8* SrcData, bool bFreeData)
{
	if (Texture && Texture->Resource)
	{
		struct FUpdateTextureRegionsData
		{
			FTexture2DResource* Texture2DResource;
			int32 MipIndex;
			uint32 NumRegions;
			FUpdateTextureRegion2D* Regions;
			uint32 SrcPitch;
			uint32 SrcBpp;
			uint8* SrcData;
		};

		FUpdateTextureRegionsData* RegionData = new FUpdateTextureRegionsData;

		RegionData->Texture2DResource = (FTexture2DResource*)Texture->Resource;
		RegionData->MipIndex = MipIndex;
		RegionData->NumRegions = NumRegions;
		RegionData->Regions = Regions;
		RegionData->SrcPitch = SrcPitch;
		RegionData->SrcBpp = SrcBpp;
		RegionData->SrcData = SrcData;

		ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(
			UpdateTextureRegionsData,
			FUpdateTextureRegionsData*, RegionData, RegionData,
			bool, bFreeData, bFreeData,
			{
				for (uint32 RegionIndex = 0; RegionIndex < RegionData->NumRegions; ++RegionIndex)
				{
					int32 CurrentFirstMip = RegionData->Texture2DResource->GetCurrentFirstMip();
					if (RegionData->MipIndex >= CurrentFirstMip)
					{
						RHIUpdateTexture2D(
							RegionData->Texture2DResource->GetTexture2DRHI(),
							RegionData->MipIndex - CurrentFirstMip,
							RegionData->Regions[RegionIndex],
							RegionData->SrcPitch,
							RegionData->SrcData
							+ RegionData->Regions[RegionIndex].SrcY * RegionData->SrcPitch
							+ RegionData->Regions[RegionIndex].SrcX * RegionData->SrcBpp
							);
					}
				}
		if (bFreeData)
		{
			FMemory::Free(RegionData->Regions);
			FMemory::Free(RegionData->SrcData);
		}
		delete RegionData;
			});
	}
}