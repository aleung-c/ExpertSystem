#include "../includes/ExpertSystem.hpp"

Fact::Fact() : _value(false)
{

}

Fact::~Fact()
{

}

char			Fact::GetName()
{
	return (_name);
}

bool			Fact::GetValue()
{
	return (_value);
}

void			Fact::SetName(char n)
{
	_name = n;
}

void			Fact::SetValue(bool b)
{
	_value = b;
}
