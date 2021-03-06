#include "Fact.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Fact::Fact ( void )
{
	return ;
}

Fact::Fact ( Fact const & src )
{
	*this = src;
	return ;
}

Fact &				Fact::operator=( Fact const & rhs )
{
	if (this != &rhs)
	{
		this->_name = rhs.GetName();
		this->_value = rhs.GetValue();
		this->_AllFacts = rhs.getAllFacts();
		this->LinkedRules = rhs.LinkedRules;
	}
	return (*this);
}

Fact::~Fact ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

bool					Fact::operator+( Fact const & rhs )
{
	return ((this->GetValueRules() && rhs.GetValueRules()));
}

bool					Fact::operator|( Fact const & rhs )
{
	return ((this->GetValueRules() || rhs.GetValueRules()));
}

bool					Fact::operator^( Fact const & rhs )
{
	return ((this->GetValueRules() ^ rhs.GetValueRules()));
}

bool					Fact::operator+( bool ean )
{
	return ((this->GetValueRules() && ean));
}

bool					Fact::operator|( bool ean )
{
	return ((this->GetValueRules() || ean));
}

bool					Fact::operator^( bool ean )
{
	return ((this->GetValueRules() ^ ean));
}

bool					Fact::operator!( void )
{
	return (!(this->GetValueRules()));
}

// ###############################################################

// PUBLIC METHOD #################################################

bool					Fact::GetValueRules( void ) const
{
	if (this->_value || this->LinkedRules.empty())
		return (this->_value);

	for(std::vector<Rule>::const_iterator it = this->LinkedRules.begin(); it != this->LinkedRules.end(); ++it)
		if (it->IsCheck(this->_AllFacts, false))
			return (true);

	return(false);
}

bool					Fact::GetValueRules( bool verbose ) const
{
	if (this->_value || this->LinkedRules.empty())
		return (this->_value);

	for(std::vector<Rule>::const_iterator it = this->LinkedRules.begin(); it != this->LinkedRules.end(); ++it)
	{
		if (it->IsCheck(this->_AllFacts, verbose))
			return (true);
		Rule::count = 0;
	}

	return(false);
}

// ###############################################################

// GETTER METHOD #################################################

char					Fact::GetName( void ) const
{
	return(this->_name);
}
bool					Fact::GetValue( void ) const
{
	return(this->_value);
}
mapFacts				Fact::getAllFacts( void ) const
{
	return(this->_AllFacts);
}

// ###############################################################

// SETTER METHOD #################################################

void					Fact::SetName(char n)
{
	this->_name = n;
	return ;
}
void					Fact::SetValue(bool b)
{
	this->_value = b;
	return ;
}
void					Fact::SetAllFacts(mapFacts f)
{
	this->_AllFacts = f;
	return ;
}

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

std::ostream &				operator<<(std::ostream & o, Fact const & i)
{
	o << "Fact: " KGRN <<  i.GetName() << KRESET " has base value: ";
	if (i.GetValue())
		o <<  KGRN; 
	else
		o << KRED; 
	o << std::boolalpha << i.GetValue() << KRESET;
	if (i.LinkedRules.empty())	
		o << " with no Rule.";
	else
	{
		o << " with Rule:";
		for(std::vector<Rule>::const_iterator it = i.LinkedRules.begin(); it != i.LinkedRules.end(); ++it)
			o << " [ " KGRN << it->GetProposition() << KRESET " ]";
	}
	o << std::endl;
	return (o);
}

bool						operator+( bool ean, Fact const & rhs  )
{
	return ((ean && rhs.GetValueRules()));
}

bool						operator|( bool ean, Fact const & rhs  )
{
	return ((ean || rhs.GetValueRules()));
}

bool						operator^( bool ean, Fact const & rhs  )
{
	return ((ean ^ rhs.GetValueRules()));
}

// ###############################################################