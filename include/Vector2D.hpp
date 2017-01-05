#pragma once

class Vector2D
{
public:
	Vector2D(double x, double y);
	Vector2D() {}

	void SetVec(double x, double y);
	void SetZero();
	void Fill(double XY);

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
	static Vector2D GetVec(double x, double y);

	// @brief				自分→相手のベクトルを生成
	// @param[in]	vec1	自分
	// @param[in]	vec2	相手
	// @return				生成したベクトル
	static Vector2D& GetVec2(const Vector2D& vec1, const Vector2D& vec2);

	const Vector2D& Normalize() const;

	// @brief Get length from vector.
	const double Length() const;

	// @brief     Get radian from vector.
	// @return    Radian.
	// @attention This func uses ToDeg().
	const double ToRad() const;

	// @brief  Get degree from vector.
	// @return Degree.
	const double ToDeg() const;

	// ---------------------------------------------------
	// @brief				相手までのベクトルを計算
	// @param[in]	other	相手のベクトル
	// @return				相手までのベクトル
	double Distance(const Vector2D& other) const;

	// ---------------------------------------------------
	// @brief             内積を計算
	// @param[in]  other  相手のベクトル
	// @return            内積
	double DotProduct(const Vector2D& other) const;

	// ---------------------------------------------------
	// @brief				外積を計算
	// @param[in]	other	相手のベクトル
	// @return				外積
	double CrossProduct(const Vector2D& other) const;

	/* operators */
	Vector2D& Vector2D::operator = (const Vector2D& obj);
	Vector2D& operator += (const Vector2D& other);
	Vector2D& operator -= (const Vector2D& obj);
	Vector2D& operator *= (const Vector2D& obj);
	Vector2D& operator /= (const Vector2D& obj);

	// @brief +vec
	const Vector2D operator + () const;
	
	// @brief vec + num
	const Vector2D operator + (const double& scalar) const;
	
	// @brief vec + vec
	const Vector2D operator + (const Vector2D& other) const;
	
	// @brief -vec
	const Vector2D operator - () const;
	
	// @brief vec - num
	const Vector2D operator - (const double& scalar) const;
	
	// @brief vec - vec
	const Vector2D operator - (const Vector2D& other) const;
	
	// @brief vec * num
	const Vector2D operator * (const double& scalar) const;
	
	// @brief vec / num
	const Vector2D operator / (const double& scalar) const;
	
	bool operator == (const Vector2D& other) const;
	bool operator != (const Vector2D& other) const;
	bool operator < (const Vector2D& other) const;
	bool operator > (const Vector2D& other) const;

	static Vector2D const ZERO;
	static Vector2D const LEFT;
	static Vector2D const RIGHT;
	static Vector2D const UP;
	static Vector2D const DOWN;

	double x, y;
};

// EOF