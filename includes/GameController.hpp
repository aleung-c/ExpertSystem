#ifndef GAMECONTROLLER_HPP
# define GAMECONTROLLER_HPP

# include "ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Input handling class										//
//																//
// ------------------------------------------------------------	//
/*
**  Second Stage
**
**	This class will handle the resolution of the expert system 
**	query.
**
**  I'll iterate through the query, check/put every fact and
**  print the final conclusion.
*/

class GameController
{
	public:
	
		GameController( void );
		GameController( std::string query, std::map<char, Fact *> allFacts, bool verbose, bool final);
		GameController( GameController const & src );
		virtual ~GameController( void );

		GameController &			operator=( GameController const & rhs );
	

		std::string				getQuery( void ) const;
		const mapFacts &		getAllFacts( void ) const;
		bool					getVerbose( void ) const;
		bool					getFinalResult( void ) const;


		void					run( void );

	private:

		std::string				_query;
		mapFacts				_allFacts;
		bool					_verbose;
		bool					_finalResult;

		void					_printFinalResult( void ) const;

};

std::ostream &				operator<<(std::ostream & o, GameController const & i);

#endif
