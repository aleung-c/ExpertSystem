#include "ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Data collecting												//
//																//
// ------------------------------------------------------------	//
/*
**	At this point, our datas are lexically and semantically OK,
**	we now have to scoop them into the desired form in view
**	of the processing.
*/

void		InputController::FillValues(t_ExpSysFile &file)
{
	if (!_initialized)
	{
		throw CustomException(KRED "InputController class not initialized!"
			" Use InputController::Init([...]) first!" KRESET);
	}
	else
	{
		collectFacts(file);
		setInitFacts(file);
		// printFacts(file); //
		collectRules(file);
		collectQuery(file);
	}
}

/*
**	Will run through each parser token and extract the FACTS datas,
**	to put then into the corresponding objects.
*/

void		InputController::collectFacts(t_ExpSysFile &file)
{
	std::list<t_token>::iterator	next;
	Fact							*newFact;
	char							factChar;
	std::string						lineStr;

	for (std::list<t_token>::iterator it = file.TokenList.begin();
			it != file.TokenList.end();
			it++)
	{
		// parse facts
		if ((*it). TokenType == FACT
			|| (*it).TokenType == INIT_FACTS
			|| (*it).TokenType == QUERY)
		{
			lineStr = (*it).Value;
			for (int i = 0; lineStr[i]; i++)
			{
				if (lineStr[i] >= 'A' && lineStr[i] <= 'Z')
				{
					factChar = lineStr[i];
					if (file.AllFacts.find(factChar)
						== file.AllFacts.end())
					{
						newFact = new Fact();
						newFact->SetName(factChar);
						newFact->SetValue(false); // no matter the value. init must NOT be done here, as
												  // we would miss the initialized existing facts.
						file.AllFacts[factChar] = newFact;
					}
				}
			}
		}
	}
	this->fillFactsWithMap(file);
}

/*
**	Parse the "=" line and set the fact initial values.
*/

void		InputController::setInitFacts(t_ExpSysFile &file)
{
	std::string		initFactsLine;

	for (std::list<t_token>::iterator it = file.TokenList.begin();
			it != file.TokenList.end();
			it++)
	{
		if ((*it).TokenType == INIT_FACTS)
		{
			initFactsLine = (*it).Value;
			for (int i = 0; initFactsLine[i]; i++)
			{
				if (initFactsLine[i] >= 'A' && initFactsLine[i] <= 'Z')
				{
					file.AllFacts[initFactsLine[i]]->SetValue(true);
				}
			}
		}
	}
}

/*
**  Fill All Facts with map completed.
*/

void		InputController::fillFactsWithMap(t_ExpSysFile &file)
{
	for (std::map<char, Fact *>::iterator it = file.AllFacts.begin();
			it != file.AllFacts.end();
			++it)
	{
		it->second->SetAllFacts(file.AllFacts);
	}
}

/*
**	Debug printing method to display FACTS and their status.
*/

void	InputController::printFacts(t_ExpSysFile &file)
{
	std::cout << KYEL "Facts collected: --------------" KRESET << std::endl;
	for (std::map<char, Fact *>::iterator it = file.AllFacts.begin();
			it != file.AllFacts.end();
			++it)
	{
    	std::cout << it->first << " => " << it->second->GetName() << " - ";
    	if (it->second->GetValue())
    		std::cout << "TRUE" << std::endl;
    	else
    		std::cout << "FALSE" << std::endl;
	}
}

/*
**	RULES go into FACTS --> EACH FACT HAS ASSOCIATED RULES.
**	Each File has its own facts and rules.
**
**	I decided to reparse the whole string file to get the rules.
**	Its more easy.
**	The additionnal formating is done here as well.
*/

void	InputController::collectRules(t_ExpSysFile &file)
{
	std::string				line;
	std::stringstream		progStream(file.Str);
	std::size_t				pos;
	Rule					newRule(this->_expertSystemDatas->Verbose);

	//	Ill search each rules, and insert them into the corresponding facts
	//	thanks to the map container.
	while (getline(progStream, line))
	{
		if ((pos = line.find("=>")) != std::string::npos
			|| (pos = line.find("<=>") != std::string::npos)) // not handled anymore.
		{
			newRule.SetName(line);
			newRule.SetProposition(line.substr(0 , pos));
			newRule.SetResult(line.c_str() + pos);

			// additionnal formating (mainly parenthesis spacing)
			formatRule(newRule);
			// Debug Print;
				// std::cout << KYEL "New Rule: ------------" KRESET << std::endl
				// 	<< "Name: " << newRule.GetName() << std::endl
				// 	<< "Proposition: " << newRule.GetProposition() << std::endl
				// 	<< "Result: " << newRule.GetResult() << std::endl;

			// we got the rule, now we add it to the conclusional facts.
			std::string result = newRule.GetResult();
			for (int i = 0; result[i]; i++)
			{
				if (result[i] >= 'A' && result[i] <= 'Z')
				{
					file.AllFacts.find(result[i])->second->LinkedRules.push_back(newRule);
					// std::cout << KGRN "Rule added to " KRESET << result[i] << std::endl; 
				}
			}
		}
	}
}

void		InputController::formatRule(Rule &newRule)
{
	std::size_t			tmp_pos;
	std::string			proposition;
	std::string			result;
	std::string			name;

	proposition = newRule.GetProposition();
	// format "("
	tmp_pos = proposition.find("(", 0);
	while (tmp_pos != std::string::npos)
	{
		proposition.insert(tmp_pos + 1, 1, ' ');
		proposition.insert(tmp_pos, 1, ' ');
		newRule.SetProposition(proposition);
		tmp_pos = proposition.find("(", tmp_pos + 2); // +2 cause space was added in front.
	}
	// format ")"
	tmp_pos = proposition.find(")", 0);
	while (tmp_pos != std::string::npos)
	{
		proposition.insert(tmp_pos + 1, 1, ' ');
		proposition.insert(tmp_pos, 1, ' ');
		newRule.SetProposition(proposition);
		tmp_pos = proposition.find(")", tmp_pos + 2); // +2 cause space was added in front.
	}

	// destroy parenthesis in result
	result = newRule.GetResult();
	std::replace(result.begin(), result.end(), '(', ' ');
	std::replace(result.begin(), result.end(), ')', ' ');
	newRule.SetResult(result);

	// destroy "(" parenthesis in name's conclusion
	name = newRule.GetName();
	tmp_pos = name.find("=>", 0);
	std::replace(name.begin() + tmp_pos, name.end(), '(', ' ');
	std::replace(name.begin() + tmp_pos, name.end(), ')', ' ');
	newRule.SetName(name);

	// std::cout << newRule.GetResult() << std::endl;
	// std::cout << KMAG "Rule fomatted: [" << newRule.GetProposition() << KRESET << std::endl;
}

/*
**	Stock the token with the whole query line into the global struct.
*/

void		InputController::collectQuery(t_ExpSysFile &file)
{
	for (std::list<t_token>::iterator it = file.TokenList.begin();
			it != file.TokenList.end();
			it++)
	{
		if ((*it).TokenType == QUERY)
		{
			file.Query = (*it).Value;
		}
	}
}
