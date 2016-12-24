#include <DxLib.h>
#include <cassert>
#include "Player.hpp"
#include "Keyboard.hpp"


namespace DEBUG
{
	constexpr float BRAKE_POWER = 0.99f;
	constexpr float BRAKE_BRAKE = 0.9999f;
}

// Static members
int PlayerClass::s_m_num = 0;


PlayerClass::PlayerClass(const GameClass* game)
	: game(game)
	, m_circle(new Circle)
	, m_img(new Image)
	, m_color(GetColor(0, 0, 0))
{
	s_m_num++;
}


PlayerClass::~PlayerClass()
{
	s_m_num--;
}


void PlayerClass::Initialize()
{
	m_circle->r = 10;

	// Get players boundary.
	int l, r, t, b;
	game->Stage()->GetBorder(l, r, t, b);
	l += m_circle->r;
	r -= m_circle->r;
	t += m_circle->r;
	b -= m_circle->r;
	int borderX = r - l;
	int borderY = b - t;
	pos.SetVec(GetRand(borderX) + l, GetRand(borderY) + t);

	m_circle->cx = pos.x;
	m_circle->cy = pos.y;

	m_force = Vector2D::ZERO;
	m_brake = DEBUG::BRAKE_POWER;

	// Setup the color.
	switch (s_m_num)
	{
	case 1: m_color = GetColor(255, 0, 0);
		break;
	case 2:	m_color = GetColor(0, 0, 255);
		break;
	default: assert(!"Abnormality val.");
		break;
	}
}



void PlayerClass::Update()
{
	// Sync objects.
	m_circle->cx = pos.x;
	m_circle->cy = pos.y;

	CheckOverBoundary();
	Move();
	clsDx();
	printfDx("force = %lf", m_force.Length());

	// DEBUG -----------------------------------------------------------
	if (Keyboard::Instance()->isPush(Input::KeyCode.Return))
	{
		Vector2D tmp;
		tmp.SetVec(GetRand(100) - 50, GetRand(100) - 50);
		m_force = tmp.Normalize() * 20;
		m_brake = DEBUG::BRAKE_POWER;
		isMoving = true;
	}
}


void PlayerClass::Draw()
{
	DrawCircle(m_circle->cx, m_circle->cy, m_circle->r, m_color, FALSE);
}


const Vector2D &PlayerClass::Pos() const
{
	return pos;
}


void PlayerClass::Move()
{
	// Add force vector to local position.
	pos += m_force;

	// Braking.
	m_force.x *= m_brake;
	m_force.y *= m_brake;
	if (m_force.Length() < 0.1)
	{
		m_force = Vector2D::ZERO;
		isMoving = false;
	}

	if (isMoving)
	{
		m_brake *= DEBUG::BRAKE_BRAKE;
	}
}


void PlayerClass::CheckOverBoundary()
{
	const bool isHitLeft   = pos.x < game->Stage()->GetBorder().left + m_circle->r;
	const bool isHitRight  = pos.x > game->Stage()->GetBorder().right - m_circle->r;
	const bool isHitTop    = pos.y < game->Stage()->GetBorder().top + m_circle->r;
	const bool isHitBottom = pos.y > game->Stage()->GetBorder().bottom - m_circle->r;
	const bool isHit       = isHitLeft || isHitRight || isHitTop || isHitBottom;

	if (!isHit)
	{
		return;
	}

	// Col to vertical wall.
	if (isHitLeft || isHitRight)
	{
		m_force.x *= -1;
	}
	// Col to horizontal wall.
	if (isHitTop || isHitBottom)
	{
		m_force.y *= -1;
	}

	// Adjust player pos.
	if (isHitLeft)
	{
		pos.x = game->Stage()->GetBorder().left + m_circle->r;
	}
	else if (isHitRight)
	{
		pos.x = game->Stage()->GetBorder().right - m_circle->r;
	}
	else if (isHitTop)
	{
		pos.y = game->Stage()->GetBorder().top + m_circle->r;
	}
	else if (isHitBottom)
	{
		pos.y = game->Stage()->GetBorder().bottom - m_circle->r;
	}

	// Add reflection rates to the force.
	m_force = m_force * 1.1;
}
