#pragma once
#include <memory>
#include "Task.hpp"
#include "PlayerClass.hpp"
#include "Stage.hpp"
#include "Mouse.hpp"


class GameClass : public Task
{
public:
	GameClass();
	~GameClass();

	virtual void Update() override;
	virtual void Draw() override;

	const PlayerClass* GetPlayer() const;
	const PlayerClass* GetPlayer2() const;
	const StageClass* Stage() const;
	static void Pause();

private:
	void Initialize();
	
	std::unique_ptr<PlayerClass> m_player;
	std::unique_ptr<PlayerClass> m_player2;
	std::unique_ptr<StageClass> m_stage;
	std::unique_ptr<MouseClass> m_mouse;
	
	static bool m_pauseFlag;
};