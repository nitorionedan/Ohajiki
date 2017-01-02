#include "Stage.hpp"


StageClass::StageClass()
	: m_img(new Image)
{
	m_img->Load("img/game_ring_0.png", "field_0"); //< Red normal ring.
	m_screen = MakeScreen(640, 480, TRUE);
}


StageClass::~StageClass()
{
}


void StageClass::Initialize()
{
	m_rect.left   = 18;
	m_rect.right  = 613;
	m_rect.top    = 28;
	m_rect.bottom = 462;
}


void StageClass::Update()
{
}


void StageClass::Draw()
{
	SetDrawScreen(m_screen);
	ClearDrawScreen();
	m_img->DrawRota(320, 240, 1.0, 0.0, "field_0", TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	//GraphFilter(m_screen, DX_GRAPH_FILTER_GAUSS, 16, 200);
	DrawGraph(0, 0, m_screen, true);
}


const Rect & StageClass::GetBorder() const
{
	return m_rect;
}


void StageClass::GetBorder(int & left, int & right, int & top, int & bottom) const
{
	left   = m_rect.left;
	right  = m_rect.right;
	top    = m_rect.top;
	bottom = m_rect.bottom;
}
