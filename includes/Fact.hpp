#ifndef FACT_HPP
# define FACT_HPP

# include "ExpertSystem.hpp"

class Fact
{
	public:
		Fact();
		~Fact();


		std::vector<Fact *>		AllFacts;
		std::vector<Rule>		LinkedRules;

		char					GetName();
		bool					GetValue();

		void					SetName(char n);
		void					SetValue(bool b);

	private:
		char					_name;
		bool					_value; // default FALSE
};

#endif
