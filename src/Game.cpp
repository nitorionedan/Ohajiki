#include "Game.hpp"
#include "Player.hpp"
#include "Stage.hpp"


GameClass::GameClass()
	: m_player(new PlayerClass)
	, m_stage(new StageClass)
{
	Initialize();
}


GameClass::~GameClass()
{
}


void GameClass::Initialize()
{
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
