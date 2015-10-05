#ifndef DICEINVADERSLIB_H
#define DICEINVADERSLIB_H

#include "DiceInvaders.h"

class DiceInvadersLib
{
public:
	explicit DiceInvadersLib(const char* libraryPath);
	~DiceInvadersLib();
	IDiceInvaders* get() const;

private:
	DiceInvadersLib(const DiceInvadersLib&);
	DiceInvadersLib& operator=(const DiceInvadersLib&);

private:
	IDiceInvaders* m_interface;
	HMODULE m_lib;
};
#endif