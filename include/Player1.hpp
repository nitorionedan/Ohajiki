#pragma once
#include <memory>
#include "Image.hpp"
#include "Circle.hpp"
#include "RectClass.hpp"
#include "Game.hpp"
#include "PlayerClass.hpp"


class Player1 : public PlayerClass
{
public:
	explicit Player1(const GameClass* game);
	~Player1();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual const Vector2D& Pos() const override;
	virtual const Circle& GetRange() const override;

private:
	Player1() { game = nullptr; }
	Player1(const Player1&) { game = nullptr; }

	void Move();
	void CheckOverBoundary();
	void CheckPlayersCol();

	const GameClass* game;

	std::unique_ptr<Image> m_img;
	Vector2D m_force;
	Rect m_ringBou;                   //< Boundary of ring.

	float m_brake;                    //< Force of brake.
	unsigned int m_color;             //< Players color.
	int m_num;
	int h_se_hit; //< Hit sound
	bool isMoving;
};
