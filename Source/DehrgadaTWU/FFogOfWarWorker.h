// Based on tutorial by Isvulfe  https://forums.unrealengine.com/showthread.php?55650-TUTORIAL-Fog-Of-War

#pragma once

class AFogOfWarManager;
/**
 * 
 */
class DEHRGADATWU_API FFogOfWarWorker : public FRunnable
{
	//Thread to run the FRunnable on
	FRunnableThread* Thread;

	//Pointer to our manager
	AFogOfWarManager* Manager;

	//Thread safe counter 
	FThreadSafeCounter StopTaskCounter;

public:
	FFogOfWarWorker();
	FFogOfWarWorker(AFogOfWarManager* manager);
	virtual ~FFogOfWarWorker();

	//FRunnable interface
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();

	//Method to perform work
	void UpdateFowTexture();

	bool bShouldUpdate = false;

	void ShutDown();
};
