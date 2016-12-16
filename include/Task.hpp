#pragma once

// -----------------------------------
// ‚È‚É‚©‚Ìƒ‚ƒWƒ…[ƒ‹‚Í‚±‚¿‚ç‚ğŒp³‚·‚é
class Task
{
public:
	virtual ~Task(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};