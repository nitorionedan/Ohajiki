#include "Physics.hpp"
#include "Vector2D.hpp"
#include "Circle.hpp"
#include "RectClass.hpp"


bool Physics::CollisionCircleIntoRect(const Circle& circle, const Rect& rect)
{
	// Left
	if (circle.cx - circle.r < rect.left)
	{
		return true;
	}

	// Right
	if (circle.cx + circle.r > rect.right)
	{
		return true;
	}

	// Top
	if (circle.cy - circle.r < rect.top)
	{
		return true;
	}

	// Bottom
	if (circle.cy + circle.r > rect.bottom)
	{
		return true;
	}

	return false;
}
