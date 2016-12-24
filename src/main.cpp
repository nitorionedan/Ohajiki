#include <DxLib.h>
#include <memory>
#include <chrono>
#include "SceneMgr.hpp"


void Setup(); //< Settings.


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Initialize.
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0)
	{
		MessageBox(nullptr, "Dxlib_Init() is failed.", "Error", MB_OK);
		return -1;
	}
	Setup();

	// Objects.
	std::unique_ptr<SceneMgrClass> sceneMgr(std::make_unique<SceneMgrClass>());
	int FrameStartTime = GetNowCount();

	// Main loop.
	while (ProcessMessage() == 0 && SetDrawScreen(DX_SCREEN_BACK) == 0 && ClearDrawScreen() == 0)
	{
		// Control modulation of main loop.
		int wait = 0; //< wait time (mili sec).
		if ( (wait = GetNowCount() - FrameStartTime) < 1000 / 60) //< 60 fps
		{
			Sleep(wait);
		}
		FrameStartTime = GetNowCount();

		// Scene process.
		sceneMgr->Update();
		sceneMgr->Draw();

		// Quit command.
#ifdef _DEBUG
		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			MessageBox(nullptr, "Thank you for playing! Bye:D", "Quit", MB_OK);
			break;
		}
#endif //< #ifdef _DEBUG

		ScreenFlip();
	}

	// Finalize.
	DxLib_End();
	return 0;
}


void Setup()
{
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE); //< If you change window mode, don't reset resources.
	SetMouseDispFlag(TRUE);
	SRand(64864);
}