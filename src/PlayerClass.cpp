#include "PlayerClass.hpp"


int PlayerClass::s_num = 0;


PlayerClass::PlayerClass()
{
	++s_num;
}


void PlayerClass::Finalize()
{
	s_num = 0;
}
