#ifndef FACT_HPP
# define FACT_HPP

# include "ExpertSystem.hpp"

class Fact
{
	public:
	
		Fact( void );
		Fact( Fact const & src );
		virtual ~Fact( void );

		Fact &				operator=( Fact const & rhs );

		char				GetName( void ) const;
		bool				GetValue( void ) const;
		mapFacts			getAllFacts( void ) const;

		void				SetName(char n);
		void				SetValue(bool b);
		void				SetAllFacts(mapFacts f);
	
		std::vector<Rule>	LinkedRules;

		bool				GetValueRules( void ) const; /* Final Value for a fact : check base value and callback rules */

		// overload operator with polymorphism for easier algo
		bool				operator+( Fact const & rhs );
		bool				operator|( Fact const & rhs );
		bool				operator^( Fact const & rhs );
		bool				operator+( bool ean );
		bool				operator|( bool ean );
		bool				operator^( bool ean );
		bool				operator!( void );

	private:

		char				_name;
		bool				_value;
		mapFacts			_AllFacts;
};

std::ostream &				operator<<(std::ostream & o, Fact const & i);
bool						operator+(bool ean, Fact const & rhs );
bool						operator|(bool ean, Fact const & rhs );
bool						operator^(bool ean, Fact const & rhs );

#endif
