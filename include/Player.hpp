#pragma once

#include <memory>
#include "Object.hpp"
#include "Image.hpp"
#include "Circle.hpp"
#include "Visitor.hpp"
#include "Game.hpp"


// ※PlayerClassという抽象クラスを用意すること。
class PlayerClass final : public Object
{
public:
	PlayerClass(const GameClass* game);
	~PlayerClass();

	void Initialize();
	void Update();
	void Draw();

	const Vector2D& Pos() const; //< Get position.
	const Circle& GetHitCircle() const; //< Get hit circle.

private:
	PlayerClass() {}

	void Move();
	void CheckOverBoundary();
	void CheckPlayersCol();

	const GameClass* game;

	static int s_m_num;               //< Num of players.

	std::unique_ptr<Image> m_img;
	Vector2D m_force;
	Circle m_circle;
	Rect m_ringBou;                   //< Boundary of ring.

	float m_brake;                    //< Force of brake.
	unsigned int m_color;             //< Players color.
	int m_num;
	int h_se_hit; //< Hit sound
	bool isMoving;
};
