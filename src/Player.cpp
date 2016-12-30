#include <DxLib.h>
#include <cassert>
#include "Player.hpp"
#include "Keyboard.hpp"

 
namespace
{
	constexpr float REFLECTION_RATE = 1.1f;
}


namespace DEBUG
{
	constexpr float BRAKE_POWER = 0.99f;
	constexpr float BRAKE_BRAKE = 0.9999f;
}

// Static members
int PlayerClass::s_m_num = 0;


PlayerClass::PlayerClass(const GameClass* game)
	: game(game)
	, m_img(new Image)
	, m_color(GetColor(0, 0, 0))
	, h_se_hit(LoadSoundMem("sound/reflection.mp3"))
	, m_num(0)
{
}


PlayerClass::~PlayerClass()
{
	s_m_num--;
	DeleteSoundMem(h_se_hit);
}


void PlayerClass::Initialize()
{
	s_m_num++;
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
	m_num = s_m_num;

	// Setup the color.
	switch (m_num)
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
	m_circle.cx = pos.x;
	m_circle.cy = pos.y;

	CheckOverBoundary();
	Move();

	// Players collision.
	CheckPlayersCol();

	// DEBUG -----------------------------------------------------------
	if (Keyboard::Instance()->isPush(Input::KeyCode.Return) && m_num == 1)
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
	DrawCircle(m_circle.cx, m_circle.cy, m_circle.r, m_color, FALSE);
}


const Vector2D &PlayerClass::Pos() const
{
	return pos;
}


const Circle & PlayerClass::GetHitCircle() const
{
	return m_circle;
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

void PlayerClass::CheckPlayersCol()
{
	bool isHit = false;
	Vector2D dir;

	// 1P
	if (m_num == 1)
	{
		isHit = Vector2D::CirclesCollision(m_circle.r, game->Player2()->GetHitCircle().r, pos, game->Player2()->Pos());
	}

	// 2P
	if (m_num == 2)
	{
		isHit = Vector2D::CirclesCollision(m_circle.r, game->Player()->GetHitCircle().r, pos, game->Player()->Pos());
	}

	// Reflection.
	if (isHit)
	{
		if (m_num == 1)
		{
			//double radAng = std::atan2(pos.y, game->Player2()->Pos().y);
			if (pos.y < game->Player2()->GetHitCircle().cy)
			{
				m_force = Vector2D(m_force.x, -m_force.y);
			}
			else
			{
				m_force = Vector2D(-m_force.x, m_force.y);
			}
		}
		else if (m_num == 2)
		{
			//double radAng = std::atan2(pos.y, game->Player()->Pos().y);
			if (pos.y < game->Player()->GetHitCircle().cy)
			{
				m_force = Vector2D(m_force.x, -m_force.y);
			}
			else
			{
				m_force = Vector2D(-m_force.x, m_force.y);
			}
		}
	}
}

// EOF
