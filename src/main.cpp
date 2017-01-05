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
		// FPSêßå‰Åiä»à’î≈Åj
		while (GetNowCount() - FrameStartTime < 1000 / 60) { Sleep(4); }
		FrameStartTime = GetNowCount();

		// Scene process.
		sceneMgr->Update();
		sceneMgr->Draw();

#ifdef _DEBUG
		// Quit command.
		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
		{
			SetMouseDispFlag(TRUE);
			MessageBox(GetParent(nullptr), "Thank you for playing! Bye:D", "Quit", MB_OK);
			break;
		}
#endif
		ScreenFlip();
	}

	// Shutdown.
	DxLib_End();
	return 0;
}


void Setup()
{
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE); //< If you change window mode, don't reset resources.
	SetMouseDispFlag(FALSE);
	SetWindowText("Ohajiki");
	SRand(64864);
}