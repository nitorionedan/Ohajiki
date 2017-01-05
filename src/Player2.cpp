#include <DxLib.h>
#include <cassert>
#include "Player2.hpp"
#include "Keyboard.hpp"


namespace
{
	constexpr float REFLECTION_RATE = 1.0f;
}


namespace DEBUG
{
	// Currently level design  //
	/****************************‘¾ŒÛ
	MIN : Force level >>> 40
	Brake power >>> 0.999f

	MAX : Force level >>> 20
	Brake power >>> 0.9f
	*****************************/

	constexpr float BRAKE_POWER = 0.999f; // 0.99
	constexpr float BRAKE_BRAKE = 0.9999f;
}


Player2::Player2(GameClass const * const game)
	: game(game)
	, m_img(new Image)
	, h_se_hit(LoadSoundMem("sound/reflection.mp3"))
	, m_num(0)
{
}


Player2::~Player2()
{
	DeleteSoundMem(h_se_hit);
}


void Player2::Initialize()
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
}


void Player2::Update()
{
	// Sync objects.
	m_circle.cx = pos.x;
	m_circle.cy = pos.y;

	Move();

	// Collision checl.
	CheckOverBoundary();
	CheckPlayersCol();
}


void Player2::Draw()
{
	DrawCircle(m_circle.cx, m_circle.cy, m_circle.r, m_color, FALSE);
}


const Vector2D &Player2::Pos() const
{
	return pos;
}


const Circle & Player2::GetRange() const
{
	return m_circle;
}


void Player2::Move()
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


void Player2::CheckOverBoundary()
{
	const bool isHitLeft = pos.x < game->Stage()->GetBorder().left + m_circle.r;
	const bool isHitRight = pos.x > game->Stage()->GetBorder().right - m_circle.r;
	const bool isHitTop = pos.y < game->Stage()->GetBorder().top + m_circle.r;
	const bool isHitBottom = pos.y > game->Stage()->GetBorder().bottom - m_circle.r;
	const bool isHit = isHitLeft || isHitRight || isHitTop || isHitBottom;

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


void Player2::CheckPlayersCol()
{

}

// EOF