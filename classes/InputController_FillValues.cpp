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

void		InputController::FillValues()
{
	if (!_initialized)
	{
		throw CustomException(KRED "InputController class not initialized!"
			" Use InputController::Init([...]) first!" KRESET);
	}
	else
	{
		collectFacts();
		printFacts(); //
		collectRules();
		
	}
}

/*
**	Will run through each parser token and extract the FACTS datas,
**	to put then into the corresponding objects.
*/

void		InputController::collectFacts()
{
	std::list<t_token>::iterator	next;
	Fact							*newFact;
	std::smatch						matches;
	char							factChar;


	for (std::list<t_token>::iterator it = _tokenList.begin();
			it != _tokenList.end();
			it++)
	{
		if ((*it).TokenType == FACT)
		{
			newFact = new Fact();
			if (std::regex_match((*it).Value, matches,
				std::regex("^!?\\(?([A-Z])\\)?$")))
			{
				factChar = matches[1].str()[0];
				// std::cout << "captured: '" << factChar << "'\n";
				if (_expertSystemDatas->AllFacts.find(factChar)
						== _expertSystemDatas->AllFacts.end())
				{
					newFact->SetName(factChar);
					newFact->SetValue(false);
					_expertSystemDatas->AllFacts[factChar] = newFact;
				}
			}
		}
	}
	this->fillFactsWithMap();
}

/*
**  Fill All Facts with map completed.
*/

void		InputController::fillFactsWithMap( void )
{
	for (std::map<char, Fact *>::iterator it = _expertSystemDatas->AllFacts.begin();
			it != _expertSystemDatas->AllFacts.end();
			++it)
	{
		it->second->SetAllFacts(this->_expertSystemDatas->AllFacts);
	}
}

/*
**	Debug printing method to display FACTS and their status.
*/

void	InputController::printFacts()
{
	std::cout << KYEL "Facts collected: --------------" KRESET << std::endl;
	for (std::map<char, Fact *>::iterator it = _expertSystemDatas->AllFacts.begin();
			it != _expertSystemDatas->AllFacts.end();
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

void	InputController::collectRules()
{
	std::string				line;
	std::stringstream		progStream(_expertSystemDatas->FileString);
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
					_expertSystemDatas->AllFacts.find(result[i])->second->LinkedRules.push_back(newRule);
					std::cout << KGRN "Rule added to " KRESET << result[i] << std::endl; 
				}
				i++;
			}
		}
	}
}
