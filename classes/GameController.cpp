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

GameController &		GameController::operator=( GameController const & rhs )
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

GameController::GameController ( std::string query, mapFacts allFacts, bool verbose )
:_verbose(verbose), _query(query), _allFacts(allFacts)
{
	if (this->_verbose)
		std::cout << *this;
	return ;
}

// ###############################################################

// OVERLOAD OPERATOR #############################################

// ###############################################################

// PUBLIC METHOD #################################################

void					GameController::run( void )
{
	for ( size_t i = 0 ; i < this->_query.length(); i++)
	{
		if (this->_query[i] != '?')
			std::cout << "Query for fact " << this->_query[i]
						<< " is " << (this->_allFacts[this->_query[i]])->GetValueRules()
						<< std::endl;
	}
}

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

std::ostream &			operator<<(std::ostream & o, GameController const & i)
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
