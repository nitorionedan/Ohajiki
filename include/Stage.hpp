#pragma once
#include <memory>


class Image;


class StageClass
{
public:
	StageClass();
	~StageClass();

	void Update();
	void Draw();

private:
	void Initialize();

	std::unique_ptr<Image> m_img;
};
