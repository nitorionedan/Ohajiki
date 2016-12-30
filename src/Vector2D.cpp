/*
@brief  Define of Vector2D.hpp
@author Shohei
*/
#include "Vector2D.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <DxLib.h>

#undef min
#undef max

Vector2D const Vector2D::ZERO(0., 0.);
Vector2D const Vector2D::LEFT(-1., 0.);
Vector2D const Vector2D::RIGHT(1., 0.);
Vector2D const Vector2D::UP(0., 1);
Vector2D const Vector2D::DOWN(0., -1);


Vector2D::Vector2D(double x, double y)
{
	this->x = x;
	this->y = y;
}


void Vector2D::SetVec(double x, double y)
{
	this->x = x;
	this->y = y;
}


void Vector2D::SetZero() {
	x = y = 0.;
}


void Vector2D::Fill(double XY)
{
	x = y = XY;
}


void Vector2D::BorderStop(double* pos, const double MIN, const double MAX)
{
	assert(MAX > MIN && "Vector2D::BorderStop()");
	*pos = std::min(MAX, std::max(MIN, *pos));
}


void Vector2D::AddVecAngele(double * PosX, double * PosY, const double& angle, const double& force)
{
	*PosX += std::cos(angle) * force;
	*PosY += std::sin(angle) * force;
}


bool Vector2D::CirclePointCollision(const double& MyX, const double& MyY, const double& TarX, const double& TarY, const double& Radius)
{
	const double& WIDTH = (TarX - MyX) * (TarX - MyX);
	const double& HEIGHT = (TarY - MyY) * (TarY - MyY);
	const double& DISTANCE = (WIDTH + HEIGHT);
	const double& RADIUS = Radius * Radius;
	return (RADIUS >= DISTANCE);
}


bool Vector2D::CirclePointCollision(const Vector2D & MyPos, const Vector2D & OtherPos, const double & Range)
{
	const double& WIDTH = (OtherPos.x - MyPos.x) * (OtherPos.x - MyPos.x);
	const double& HEIGHT = (OtherPos.y - MyPos.y) * (OtherPos.y - MyPos.y);
	const double& DISTANCE = (WIDTH + HEIGHT);
	const double& RADIUS = Range * Range;
	return (RADIUS >= DISTANCE);
}


bool Vector2D::CirclesCollision(const double & Range1, const double & Range2, const double & X1, const double & Y1, const double & X2, const double & Y2)
{
	const double& hLengrth = (Range1 + Range2);
	const double& xLength = (X1 - X2);
	const double& yLength = (Y1 - Y2);
	return (hLengrth * hLengrth >= xLength * xLength + yLength * yLength);
}


bool Vector2D::CirclesCollision(const double & Range1, const double & Range2, const Vector2D & Pos1, const Vector2D & Pos2)
{
	const double& hLen = (Range1 + Range2);
	const Vector2D Len = Vector2D::GetVec2(Pos1, Pos2);
	return (hLen * hLen >= std::pow(Len.x, 2) + std::pow(Len.y, 2));
}


bool Vector2D::RectanglePointCollision(const double & MyX, const double & MyY, const double & Width, const double & Height, const double & TarX, const double & TarY)
{
	const double& MyX2 = (MyX + Width);
	const double& MyY2 = (MyY + Height);
	return (MyX <= TarX && TarX <= MyX2 && MyY <= TarY && TarY <= MyY2);
}


Vector2D Vector2D::GetVec(double x, double y)
{
	return  Vector2D(x, y);
}


Vector2D & Vector2D::GetVec2(const Vector2D & vec1, const Vector2D & vec2)
{
	Vector2D vec(vec2.x - vec1.x, vec2.y - vec1.y);
	return vec;
}


const Vector2D & Vector2D::Normalize() const
{
	const double& len = Length();
	if (len < DBL_EPSILON)
		return Vector2D::ZERO;
	return *this / len;
}


const double Vector2D::Length() const {
	return std::sqrt(DotProduct(*this));
}


const double Vector2D::ToRad() const {
	return this->ToAngle() * DX_PI / 180;
}


const double Vector2D::ToAngle() const
{
	double angle = std::acos(x / std::sqrt(x * x + y * y));
	angle *= 180 / DX_PI;
	if (y < 0) angle = 360 - angle;
	return angle;

	/* Is this correct? Unfortunately, I don't know... */
	//return std::atan2(x, y) * 180 / DX_PI;
}


double Vector2D::Distance(const Vector2D & other) const
{
	return (*this - other).Length();
}


double Vector2D::DotProduct(const Vector2D & other) const
{
	return (x * other.x) + (y * other.y);
}


double Vector2D::CrossProduct(const Vector2D & other) const
{
	return (x * other.y) - (y * other.x);
}


Vector2D & Vector2D::operator=(const Vector2D & obj)
{
	x = obj.x;
	y = obj.y;
	return *this;
}


Vector2D & Vector2D::operator+=(const Vector2D & other)
{
	x += other.x;
	y += other.y;
	return *this;
}


Vector2D & Vector2D::operator-=(const Vector2D & obj)
{
	this->x -= obj.x;
	this->y -= obj.y;
	return *this;
}


Vector2D & Vector2D::operator*=(const Vector2D & obj)
{
	this->x *= obj.x;
	this->y *= obj.y;
	return *this;
}


Vector2D & Vector2D::operator/=(const Vector2D & obj)
{
	this->x /= obj.x;
	this->y /= obj.y;
	return *this;
}


const Vector2D Vector2D::operator+() const
{
	return *this;
}


const Vector2D Vector2D::operator+(const double & scalar) const
{
	return Vector2D(scalar + x, scalar + y);
}


const Vector2D Vector2D::operator+(const Vector2D & other) const
{
	return Vector2D(x + other.x, y + other.y);
}


const Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}


const Vector2D Vector2D::operator-(const double & scalar) const
{
	return Vector2D(x - scalar, y - scalar);
}


const Vector2D Vector2D::operator-(const Vector2D & other) const
{
	return Vector2D(x - other.x, y - other.y);
}


const Vector2D Vector2D::operator*(const double & scalar) const
{
	return Vector2D(scalar * x, scalar * y);
}


const Vector2D Vector2D::operator/(const double & scalar) const
{
	assert(scalar != 0);
	return Vector2D(x / scalar, y / scalar);
}


bool Vector2D::operator==(const Vector2D & other) const
{
	return (x == other.x) && (y == other.y);
}


bool Vector2D::operator!=(const Vector2D & other) const
{
	return !(*this == other);
}


bool Vector2D::operator<(const Vector2D & other) const
{
	if (x < other.x)	return true;
	if (y < other.y)	return true;
	return false;
}


bool Vector2D::operator>(const Vector2D & other) const
{
	if (x > other.x)	return true;
	if (y > other.y)	return true;
	return false;
}

// EOF