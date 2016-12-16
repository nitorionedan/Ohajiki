#include <DxLib.h>
#include <memory>
#include <chrono>
#include "SceneMgr.hpp"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Initialize.
	ChangeWindowMode(TRUE);
	if (DxLib_Init() != 0)
	{
		MessageBox(nullptr, "Dxlib_Init() is failed.", "Error", MB_OK);
		return -1;
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE); //< If you change window mode, don't reset resources.

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
		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			MessageBox(nullptr, "Bye!", "Quit a game.", MB_OK);
			break;
		}

		ScreenFlip();
	}

	// Finalize.
	DxLib_End();
	return 0;
}