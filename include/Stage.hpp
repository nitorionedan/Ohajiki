#pragma once
#include <memory>
#include "Image.hpp"
#include "RectClass.hpp"


class StageClass
{
public:
	StageClass();
	~StageClass();

	void Initialize();
	void Update();
	void Draw();
	const Rect& GetBorder() const;
	void GetBorder(int& left, int& right, int& top, int& bottom) const;

private:

	std::unique_ptr<Image> m_img;
	Rect m_rect;
	int m_screen;
	
};
