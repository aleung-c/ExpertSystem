#include "Rule.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Rule::Rule ( void )
{
	return ;
}

Rule::Rule ( Rule const & src )
{
	*this = src;
	return ;
}

Rule &				Rule::operator=( Rule const & rhs )
{
	if (this != &rhs)
	{
		this->_name = rhs.GetName();
		this->_poloneseInversed = rhs.GetPoloneseInversed();
		this->_proposition = rhs.GetProposition();
		this->_result = rhs.GetResult();
	}
	return (*this);
}

Rule::~Rule ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

// ###############################################################

// PUBLIC METHOD #################################################

bool				Rule::IsCheck( void )
{
	return (false);
}

// ###############################################################

// GETTER METHOD #################################################

std::string			Rule::GetName( void ) const
{
	return(this->_name);
}
std::string			Rule::GetPoloneseInversed( void ) const
{
	return(this->_poloneseInversed);
}
std::string			Rule::GetProposition( void ) const
{
	return(this->_proposition);
}
std::string			Rule::GetResult( void ) const
{
	return(this->_result);
}

// ###############################################################

// SETTER METHOD #################################################

void				Rule::SetName(std::string name)
{
	this->_name = name;
	return ;
}
void				Rule::SetPoloneseInversed(std::string str)
{
	this->_poloneseInversed = str;
	return ;
}
void				Rule::SetProposition(std::string str)
{
	this->_proposition = this->_strtrim(str);
	return ;
}
void				Rule::SetResult(std::string str)
{
	this->_result = this->_strtrim(str);
	return ;
}

// ###############################################################

// PRIVATE METHOD ################################################

std::string			Rule::_strtrim(std::string str)
{
	str.erase(str.find_last_not_of(" \n\r\t") + 1);
	return (str);
}

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
