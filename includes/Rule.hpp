#ifndef RULE_HPP
# define RULE_HPP

# include "ExpertSystem.hpp"

class Rule
{
	public:
	
		Rule( void );
		Rule( Rule const & src );
		virtual ~Rule( void );

		Rule &			operator=( Rule const & rhs );

		// Getter
		std::string		GetName( void ) const;
		std::string		GetPoloneseInversed( void ) const;
		std::string		GetProposition( void ) const;
		std::string		GetResult( void ) const;
	
		// Setter
		void			SetName(std::string name);
		void			SetPoloneseInversed(std::string str);
		void			SetProposition(std::string str);
		void			SetResult(std::string str);

		// For algorythme
		bool			IsCheck( void );

	private:

		std::string		_strtrim(std::string str); // right trim called in setter Proposition/Result


		std::string		_name;
		std::string		_poloneseInversed;
		std::string		_proposition;
		std::string		_result;
};

#endif
