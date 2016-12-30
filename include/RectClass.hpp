#pragma once


class Rect
{
public:
	Rect() {}
	~Rect() {}

	void Draw();

	float left, right, top, bottom;

	Rect& operator+=(const Rect& other);
	Rect& operator-=(const Rect& other);
};