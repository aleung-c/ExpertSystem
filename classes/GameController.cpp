#include "ExpertSystem.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

GameController::GameController ( void )
{
	return ;
}

GameController::GameController ( GameController const & src )
{
	*this = src;
	return ;
}

GameController &				GameController::operator=( GameController const & rhs )
{
	if (this != &rhs)
	{
		this->_query = rhs.getQuery();
		this->_allFacts = rhs.getAllFacts();
	}
	return (*this);
}

GameController::~GameController ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

GameController::GameController ( std::string query, std::map<char, Fact *> allFacts ) : _query(query), _allFacts(allFacts)
{
	return ;
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################

// GETTER METHOD #################################################

std::string				GameController::getQuery( void ) const
{
	return(this->_query);
}
std::map<char, Fact *>	GameController::getAllFacts( void ) const
{
	return(this->_allFacts);
}

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

std::ostream &				operator<<(std::ostream & o, GameController const & i)
{
	o << KYEL "In GameController ------------" KRESET << std::endl;
	o << "Query: " KGRN << i.getQuery() << std::endl << KRESET "Facts:" << std::endl;
	o << i.getAllFacts()[0];
	// for(std::map<char, Fact *>::const_iterator it = i.getAllFacts().begin();
 //    	it != i.getAllFacts().end(); ++it)
	// {
 //    	o << (*it->second);
	// }
	return (o);
}

// ###############################################################
