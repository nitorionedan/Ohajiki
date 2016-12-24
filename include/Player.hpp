#pragma once

#include <memory>
#include "Object.hpp"
#include "Image.hpp"
#include "Circle.hpp"
#include "Visitor.hpp"
#include "Game.hpp"


class PlayerClass final : public Object
{
public:
	PlayerClass(const GameClass* game);
	~PlayerClass();

	void Initialize();
	void Update();
	void Draw();

	const Vector2D& Pos() const; //< Get player position.

private:
	PlayerClass() {}

	void Move();
	void CheckOverBoundary();

	const GameClass* game;

	static int s_m_num;               //< Num of players.

	std::unique_ptr<Circle> m_circle; //< Circle object;
	std::unique_ptr<Image> m_img;
	Vector2D m_force;
	Rect m_ringBou;                   //< Boundary of ring.

	float m_brake;                    //< Force of brake.
	unsigned int m_color;             //< Players color.
	bool isMoving;
};
