#include <DxLib.h>
#include <cassert>
#include "Player1.hpp"
#include "Keyboard.hpp"

 
namespace
{
	constexpr float REFLECTION_RATE = 1.0f;
}


namespace DEBUG
{
	constexpr float BRAKE_POWER = 0.999f; // 0.99
	constexpr float BRAKE_BRAKE = 0.9999f;
	Circle other;
}


Player1::Player1(const GameClass* game)
	: game(game)
	, m_img(new Image)
	, m_color(GetColor(0, 0, 0))
	, h_se_hit(LoadSoundMem("sound/reflection.mp3"))
	, m_num(0)
{
}


Player1::~Player1()
{
	DeleteSoundMem(h_se_hit);
}


void Player1::Initialize()
{
	m_circle.r = 10;

	// Get players boundary.
	int l, r, t, b;
	game->Stage()->GetBorder(l, r, t, b);
	l += m_circle.r;
	r -= m_circle.r;
	t += m_circle.r;
	b -= m_circle.r;
	int borderX = r - l;
	int borderY = b - t;
	pos.SetVec(GetRand(borderX) + l, GetRand(borderY) + t);

	m_circle.cx = pos.x;
	m_circle.cy = pos.y;

	m_force = Vector2D::ZERO;
	m_brake = DEBUG::BRAKE_POWER;
	m_num = PlayerClass::s_num;

	// Setup the color.
	m_color = GetColor(255, 0, 0);

	// DEBUG ----------------------------------------------
	DEBUG::other.cx = GetRand(borderX) + l;
	DEBUG::other.cy = GetRand(borderY) + t;
	DEBUG::other.r = 10.;
}


void Player1::Update()
{
	// Sync objects.
	m_circle.cx = pos.x;
	m_circle.cy = pos.y;

	CheckOverBoundary();
	Move();

	// Collision checl.
	//CheckPlayersCol();

	// DEBUG -----------------------------------------------------------
	if (Keyboard::Instance()->isPush(Input::KeyCode.Return))
	{
		printfDx("ok");
		Vector2D tmp;
		tmp.SetVec(GetRand(100) - 50, GetRand(100) - 50);
		m_force = tmp.Normalize() * 40;
		m_brake = DEBUG::BRAKE_POWER;
		isMoving = true;
	}
}


void Player1::Draw()
{
	DrawCircle(m_circle.cx, m_circle.cy, m_circle.r, m_color, FALSE);

	// DEBUG ----------------------------------------------------------
	DrawCircle(DEBUG::other.cx, DEBUG::other.cy, DEBUG::other.r, GetColor(0, 255, 0), FALSE);
}


const Vector2D &Player1::Pos() const
{
	return pos;
}


const Circle & Player1::GetRange() const
{
	return m_circle;
}


void Player1::Move()
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


void Player1::CheckOverBoundary()
{
	const bool isHitLeft   = pos.x < game->Stage()->GetBorder().left + m_circle.r;
	const bool isHitRight  = pos.x > game->Stage()->GetBorder().right - m_circle.r;
	const bool isHitTop    = pos.y < game->Stage()->GetBorder().top + m_circle.r;
	const bool isHitBottom = pos.y > game->Stage()->GetBorder().bottom - m_circle.r;
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
		pos.x = game->Stage()->GetBorder().left + m_circle.r;
	}
	else if (isHitRight)
	{
		pos.x = game->Stage()->GetBorder().right - m_circle.r;
	}
	else if (isHitTop)
	{
		pos.y = game->Stage()->GetBorder().top + m_circle.r;
	}
	else if (isHitBottom)
	{
		pos.y = game->Stage()->GetBorder().bottom - m_circle.r;
	}

	// Add reflection rates to the force.
	m_force = m_force * REFLECTION_RATE;

	PlaySoundMem(h_se_hit, DX_PLAYTYPE_BACK);
}

void Player1::CheckPlayersCol()
{
	//bool isHit = false;
	//Vector2D dir;

	//isHit = Vector2D::CirclesCollision(m_circle.r, game->Player2()->GetRange().r, pos, game->Player2()->Pos());

	//// Reflection.
	//if (!isHit)
	//{
	//	return;
	//}

	//if (pos.y < game->Player2()->GetRange().cy)
	//{
	//	m_force = Vector2D(m_force.x, -m_force.y);
	//}
	//else
	//{
	//	m_force = Vector2D(-m_force.x, m_force.y);
	//}
}

// EOF
