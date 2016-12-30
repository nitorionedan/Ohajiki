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

	const std::shared_ptr<PlayerClass> Player() const;
	const std::shared_ptr<PlayerClass> Player2() const;
	const std::shared_ptr<StageClass> Stage() const;

private:
	void Initialize();
	
	std::shared_ptr<PlayerClass> m_player;
	std::shared_ptr<PlayerClass> m_player2;
	std::shared_ptr<StageClass> m_stage;
	
	bool m_pauseFlag;
};