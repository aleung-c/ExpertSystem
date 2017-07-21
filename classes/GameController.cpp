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

GameController::GameController ( std::string query, mapFacts allFacts, bool verbose, bool final )
: _query(query), _allFacts(allFacts), _verbose(verbose), _finalResult(final)
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
	std::cout << std::boolalpha;
	for ( size_t i = 0 ; i < this->_query.length(); i++)
	{
		if (this->_query[i] != '?')
		{
			if ((this->_allFacts[this->_query[i]])->GetValueRules(this->_verbose))
				std::cout << "Query for fact " KYEL << this->_query[i] << KRESET " is " KGRN << true << KRESET << std::endl;
			else
			{
				std::cout << "Query for fact " KYEL << this->_query[i] << KRESET " is " KRED << false << KRESET << std::endl;
				this->_finalResult = false;
			}
		}
	}
	this->_printFinalResult();
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
bool					GameController::getVerbose( void ) const
{
	return(this->_verbose);
}
bool					GameController::getFinalResult( void ) const
{
	return(this->_finalResult);
}

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

void					GameController::_printFinalResult( void ) const
{
	if (this->_finalResult)
		std::cout << "Query " KYEL << this->_query << KRESET " is " KGRN << true << KRESET << std::endl;
	else
		std::cout << "Query " KYEL << this->_query << KRESET " is " KRED << false << KRESET << std::endl;
}

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
