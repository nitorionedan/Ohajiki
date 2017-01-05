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
	// Currently level design  //
	/****************************
	MIN : Force level >>> 40
	      Brake power >>> 0.999f

	MAX : Force level >>> 20
	      Brake power >>> 0.9f
	*****************************/
	constexpr float FORCE_LEVEL = 20.0f;
	constexpr float BRAKE_POWER = 0.99f;
	constexpr float BRAKE_BRAKE = 0.9999f;
}


Player1::Player1(GameClass const * const game)
	: game(game)
	, m_img(new Image)
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
}


void Player1::Update()
{
	// Sync objects.
	m_circle.cx = pos.x;
	m_circle.cy = pos.y;

	Move();

	// Collision check.
	CheckOverBoundary();
	CheckPlayersCol();

	// DEBUG -----------------------------------------------------------
	int Mouse = GetMouseInput();
	if (Mouse & MOUSE_INPUT_LEFT)
	{
		int mouse_x, mouse_y;
		GetMousePoint(&mouse_x, &mouse_y);
		Vector2D tmp = Vector2D(pos.x - mouse_x, pos.y - mouse_y);
		m_force = tmp.Normalize() * DEBUG::FORCE_LEVEL;
		m_brake = DEBUG::BRAKE_POWER;
		isMoving = true;
	}
}


void Player1::Draw()
{
	DrawCircle(m_circle.cx, m_circle.cy, m_circle.r, m_color, FALSE);
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

	// If don't collide anybody, return here.
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
	bool isHit = Vector2D::CirclesCollision(m_circle.r, game->GetPlayer2()->GetRange().r,
		pos, game->GetPlayer2()->Pos());

	// If it no collision, return here.
	if (!isHit)
	{
		return;
	}

	GameClass::Pause();

	// Separate player1 from player2.
	Vector2D dis = Vector2D(game->GetPlayer2()->Pos().x - pos.x, game->GetPlayer2()->Pos().y - pos.y);
	Vector2D unit = Vector2D(dis.Normalize().x, dis.Normalize().y);
	double dir = dis.ToRad();
	double offset = m_circle.r - game->GetPlayer2()->GetRange().r;
	pos.x += unit.x * std::cos(dir) * offset;
	pos.y += unit.y * std::sin(dir) * offset;

	// Calc reflection.
	if (pos.y < game->GetPlayer2()->GetRange().cy)
	{
		m_force = Vector2D(m_force.x, -m_force.y);
	}
	else
	{
		m_force = Vector2D(-m_force.x, m_force.y);
	}
}

// EOF