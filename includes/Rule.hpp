#ifndef RULE_HPP
# define RULE_HPP

# include "ExpertSystem.hpp"

class Rule
{
	public:
		Rule();
		~Rule();
		
		bool			IsCheck();

		std::string		GetName();
		std::string		GetPoloneseInversed();
		std::string		&GetProposition();
		std::string		&GetResult();

		void			SetName(std::string name);
		void			SetPoloneseInversed(std::string str);
		void			SetProposition(std::string str);
		void			SetResult(std::string str);

	private:
		std::string		_name;
		std::string		_poloneseInversed;
		std::string		_proposition;
		std::string		_result;
};

#endif
