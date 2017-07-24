#ifndef RULE_HPP
# define RULE_HPP

#include <stack>

# include "ExpertSystem.hpp"

struct Value {
    bool b;
    std::string s;
};

class Rule
{
	public:
	
		Rule( void );
		Rule( bool verbose );
		Rule( Rule const & src );
		virtual ~Rule( void );

		Rule &			operator=( Rule const & rhs );

		// Getter
		std::string		GetName( void ) const;
		std::string		GetPoloneseInversed( void ) const;
		std::string		GetProposition( void ) const;
		std::string		GetResult( void ) const;
		bool			GetVerbose( void ) const;

		// Setter
		void			SetName(std::string name);
		void			SetPoloneseInversed( void );
		void			SetProposition(std::string str);
		void			SetResult(std::string str);

		// For algorythme
		bool			IsCheck( mapFacts list, bool verbose ) const;

	private:

		std::string		_strtrim(std::string str); /* right trim called in setter Proposition/Result */
		std::string		_convertToNPI(std::string str); /* Algorithme Shunting-yard basic */
		bool			_chooseOperator(mapFacts list, Value one, Value two, char op) const;
		bool			_factOrRevFact(mapFacts list, Value val) const;
		void			_changeStack(std::string & NPI, std::stack<std::string>	& operators);
		bool			_checkUnknownBehavior(mapFacts list, Value v) const;
		bool			_communChar(std::string str, std::string tofind) const;
		bool			_verboseOrNot( bool n, bool v ) const;
		bool			_jokerChoice(mapFacts list, Value one, Value two) const;
		bool			_checkInput(void) const;
		std::string		_valueToStr(Value v) const;

		std::string		_name;
		std::string		_poloneseInversed;
		std::string		_proposition;
		std::string		_result;
		bool			_verbose;
};

#endif
