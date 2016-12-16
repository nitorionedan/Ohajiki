#pragma once

#include <memory>
#include "Circle.hpp"
#include "Image.hpp"
#include "Object.hpp"


class PlayerClass : public Object
{
public:
	PlayerClass();
	~PlayerClass();
	void Update();
	void Draw();

private:
	void Initialize();

	std::unique_ptr<Circle> m_circle;
	std::unique_ptr<Image> m_img;
};
