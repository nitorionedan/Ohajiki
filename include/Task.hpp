#pragma once

// -----------------------------------
// �Ȃɂ��̃��W���[���͂�������p������
class Task
{
public:
	virtual ~Task(){}
	virtual void Update() = 0;
	virtual void Draw() = 0;
};