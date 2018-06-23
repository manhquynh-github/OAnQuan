#include "O.h"



O::O()
{
	Type = OTHUONG;
	Value = 5;
}

O::O(O_Type o_type)
{
	Type = o_type;
	if (o_type == OQUAN)
		Value = 10;
	else
		Value = 5;
}


O::~O()
{
}

int O::getType() const
{
	return Type;
}

int O::getValue() const
{
	return Value;
}

int O::Consume()
{
	int s = Value;
	Value = 0;
	return s;
}

void O::AddValue(int value)
{
	Value += value;
}
