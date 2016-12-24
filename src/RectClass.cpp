#include <DxLib.h>
#include "RectClass.hpp"


void Rect::Draw()
{
	DrawBox(left, right, top, bottom, GetColor(0, 0, 255), FALSE);
}
