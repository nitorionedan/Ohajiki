#pragma once
#include <memory>
#include "Task.hpp"


class PlayerClass;
class StageClass;


class GameClass : public Task
{
public:
	GameClass();
	~GameClass();

	virtual void Update() override;
	virtual void Draw() override;

private:
	void Initialize();
	
	std::shared_ptr<PlayerClass> m_player;
	std::shared_ptr<StageClass> m_stage;
};