#include "Stage.hpp"
#include "Image.hpp"


StageClass::StageClass()
	: m_img(new Image)
{
	m_img->Load("img/game_ring_0.png", "field_0"); //< Red normal ring.
	Initialize();
}


StageClass::~StageClass()
{
}


void StageClass::Initialize()
{
}


void StageClass::Update()
{
}


void StageClass::Draw()
{
	m_img->DrawRota(320, 240, 1.0, 0.0, "ring_0", TRUE);
}
