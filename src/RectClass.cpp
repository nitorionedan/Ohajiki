#include <DxLib.h>
#include "RectClass.hpp"


void Rect::Draw()
{
	DrawBox(left, right, top, bottom, GetColor(0, 0, 255), FALSE);
}


Rect& Rect::operator+=(const Rect & other)
{
	left   += other.left;
	right  += other.right;
	top    += other.top;
	bottom += other.bottom;
	return *this;
}


Rect& Rect::operator-=(const Rect & other)
{
	left   -= other.left;
	right  -= other.right;
	top    -= other.top;
	bottom -= other.bottom;
	return *this;
}

// EOF