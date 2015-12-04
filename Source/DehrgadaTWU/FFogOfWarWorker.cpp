// Fill out your copyright notice in the Description page of Project Settings.

#include "DehrgadaTWU.h"
#include "FogOfWarManager.h"
#include "FogOfWarLight.h"
#include "FogOfWarViewer.h"
#include "FFogOfWarWorker.h"

FFogOfWarWorker::FFogOfWarWorker() {}

FFogOfWarWorker::FFogOfWarWorker(AFogOfWarManager* manager) {
	Manager = manager;
	Thread = FRunnableThread::Create(this, TEXT("FFogOfWarWorker"), 0U, TPri_BelowNormal);
}

FFogOfWarWorker::~FFogOfWarWorker() {
	delete Thread;
	Thread = NULL;
}

void FFogOfWarWorker::ShutDown() {
	Stop();
	Thread->WaitForCompletion();
}

bool FFogOfWarWorker::Init() {
	if (Manager) {
		Manager->GetWorld()->GetFirstPlayerController()->ClientMessage("Fog of War worker thread started");
		return true;
	}
	return false;
}

uint32 FFogOfWarWorker::Run() {
	FPlatformProcess::Sleep(0.03f);
	while (StopTaskCounter.GetValue() == 0) {
		float time;
		if (Manager && Manager->GetWorld()) {
			time = Manager->GetWorld()->TimeSeconds;
		}
		if (!Manager->bHasFOWTextureUpdate) {
			UpdateFowTexture();
			if (Manager && Manager->GetWorld()) {
				Manager->fowUpdateTime = Manager->GetWorld()->TimeSince(time);
			}
		}
		FPlatformProcess::Sleep(0.05f);
	}
	return 0;
}

