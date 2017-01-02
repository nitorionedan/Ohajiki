#pragma once


// Using classes.
class Vector2D;
class Circle;
class Rect;


namespace Physics
{
	bool CollisionCircleIntoRect(const Circle& circle, const Rect& rect);
}