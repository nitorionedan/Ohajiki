#pragma once


class LineClass
{
public:
	LineClass() : sx(0), sy(0), ex(0), ey(0) {}
	~LineClass() {}
	int sx, sy; //< start position.
	int ex, ey; //< end position.

private:
	void Draw();
};
