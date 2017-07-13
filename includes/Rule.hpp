#ifndef RULE_HPP
# define RULE_HPP

# include "ExpertSystem.hpp"

class Rule
{
	public:
		Rule();
		~Rule();
		
		bool			is_check();

	private:
		std::string		_name;
		std::string		_poloneseInversed;
		std::string		_calcul;
};

#endif
