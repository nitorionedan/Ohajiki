#include "SceneMgr.hpp"
#include <DxLib.h>


SceneMgrClass::SceneMgrClass()
	: m_game(new GameClass)
{
	Initialize();
}


SceneMgrClass::~SceneMgrClass()
{
	delete m_game;
}


void SceneMgrClass::Initialize()
{
}


void SceneMgrClass::Update()
{
	m_game->Update();
}


void SceneMgrClass::Draw()
{
	m_game->Draw();
}