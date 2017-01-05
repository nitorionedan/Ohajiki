#ifndef DEF_PLAYER2_HPP
#define DEF_PLAYER2_HPP

#include <memory>
#include "Image.hpp"
#include "RectClass.hpp"
#include "Game.hpp"
#include "PlayerClass.hpp"


class Player2 : public PlayerClass
{
public:
	explicit Player2(GameClass const * const game);
	~Player2();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual const Vector2D& Pos() const override;
	virtual const Circle& GetRange() const override;

private:
	Player2() : game(nullptr) {}
	Player2(const Player2&) : game(nullptr) {}

	void Move();
	void CheckOverBoundary();
	void CheckPlayersCol();

	const GameClass* const game;

	std::unique_ptr<Image> m_img;
	Vector2D m_force;
	Rect m_ringBou; //< Boundary of ring.

	float m_brake;        //< Force of brake.
	unsigned int m_color; //< Players color.
	int m_num;
	int h_se_hit;         //< Hit sound
	bool isMoving;
};

#endif