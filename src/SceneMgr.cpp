#include <DxLib.h>

#include "SceneMgr.hpp"
#include "Keyboard.hpp"


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
	Keyboard::Instance()->Update();

	m_game->Update();
}


void SceneMgrClass::Draw()
{
	m_game->Draw();
}