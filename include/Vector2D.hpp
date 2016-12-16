#pragma once

class Vector2D
{
public:
	explicit Vector2D(double x, double y);
	Vector2D() {}

	void SetVec(const double& x, const double& y) {
		this->x = x;
		this->y = y;
	}
	void SetZero();
	void Fill(const double& XY) {
		x = y = XY;
	}

	static void BorderStop(double* pos, const double MIN, const double MAX);
	static void AddVecAngele(double* PosX, double* PosY, const double& angle, const double& force);
	static bool CirclePointCollision(const double& MyX, const double& MyY, const double& TarX, const double& TarY, const double& Radius);
	static bool CirclePointCollision(const Vector2D& MyPos, const Vector2D& OtherPos, const double& Range);
	static bool CirclesCollision(const double& Range1, const double& Range2,
		const double& X1, const double& Y1, const double& X2, const double& Y2);
	static bool CirclesCollision(const double& Range1, const double& Range2,
		const Vector2D& Pos1, const Vector2D& Pos2);
	static bool RectanglePointCollision(const double& MyX, const double& MyY, const double& Width, const double& Height, const double& TarX, const double& TarY);

	// @brief				ベクトルを生成
	// @param[in]	x, y	座標
	// @return				生成したベクトル
	static Vector2D GetVec(double x, double y) {
		return  Vector2D(x, y);
	}

	// @brief				自分→相手のベクトルを生成
	// @param[in]	vec1	自分
	// @param[in]	vec2	相手
	// @return				生成したベクトル
	static Vector2D& GetVec2(const Vector2D& vec1, const Vector2D& vec2) {
		Vector2D vec(vec2.x - vec1.x, vec2.y - vec1.y);
		return vec;
	}

	const Vector2D& Normalize() const;
	const double Length() const;
	const double ToRad() const;
	const double ToAngle() const;

	const double Distance(const Vector2D& other) const {
		return (*this - other).Length();
	}

	// @brief				内積を計算
	// @param[in]	other	相手のベクトル
	// @return				内積
	const double DotProduct(const Vector2D& other) const {
		return (x * other.x) + (y * other.y);
	}

	// @brief				外積を計算
	// @param[in]	other	相手のベクトル
	// @return				外積
	const double CrossProduct(const Vector2D& other) const {
		return (x * other.y) - (y * other.x);
	}

	/* operators */
	Vector2D& Vector2D::operator = (const Vector2D& obj) {
		x = obj.x;
		y = obj.y;
		return *this;
	}
	Vector2D& operator += (const Vector2D& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2D& operator -= (const Vector2D& obj) {
		this->x -= obj.x;
		this->y -= obj.y;
		return *this;
	}
	Vector2D& operator *= (const Vector2D& obj){
		this->x *= obj.x;
		this->y *= obj.y;
		return *this;
	}
	Vector2D& operator /= (const Vector2D& obj) {
		this->x /= obj.x;
		this->y /= obj.y;
		return *this;
	}
	const Vector2D operator + () const {
		return *this;
	}
	const Vector2D operator + (const double& scalar) const {
		return Vector2D(scalar + x, scalar + y);
	}
	const Vector2D operator + (const Vector2D& other) const {
		return Vector2D(x + other.x, y + other.y);
	}
	const Vector2D operator - () const {
		return Vector2D(-x, -y);
	}
	const Vector2D operator - (const double& scalar) const {
		return Vector2D(x - scalar, y - scalar);
	}
	const Vector2D operator - (const Vector2D& other) const {
		return Vector2D(x - other.x, y - other.y);
	}
	const Vector2D operator * (const double& scalar) const {
		return Vector2D(scalar * x, scalar * y);
	}
	const Vector2D operator / (const double& scalar) const;
	bool operator == (const Vector2D& other) const {
		return (x == other.x) && (y == other.y);
	}
	bool operator != (const Vector2D& other) const {
		return !(*this == other);
	}
	bool operator < (const Vector2D& other) const {
		if (x < other.x)	return true;
		if (y < other.y)	return true;
		return false;
	}
	bool operator > (const Vector2D& other) const {
		if (x > other.x)	return true;
		if (y > other.y)	return true;
		return false;
	}

	static Vector2D const ZERO;
	static Vector2D const LEFT;
	static Vector2D const RIGHT;
	static Vector2D const UP;
	static Vector2D const DOWN;

	double x, y;
};
// EOF