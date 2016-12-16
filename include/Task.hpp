#pragma once

// -----------------------------------
// なにかのモジュールはこちらを継承する
class Task
{
public:
	virtual ~Task(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};