void FFogOfWarWorker::UpdateFowTexture() {
	Manager->LastFrameTextureData = TArray<FColor>(Manager->TextureData);
	uint32 halfTextureSize = Manager->TextureSize / 2;
	int signedSize = (int)Manager->TextureSize; //For convenience....
	TArray<int> currentlyInSight;
	TSet<FVector2D> texelsToBlur;
	int sightTexels;
	float dividend = 100.0f / Manager->SamplesPerMeter;
	uint8 partialFogByte = Manager->partialFog * 255;

	if (Manager->ambientLight != 1)
	{
		for (auto Itr(Manager->FowLights.CreateIterator()); Itr; Itr++) {
			//Find actor position
			if (!*Itr) return;
			FVector position = (*Itr)->GetOwner()->GetActorLocation();
			sightTexels = (*Itr)->lightRadius * Manager->SamplesPerMeter;

			//We divide by 100.0 because 1 texel equals 1 meter of visibility-data.
			int posX = (int)(position.X / dividend) + halfTextureSize;
			int posY = (int)(position.Y / dividend) + halfTextureSize;

			FVector2D textureSpacePos = FVector2D(posX, posY);
			int size = (int)Manager->TextureSize;

			FCollisionQueryParams queryParams(FName(TEXT("FOW trace")), false, (*Itr)->GetOwner());
			int halfKernelSize = (Manager->blurKernelSize - 1) / 2;

			if (Manager->GetIsBlurEnabled())
			{
				//Store the positions we want to blur
				for (int y = posY - sightTexels - halfKernelSize; y <= posY + sightTexels + halfKernelSize; y++) {
					for (int x = posX - sightTexels - halfKernelSize; x <= posX + sightTexels + halfKernelSize; x++) {
						if (x > 0 && x < size && y > 0 && y < size) {
							texelsToBlur.Add(FIntPoint(x, y));
						}
					}
				}
			}

			//Scan
			TArray<float> scanDistSqs;
			for (int i = 0; i < (*Itr)->scanPoints.Num(); i++)
			{
				FHitResult hit;
				if (Manager->GetWorld()->LineTraceSingleByChannel(hit, position, position + (*Itr)->scanPoints[i], ECC_WorldStatic, queryParams))
				{
					scanDistSqs.Add((hit.ImpactPoint - position).SizeSquared());
				}
				else
				{
					scanDistSqs.Add((*Itr)->lightRadiusSq * 100 * 100);
				}
			}


			//Unveil the positions our actors are currently looking at
			for (int y = posY - sightTexels - Manager->SamplesPerMeter; y <= posY + sightTexels + Manager->SamplesPerMeter; y++)
			{
				for (int x = posX - sightTexels - Manager->SamplesPerMeter; x <= posX + sightTexels + Manager->SamplesPerMeter; x++)
				{
					//Kernel for radial sight
					if (x > 0 && x < size && y > 0 && y < size)
					{
						FVector currentWorldSpacePos = FVector(
							((x - (int)halfTextureSize)) * dividend,
							((y - (int)halfTextureSize)) * dividend,
							position.Z);

						int index = x + y*Manager->TextureSize;

						float distSq = (currentWorldSpacePos - position).SizeSquared();
						float ang = atan2f(currentWorldSpacePos.Y - position.Y, currentWorldSpacePos.X - position.X);
						if ((*Itr)->angle != 360)
						{
							float diff = fabs(ang * 180 / PI - (*Itr)->GetOwner()->GetActorRotation().Yaw);
							if (diff > 180) diff = 360 - diff;
							if (diff > (*Itr)->angle / 2)
							{
								if (!Manager->seenThisCycleData[index])
								{
									Manager->seenThisCycleData[index] = true;
									currentlyInSight.Add(index);
									Manager->SightData[index] = 0;
									Manager->LightData[index] = Manager->StaticLightData[index];
								}
								continue;
							}
						}
						if (ang < 0) ang += PI * 2;
						float angInd = ang / (*Itr)->scanAngle;
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
							float val = (*Itr)->intensity * (1 - sqrtf(distSq) / ((*Itr)->lightRadius * 100));

							if (!Manager->seenThisCycleData[index])
							{
								Manager->seenThisCycleData[index] = true;
								currentlyInSight.Add(index);
								Manager->SightData[index] = 0;
								Manager->LightData[index] = 1 - (1 - Manager->StaticLightData[index]) * (1 - val);
							}
							else
							{

								Manager->LightData[index] = 1 - (1 - Manager->LightData[index]) * (1 - val);
							}
						}
						else
						{
							if (!Manager->seenThisCycleData[index])
							{
								Manager->seenThisCycleData[index] = true;
								currentlyInSight.Add(index);
								Manager->SightData[index] = 0;
								Manager->LightData[index] = Manager->StaticLightData[index];
							}
						}
					}
				}
			}
		}
	}

	for (auto Itr(Manager->FowViewers.CreateIterator()); Itr; Itr++) {
		//Find actor position
		if (!*Itr) return;
		FVector position = (*Itr)->GetOwner()->GetActorLocation();
		sightTexels = (*Itr)->sightRadius * Manager->SamplesPerMeter;

		//We divide by 100.0 because 1 texel equals 1 meter of visibility-data.
		int posX = (int)(position.X / dividend) + halfTextureSize;
		int posY = (int)(position.Y / dividend) + halfTextureSize;
		//float integerX, integerY;

		//FVector2D fractions = FVector2D(modf(position.X / 50.0f, &integerX), modf(position.Y / 50.0f, &integerY));
		FVector2D textureSpacePos = FVector2D(posX, posY);
		int size = (int)Manager->TextureSize;

		FCollisionQueryParams queryParams(FName(TEXT("FOW trace")), false, (*Itr)->GetOwner());
		int halfKernelSize = (Manager->blurKernelSize - 1) / 2;

		if (Manager->GetIsBlurEnabled())
		{
			//Store the positions we want to blur
			for (int y = posY - sightTexels - halfKernelSize; y <= posY + sightTexels + halfKernelSize; y++) {
				for (int x = posX - sightTexels - halfKernelSize; x <= posX + sightTexels + halfKernelSize; x++) {
					if (x > 0 && x < size && y > 0 && y < size) {
						texelsToBlur.Add(FIntPoint(x, y));
					}
				}
			}
		}

		//Scan
		TArray<float> scanDistSqs;
		for (int i = 0; i < (*Itr)->scanPoints.Num(); i++)
		{
			FHitResult hit;
			if (Manager->GetWorld()->LineTraceSingleByChannel(hit, position, position + (*Itr)->scanPoints[i], ECC_WorldStatic, queryParams))
			{
				scanDistSqs.Add((hit.ImpactPoint - position).SizeSquared());
			}
			else
			{
				scanDistSqs.Add((*Itr)->sightRadiusSq * 100 * 100);
			}
		}


		//Unveil the positions our actors are currently looking at
		for (int y = posY - sightTexels - Manager->SamplesPerMeter; y <= posY + sightTexels + Manager->SamplesPerMeter; y++)
		{
			for (int x = posX - sightTexels - Manager->SamplesPerMeter; x <= posX + sightTexels + Manager->SamplesPerMeter; x++)
			{
				//Kernel for radial sight
				if (x > 0 && x < size && y > 0 && y < size)
				{
					FVector currentWorldSpacePos = FVector(
						((x - (int)halfTextureSize)) * dividend,
						((y - (int)halfTextureSize)) * dividend,
						position.Z);

					int index = x + y*Manager->TextureSize;

					float distSq = (currentWorldSpacePos - position).SizeSquared();
					float ang = atan2f(currentWorldSpacePos.Y - position.Y, currentWorldSpacePos.X - position.X);
					if (ang < 0) ang += PI * 2;
					float angInd = ang / (*Itr)->scanAngle;
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
					if (distSq < 100 * 100)
					{
						if (!Manager->seenThisCycleData[index])
						{
							Manager->seenThisCycleData[index] = true;
							currentlyInSight.Add(index);
						}

						Manager->SightData[index] = 2;

						Manager->UnfoggedData[index] = true;
					}
					else if (distSq < lerpedDistSq)
					{
						if (!Manager->seenThisCycleData[index])
						{
							Manager->seenThisCycleData[index] = true;
							currentlyInSight.Add(index);
							Manager->SightData[index] = 0;
							Manager->LightData[index] = Manager->StaticLightData[index];
						}

						float val = 1 - sqrtf(distSq) / ((*Itr)->sightRadius * 100);
						if ((*Itr)->bLowLightVision)
						{
							float effLight = Manager->LightData[index] + .5f;
							if (effLight > 1) effLight = 1;
							val *= effLight;
						}
						else
							val *= Manager->LightData[index];

						if (val < Manager->partialFog)
						{
							continue;
						}

						if (val > Manager->SightData[index])
						{
							Manager->SightData[index] = val;
						}

						Manager->UnfoggedData[index] = true;
					}
					else
					{
						if (!Manager->seenThisCycleData[index])
						{
							Manager->seenThisCycleData[index] = true;
							currentlyInSight.Add(index);
							Manager->SightData[index] = 0;
							Manager->LightData[index] = Manager->StaticLightData[index];
						}
					}
				}
			}
		}
	}

	if (Manager->GetIsBlurEnabled()) {
		//Horizontal blur pass
		int offset = floorf(Manager->blurKernelSize / 2.0f);
		for (auto Itr(texelsToBlur.CreateIterator()); Itr; ++Itr) {
			int x = (Itr)->IntPoint().X;
			int y = (Itr)->IntPoint().Y;
			float sum = 0;
			for (int i = 0; i < Manager->blurKernelSize; i++) {
				int shiftedIndex = i - offset;
				if (x + shiftedIndex >= 0 && x + shiftedIndex <= signedSize - 1) {
					if (Manager->UnfoggedData[x + shiftedIndex + (y * signedSize)]) {
						if (Manager->SightData[x + shiftedIndex + (y * signedSize)] == 2)
						{
							sum += (Manager->blurKernel[i] * 255);
						}
						else
						{
							sum += (Manager->blurKernel[i] * (Manager->SightData[x + shiftedIndex + (y * signedSize)] * (255 - partialFogByte) + partialFogByte));
						}
					}
				}
			}
			Manager->HorizontalBlurData[x + y * signedSize] = (uint8)sum;
		}


		//Vertical blur pass
		for (auto Itr(texelsToBlur.CreateIterator()); Itr; ++Itr) {
			int x = (Itr)->IntPoint().X;
			int y = (Itr)->IntPoint().Y;
			float sum = 0;
			for (int i = 0; i < Manager->blurKernelSize; i++) {
				int shiftedIndex = i - offset;
				if (y + shiftedIndex >= 0 && y + shiftedIndex <= signedSize - 1) {
					sum += (Manager->blurKernel[i] * Manager->HorizontalBlurData[x + (y + shiftedIndex) * signedSize]);
				}
			}
			Manager->TextureData[x + y * signedSize] = FColor((uint8)sum, (uint8)sum, (uint8)sum, 255);
		}
	}
	else {
		for (int y = 0; y < signedSize; y++) {
			for (int x = 0; x < signedSize; x++) {

				if (Manager->UnfoggedData[x + (y * signedSize)]) {
					if (Manager->SightData[x + y * signedSize] == 2)
					{
						Manager->TextureData[x + y * signedSize] = FColor(255, 255, 255, 255);
					}
					else
					{
						uint8 val = (Manager->SightData[x + y * signedSize] * (255 - partialFogByte) + partialFogByte);
						Manager->TextureData[x + y * signedSize] = FColor(val, val, val, 255);
					}
				}
			}
		}
	}

	for (int i = 0; i < currentlyInSight.Num(); i++)
	{
		Manager->seenThisCycleData[currentlyInSight[i]] = false;
	}

	Manager->bHasFOWTextureUpdate = true;
}

void FFogOfWarWorker::Stop() {
	StopTaskCounter.Increment();
}
