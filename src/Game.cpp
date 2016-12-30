#include "Game.hpp"
#include "Player.hpp"
#include "Stage.hpp"
#include "Keyboard.hpp"


GameClass::GameClass()
	: m_stage(new StageClass)
	, m_player(new PlayerClass(this))
	, m_player2(new PlayerClass(this))
{
	Initialize();
}


GameClass::~GameClass()
{
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
	// Puse switching
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


const std::shared_ptr<PlayerClass> GameClass::Player() const
{
	return m_player;
}


const std::shared_ptr<PlayerClass> GameClass::Player2() const
{
	return m_player2;
}


const std::shared_ptr<StageClass> GameClass::Stage() const
{
	return m_stage;
}

// EOF