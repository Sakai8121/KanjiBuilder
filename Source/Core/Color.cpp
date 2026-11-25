#include "Core/Color.h"
#include <DxLib.h>

unsigned int Color::ToDxColor() const
{
	return GetColor(r, g, b);
}