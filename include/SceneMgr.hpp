#pragma once
#include "Task.hpp"
#include "Game.hpp"


class SceneMgrClass : public Task
{
public:
	SceneMgrClass();
	~SceneMgrClass();
	
	virtual void Update() override;
	virtual void Draw() override;

private:
	void Initialize();

	GameClass* m_game;
};