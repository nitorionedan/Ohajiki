#pragma once
#include "Singleton.hpp"
#include <DxLib.h>


struct KeyCode_t
{
	const int Right  = KEY_INPUT_RIGHT;
	const int Left   = KEY_INPUT_LEFT;
	const int Up     = KEY_INPUT_UP;
	const int Down   = KEY_INPUT_DOWN;
	const int Lshift = KEY_INPUT_LSHIFT;
	const int Rshift = KEY_INPUT_RSHIFT;
	const int Return = KEY_INPUT_RETURN;
	const int A      = KEY_INPUT_A;
	const int B      = KEY_INPUT_B;
	const int C      = KEY_INPUT_C;
	const int D      = KEY_INPUT_D;
	const int E      = KEY_INPUT_E;
	const int F      = KEY_INPUT_F;
	const int G      = KEY_INPUT_G;
	const int H      = KEY_INPUT_H;
	const int I      = KEY_INPUT_I;
	const int J      = KEY_INPUT_J;
	const int K      = KEY_INPUT_K;
	const int L      = KEY_INPUT_L;
	const int M      = KEY_INPUT_M;
	const int N      = KEY_INPUT_N;
	const int O      = KEY_INPUT_O;
	const int P      = KEY_INPUT_P;
	const int Q      = KEY_INPUT_Q;
	const int R      = KEY_INPUT_R;
	const int S      = KEY_INPUT_S;
	const int T      = KEY_INPUT_T;
	const int U      = KEY_INPUT_U;
	const int V      = KEY_INPUT_V;
	const int W      = KEY_INPUT_W;
	const int X      = KEY_INPUT_X;
	const int Y      = KEY_INPUT_Y;
	const int Z      = KEY_INPUT_Z;
};


class Input
{
public: static KeyCode_t KeyCode;
};


class Keyboard : public Singleton<Keyboard>
{
	Keyboard();
	friend Singleton<Keyboard>;

public:
	bool Update();
	int GetDown(int keyCode);
	int GetUp(int keyCode);
	bool isDown(int keyCode);
	bool isPush(int keyCode);

private:
	// keyCodeは有効なキーコードか？
	bool IsAvailableCode(int keyCode);
	static const int KEY_NUM = 256;
	int mKeyDownCount[KEY_NUM];
	int mKeyUpCount[KEY_NUM];
};