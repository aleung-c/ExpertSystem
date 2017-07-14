#include "../includes/ExpertSystem.hpp"

Rule::Rule()
{

}

Rule::~Rule()
{

}

bool	Rule::IsCheck()
{
	return (false);
}

/*
**	Getters - setters.
*/

std::string		Rule::GetName()
{
	return (_name);
}

std::string		Rule::GetPoloneseInversed()
{
	return (_poloneseInversed);
}

std::string		&Rule::GetProposition()
{
	return (_proposition);
}

std::string		&Rule::GetResult()
{
	return (_result);
}

void			Rule::SetName(std::string name)
{
	_name = name;
}

void			Rule::SetPoloneseInversed(std::string str)
{
	_poloneseInversed = str;
}

void			Rule::SetProposition(std::string str)
{
	_proposition = str;
}

void			Rule::SetResult(std::string str)
{
	_result = str;
}
