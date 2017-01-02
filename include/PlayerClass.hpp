#pragma once
#include "Vector2D.hpp"
#include "Circle.hpp"


class PlayerClass
{
public:
	PlayerClass();
	virtual ~PlayerClass() {}

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual const Vector2D& Pos() const = 0;
	virtual const Circle& GetRange() const = 0;

	static void Finalize();

protected:
	static int s_num;
	Vector2D pos;
	Circle m_circle;
};