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
		printFacts(file); //
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
	std::smatch						matches;
	char							factChar;
	std::string						specialLineStr;


	for (std::list<t_token>::iterator it = file.TokenList.begin();
			it != file.TokenList.end();
			it++)
	{
		if ((*it).TokenType == FACT)
		{
			if (std::regex_match((*it).Value, matches,
				std::regex("^!?\\(?([A-Z])\\)?$")))
			{
				factChar = matches[1].str()[0];
				// std::cout << "captured: '" << factChar << "'\n";
				if (file.AllFacts.find(factChar)
						== file.AllFacts.end())
				{
					newFact = new Fact();
					newFact->SetName(factChar);
					newFact->SetValue(false);
					file.AllFacts[factChar] = newFact;
				}
			}
		}
		// parse init facts and query line for unruled facts.
		if ((*it).TokenType == INIT_FACTS || (*it).TokenType == QUERY)
		{
			specialLineStr = (*it).Value;
			for (int i = 0; specialLineStr[i]; i++)
			{
				if (specialLineStr[i] >= 'A' && specialLineStr[i] <= 'Z')
				{
					factChar = specialLineStr[i];
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
**
**	I decided to reparse the whole string file to get the rules.
**	Its more easy.
*/

void	InputController::collectRules(t_ExpSysFile &file)
{
	std::string				line;
	std::stringstream		progStream(file.Str);
	// char 					*splittedString;
	std::size_t				pos;
	Rule					newRule;

	//	Ill search each rules, and insert them into the corresponding facts
	//	thanks to the map container.
	while (getline(progStream, line))
	{
		if ((pos = line.find("=>")) != std::string::npos
			|| (pos = line.find("<=>") != std::string::npos))
		{
			// we are in a valid rule line.
			newRule.SetName(line);
			newRule.SetProposition(line.substr(0 , pos)); // newRule.GetProposition().assign(line.c_str(), pos);  ça convient mieux pour moi, dis moi si ça pose un probleme :)
			newRule.SetResult(line.c_str() + pos); // newRule.GetResult().assign(&(line[pos]), line.size() - pos);
			
			std::cout << KYEL "New Rule: ------------" KRESET << std::endl
				<< "Name: " << newRule.GetName() << std::endl
				<< "Proposition: " << newRule.GetProposition() << std::endl
				<< "Result: " << newRule.GetResult() << std::endl;

			// we got the rule, now we add it to the conclusional facts.
			int i = 0;
			const char *result = newRule.GetResult().c_str();
			while (result[i])
			{
				if (result[i] >= 'A' && result[i] <= 'Z')
				{
					file.AllFacts.find(result[i])->second->LinkedRules.push_back(newRule);
					std::cout << KGRN "Rule added to " KRESET << result[i] << std::endl; 
				}
				i++;
			}
		}
	}
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
