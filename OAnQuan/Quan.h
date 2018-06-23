#pragma once
class Quan
{
protected:
	int Type, Value;
public:
	enum Quan_Type { QUAN, DAN };

	Quan();
	Quan(Quan_Type quan_type);
	~Quan();

	int getType() const;
	int getValue() const;
};

