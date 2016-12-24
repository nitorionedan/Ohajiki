#include <DxLib.h>
#include "Line.hpp"


void LineClass::Draw()
{
	DrawLine(sx, sy, ex, ey, GetColor(0, 0, 255));
}
