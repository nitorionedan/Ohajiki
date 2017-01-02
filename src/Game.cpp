#include "Game.hpp"
#include "Player1.hpp"
#include "Player2.hpp"
#include "Keyboard.hpp"


GameClass::GameClass()
	: m_stage(new StageClass)
	, m_player(static_cast<PlayerClass*>(new Player1(this)))
	, m_player2(static_cast<PlayerClass*>(new Player2(this)))
{
	Initialize();
}


GameClass::~GameClass()
{
	PlayerClass::Finalize();
}


void GameClass::Initialize()
{
	// First: stage object.
	m_stage->Initialize();

	// Second: The other objects.
	m_player->Initialize();
	m_player2->Initialize();

	m_pauseFlag = false;
}


void GameClass::Update()
{
	// Pause switching
	if (Keyboard::Instance()->isPush(Input::KeyCode.Q))
	{
		m_pauseFlag = !m_pauseFlag;
	}

	if (!m_pauseFlag)
	{
		m_stage->Update();
		m_player->Update();
		m_player2->Update();
	}

	// DEBUG -------------------------------------------------
	if (m_pauseFlag)
	{
		DrawFormatString(320, 240, GetColor(0, 255, 0), "PAUSE");
	}
}


void GameClass::Draw()
{
	m_stage->Draw();
	m_player->Draw();
	m_player2->Draw();
}


const PlayerClass* GameClass::GetPlayer() const
{
	return m_player.get();
}


const PlayerClass* GameClass::GetPlayer2() const
{
	return m_player2.get();
}


const StageClass* GameClass::Stage() const
{
	return m_stage.get();
}

// EOF