#include "Player2.hpp"


Player2::Player2(const GameClass * game)
	: game(game)
{
}


Player2::~Player2()
{
}


void Player2::Initialize()
{
}


void Player2::Update()
{
}


void Player2::Draw()
{
}


const Vector2D & Player2::Pos() const
{
	return pos;
}


const Circle & Player2::GetRange() const
{
	return m_circle;
}


void Player2::Move()
{
}


void Player2::CheckOverBoundary()
{
}


void Player2::CheckPlayersCol()
{
}

// EOF