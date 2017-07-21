#include "Rule.hpp"
#include <stack>
#include <regex>

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Rule::Rule ( void )
{
	return ;
}

Rule::Rule ( Rule const & src )
{
	*this = src;
	return ;
}

Rule &				Rule::operator=( Rule const & rhs )
{
	if (this != &rhs)
	{
		this->_name = rhs.GetName();
		this->_poloneseInversed = rhs.GetPoloneseInversed();
		this->_proposition = rhs.GetProposition();
		this->_result = rhs.GetResult();
	}
	return (*this);
}

Rule::~Rule ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

// ###############################################################

// PUBLIC METHOD #################################################

bool				Rule::IsCheck( mapFacts list ) const
{
	std::string				out;
	std::stringstream		tmpstr(this->_poloneseInversed);
	std::stack<Value>		facts;
	Value					one;
	Value					two;
	Value					val;

	while (tmpstr >> out)
	{
		if (std::strstr(OPERATORS, out.c_str()))
		{
			two = facts.top();
			facts.pop();
			one = facts.top();
			facts.pop();
			val.b = this->_chooseOperator(list, one, two, out.c_str()[0]);
			facts.push(val);
		}
		else
		{
			val.s = std::string(out);
			facts.push(val);
			val.s.clear();
		}
	}
	if (facts.empty() || facts.top().s.empty())
		return (facts.top().b);

	// In case we have a rule without operator
	one = facts.top();
	if (this->_checkUnknownBehavior(list, one))
		throw CustomException("Unknown Behavior");

	return (this->_factOrRevFact(list, one));
}

// ###############################################################

// GETTER METHOD #################################################

std::string			Rule::GetName( void ) const
{
	return(this->_name);
}
std::string			Rule::GetPoloneseInversed( void ) const
{
	return(this->_poloneseInversed);
}
std::string			Rule::GetProposition( void ) const
{
	return(this->_proposition);
}
std::string			Rule::GetResult( void ) const
{
	return(this->_result);
}

// ###############################################################

// SETTER METHOD #################################################

void				Rule::SetName(std::string name)
{
	this->_name = name;
	return ;
}
void				Rule::SetPoloneseInversed(void)
{
	this->_poloneseInversed = this->_convertToNPI(this->_proposition);
	return ;
}
void				Rule::SetProposition(std::string str)
{
	this->_proposition = this->_strtrim(str);
	this->SetPoloneseInversed();
	return ;
}
void				Rule::SetResult(std::string str)
{
	this->_result = this->_strtrim(str);
	return ;
}

// ###############################################################

// PRIVATE METHOD ################################################

bool				Rule::_checkUnknownBehavior(mapFacts list, Value v) const
{
	std::vector<Rule>	rules;
	std::regex			word("[=|>| ]");
	std::string			result;
	std::string			proposition;

	if (v.s.empty())
		return (false);

	rules = (v.s[0] == '!') ? list[v.s[1]]->LinkedRules : list[v.s[0]]->LinkedRules;
	for(unsigned int i = 0 ; i < rules.size(); i++)
	{
		result = std::regex_replace(rules[i].GetResult().c_str(),word,"",std::regex_constants::format_default);
		proposition = std::regex_replace(rules[i].GetProposition().c_str(), word, "", std::regex_constants::format_default);
		if (this->_communChar(this->_proposition, result) && this->_communChar(this->_result, proposition)) /* We compare the facts of proposition's rule and result's of a other for unknown behavior */
			return (true);
	}
	return (false);
}

bool				Rule::_communChar(std::string str, std::string tofind) const
{
	for (size_t i = 0; i < tofind.size(); i++)
		if (std::strchr(str.c_str(), tofind[i]) != NULL)
			return (true);
	return (false);
}

std::string			Rule::_strtrim(std::string str)
{
	str.erase(str.find_last_not_of(" \n\r\t") + 1);
	return (str);
}

/*
**  Proposition
**  Must be formated like "!C ^ ( ( B + A ) + ( C | D ) )"
**  spaces are important
*/

std::string			Rule::_convertToNPI(std::string str)
{
	std::string				NPI;
	std::string				out;
	std::stringstream		tmpstr(str);
	std::stack<std::string>	operators;
	std::map<char, int>		priority = { {'+', 3}, {'|', 2}, {'^', 1}, {'*', 0} };

	while (tmpstr >> out)
	{
		if (std::strstr(OPERATORS, out.c_str()))
		{
			if (!operators.empty() and priority[out.c_str()[0]] <= priority[operators.top()[0]])
				this->_changeStack(NPI, operators);
			operators.push(out);
		}
		else if (std::strstr("(", out.c_str()))
			operators.push(out);
		else if (std::strstr(")", out.c_str()))
		{
			while (!std::strstr("(", operators.top().c_str()))
				this->_changeStack(NPI, operators);
			operators.pop();
		}
		else
			NPI += (out + " ");
	}
	while (!operators.empty())
		this->_changeStack(NPI, operators);
	return (this->_strtrim(NPI));
}

void				Rule::_changeStack(std::string & NPI, std::stack<std::string> & operators)
{
	NPI += operators.top() + " ";
	operators.pop();
}

/*
**  Solver
*/

bool				Rule::_chooseOperator(mapFacts list, Value one, Value two, char op) const
{
	if (op == '|')
		return (this->_factOrRevFact(list, one) || this->_factOrRevFact(list, two));
	else if (op == '+')
		return (this->_factOrRevFact(list, one) && this->_factOrRevFact(list, two));
	else if (op == '^')
		return (this->_factOrRevFact(list, one) && this->_factOrRevFact(list, two));
	return (this->_jokerChoice(list, one, two));
}

/*
**  Joker
*/

bool				Rule::_jokerChoice(mapFacts list, Value one, Value two) const
{
	std::string						str;
	std::map<std::string, char>		choice_op = { {"3", '+'}, {"4", '|'}, {"5", '^'} };
	std::map<std::string, Value>	choice_val = { {"1", one}, {"2", two} };

	while (1)
	{
		std::cout << std::endl << KRED "\tJoker" KRESET " choice for " KYEL << this->_valueToStr(one) <<KRESET " and " KYEL << this->_valueToStr(two) << KRESET" :" << std::endl;
		std::cout << KYEL "\t\t1" KRESET << " Left Value\n" << KYEL "\t\t2" KRESET << " Right Value\n" << KYEL "\t\t3" KRESET << " Operator '+'\n" << KYEL "\t\t4" KRESET << " Operator '|'\n" << KYEL "\t\t5" KRESET << " Operator '^'" << std::endl;
		str.clear();
		std::getline(std::cin, str);
		if (str.empty())
			break ;
		if (str.length() == 1 and std::strstr("345", str.c_str()))
			return (this->_chooseOperator(list, one, two, choice_op[str]));
		if (str.length() == 1 and std::strstr("12", str.c_str()))
			return (this->_factOrRevFact(list, choice_val[str]));
	}
	throw CustomException("Invalid User Joker Choise");
	return (true);
}

bool 				Rule::_checkInput(void) const
{
	return ((std::cin.bad() || std::cin.eof()) ? false : true);
}

std::string 				Rule::_valueToStr(Value v) const
{
	if (v.s.empty())
		return (v.b ? "true" : "false");
	return (v.s);
}

/*
**  For !Fact ( like !A)
*/

bool				Rule::_factOrRevFact(mapFacts list, Value val) const
{
	if (val.s.empty())
		return (val.b);
	return ((val.s[0] == '!') ? !list[val.s[1]]->GetValueRules() : list[val.s[0]]->GetValueRules());
}

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
