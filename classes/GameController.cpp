#include "ExpertSystem.hpp"
#include "GameController.hpp"

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

GameController::GameController ( std::string query, mapFacts allFacts ) : _query(query), _allFacts(allFacts)
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
const mapFacts &		GameController::getAllFacts( void ) const
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
	o << KYEL "In GameController: ------------" KRESET << std::endl;
	o << "Query: " KGRN << i.getQuery() << std::endl << KRESET "Facts:" << std::endl;
	for(mapFacts::const_iterator it = i.getAllFacts().begin();
    	it != i.getAllFacts().end(); ++it)
	{
    	o << "\t" << (*it->second);
	}
	return (o);
}

// ###############################################################
