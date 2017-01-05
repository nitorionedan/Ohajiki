#include <DxLib.h>
#include "Mouse.hpp"


MouseClass::MouseClass()
	: gh_mouse(LoadGraph("img/game_mouse_0.png"))
{
	Initialize();
}


MouseClass::~MouseClass()
{
	DeleteGraph(gh_mouse);
}


void MouseClass::Initialize()
{
	pos.x = 0;
	pos.y = 0;
}


void MouseClass::Update()
{
	GetMousePoint(&pos.x, &pos.y);
}


void MouseClass::Draw()
{
	DrawCircle(pos.x, pos.y, 2, GetColor(255, 0, 0), TRUE);
	DrawRotaGraph(pos.x + 7, pos.y + 12, 1.0, 0.0, gh_mouse, true);
}

// EOF