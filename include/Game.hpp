#pragma once
#include "Task.hpp"


class GameClass : public Task
{
public:
	GameClass();
	~GameClass();

	virtual void Update() override;
	virtual void Draw() override;

private:
	void Initialize();
};