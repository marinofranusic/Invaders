#include <windows.h>
#include <cassert>
#include <cstdio>
#include "DiceInvadersLib.h"
#include "DiceInvaders.h"

DiceInvadersLib::DiceInvadersLib(const char* libraryPath)
{
	m_lib = LoadLibrary(libraryPath);
	assert(m_lib);

	DiceInvadersFactoryType* factory = (DiceInvadersFactoryType*)GetProcAddress(
		m_lib, "DiceInvadersFactory");
	m_interface = factory();
	assert(m_interface);
}

DiceInvadersLib::~DiceInvadersLib()
{
	FreeLibrary(m_lib);
}

IDiceInvaders* DiceInvadersLib::get() const
{
	return m_interface;
}

