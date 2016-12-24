#pragma once
#include "Stage.hpp"
#include "Player.hpp"


class VisitorClass
{
public:
	VisitorClass() {}
	~VisitorClass() {}

	virtual void VisitStage(StageClass* stage) = 0;
	//virtual void visitPlayer(PlayerClass* player) = 0;

private:

};
