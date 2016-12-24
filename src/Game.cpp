#include "Game.hpp"
#include "Player.hpp"
#include "Stage.hpp"


GameClass::GameClass()
	: m_stage(new StageClass)
	, m_player(new PlayerClass(this))
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
}


void GameClass::Update()
{
	m_stage->Update();
	m_player->Update();
}


void GameClass::Draw()
{
	m_stage->Draw();
	m_player->Draw();
}


const std::shared_ptr<PlayerClass> GameClass::Player() const
{
	return m_player;
}


const std::shared_ptr<StageClass> GameClass::Stage() const
{
	return m_stage;
}
