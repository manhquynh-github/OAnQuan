#include "Quan.h"


Quan::Quan()
{
}

Quan::Quan(Quan_Type quan_type)
{
	Type = quan_type;
	if (quan_type == QUAN)
		Value = 10;
	else
		Value = 1;
}


Quan::~Quan()
{
}

int Quan::getType() const
{
	return Type;
}

int Quan::getValue() const
{
	return Value;
}
