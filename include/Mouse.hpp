#pragma once


class MouseClass
{
	struct Position
	{
		int x, y;
	};

public:
	MouseClass();
	~MouseClass();

	void Update();
	void Draw();

private:
	MouseClass(const MouseClass&) {}

	void Initialize();

	Position pos;
	int gh_mouse; //< Mouse img
};