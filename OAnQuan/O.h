#pragma once
#include "Quan.h"
#include "List.h"
class O
{
protected:
	int Value, Type;
public:
	enum O_Type { OQUAN, OTHUONG };

	O();
	O(O_Type o_type);
	~O();

	int getType() const;
	int getValue() const;
	int Consume();
	void AddValue(int value);
};

