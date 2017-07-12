#include "../includes/ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Lexer Parser												//
//																//
// ------------------------------------------------------------	//
/*
**	The file has been opened and put into _expertSystemDatas->FileString;
**	We will now lex this file in token, and parse those tokens.
*/

void		InputController::LexParse()
{
	if (!_initialized)
	{
		throw CustomException(KRED "InputController class not initialized!"
			" Use InputController::Init([...]) first!" KRESET);
	}
	else
	{
		// STEP 1: cut the file in tokens
		lexInput();
		// STEP 2: parse those token to give them a type.
		parseTokenTypes();
		// STEP 3 : are any of these token type invalid?
		if (tokenTypeCheck() != 0)
			throw CustomException(KRED "InputController: Parser: invalid token." KRESET);
		// STEP 4 : are they correctly positionned in their lines?
		if (checkTokenPositions() != 0)
			throw CustomException(KRED "InputController: Parser: invalid token position." KRESET);
		// STEP % : are there forbidden duplicates?
		if (checkTokenDuplicates() != 0)
			throw CustomException(KRED "InputController: Parser: missing or duplicate token." KRESET);
	}
}

/*
**	The lexer will only cut the file in small tokens, that will be 
**	analyzed during the parsing.
**	We will also get the positions of those tokens.
*/

void				InputController::lexInput()
{
	std::string				line;
	std::stringstream		progStream(_expertSystemDatas->FileString);
	char 					*splittedString;
	int						lineNumber;
	int						numberInLine;
	t_token					curToken;

	lineNumber = 0;
	numberInLine = 0;
	while (getline(progStream, line))
	{
		for (splittedString = std::strtok((char *)line.c_str(), " \t");
			splittedString != NULL; splittedString = strtok (NULL, " \t"))
		{
			curToken.Value = splittedString;
			curToken.LineNumber = lineNumber;
			curToken.NumberInLine = numberInLine;
			_tokenList.push_back(curToken);
			numberInLine += 1;
		}
		lineNumber += 1;
		numberInLine = 0;
	}
}

/*
**	The lexer cut the file in tokens, we will now parse these token to set a TYPE.
**	For this we will check if they correspond to our
**	authorized types of symbols and values. -> semantical check.
*/

void		InputController::parseTokenTypes()
{
	for (std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		(*it).ExitParenthesis = false;
		(*it).EntryParenthesis = false;
		// regexes for VALUE, SYMBOL, FACT, QUERY.
		if (std::regex_match((*it).Value, std::regex("^!?\\(?[A-Z]\\)?$")))
		{
			(*it).TokenType = FACT;
			// CHECKING FOR PARENTHESIS SIDE - Entry or exit ?
			if ((*it).Value.find("(") != std::string::npos)
				(*it).EntryParenthesis = true;
			if ((*it).Value.find(")") != std::string::npos)
				(*it).ExitParenthesis = true;
		}
		else if (std::regex_match((*it).Value, std::regex("^[+|^]$|^=>$|^<=>$")))
		{
			(*it).TokenType = SYMBOL;
		}
		else if (std::regex_match((*it).Value, std::regex("^=[A-Z]*$")))
		{
			(*it).TokenType = INIT_FACTS;
		}
		else if (std::regex_match((*it).Value, std::regex("^\\?[A-Z]+$")))
		{
			(*it).TokenType = QUERY;
		}
		else
		{
			(*it).TokenType = ERROR;
		}
	}
	// Debug print: Display token and their stats.
	printf(KYEL "Tokenized file: --------------------------%s\n", KRESET);
	for(std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		printf("token : line %d col %d -", (*it).LineNumber,(*it).NumberInLine);
		if ((*it).TokenType == FACT)
			printf(" type = FACT");
		else if ((*it).TokenType == SYMBOL)
			printf(" type = SYMBOL");
		else if ((*it).TokenType == INIT_FACTS)
			printf(" type = INIT_FACTS");
		else if ((*it).TokenType == QUERY)
			printf(" type = QUERY");
		else if ((*it).TokenType == ERROR)
			printf(" type = %s*ERROR*%s", KMAG, KRESET);
		if ((*it).EntryParenthesis == true)
			printf(" - ENTRY P");
		else if ((*it).ExitParenthesis == true)
			printf(" - EXIT P");
		printf(" : [%s %s %s]\n", KYEL, (*it).Value.c_str(), KRESET);
	}
}

/*
**	First pass of check : everything has been tokenized.
**	if some of these token are ERROR, we stop here.
*/

int					InputController::tokenTypeCheck()
{
	int		nbOfErrors = 0;

	for(std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		if ((*it).TokenType == ERROR)
		{
			nbOfErrors += 1;
			std::cout << KRED "Line " << (*it).LineNumber << " col "
			<< (*it).NumberInLine << ": Invalid syntax: \""
			<< (*it).Value << "\"" KRESET << std::endl;
		}
	}
	if (nbOfErrors != 0)
	{
		return (-1);
	}
	return (0); // All green;
}

/*
**	Second pass on the tokens: are they rightly placed?
**	For example, we cannot have an symbol at the start of a line.
*/

int				InputController::checkTokenPositions()
{
	int								nbOfErrors = 0;
	std::list<t_token>::iterator	next;

	for (std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		// next = it++;
		next = it;
		next++;
		// ------ SYMBOLS position check;
		// check for symbol at start of line.
		if ((*it).NumberInLine == 0 && (*it).TokenType == SYMBOL)
		{
			nbOfErrors += 1;
			std::cout << KRED "Line " << (*it).LineNumber << " col "
			<< (*it).NumberInLine << ": symbol cannot be first on line: \""
			<< (*it).Value << "\"" KRESET << std::endl;
		}
		// check for solo SYMBOL on end of line.
		if ((*it).TokenType == SYMBOL
			&& ((next != _tokenList.end() && (*it).LineNumber != (*next).LineNumber)
			|| next == _tokenList.end()))
		{
			nbOfErrors += 1;
			std::cout << KRED "Line " << (*it).LineNumber << " col "
			<< (*it).NumberInLine << ": symbol cannot finish line: \""
			<< (*it).Value << "\"" KRESET << std::endl;
		}
		// check for two SYMBOLs following each other
		if ((*it).TokenType == SYMBOL && next != _tokenList.end()
			&& (*it).LineNumber == (*next).LineNumber
			&& (*next).TokenType == (*it).TokenType)
		{
			nbOfErrors += 1;
			std::cout << KRED "Line " << (*it).LineNumber << " col "
			<< (*it).NumberInLine << ": two symbols cannot be consecutive: \""
			<< (*it).Value << "\"" KRESET << std::endl;
		}
		// ------ FACT position check;
		// check for two consecutive facts in rule.
		if ((*it).TokenType == FACT && next != _tokenList.end()
			&& (*it).LineNumber == (*next).LineNumber
			&& (*next).TokenType == (*it).TokenType)
		{
			nbOfErrors += 1;
			std::cout << KRED "Line " << (*it).LineNumber << " col "
			<< (*it).NumberInLine << ": two facts cannot be consecutive in rule: \""
			<< (*it).Value << "\"" KRESET << std::endl;
		}
	}
	if (nbOfErrors != 0)
	{
		return (-1);
	}
	return (0); // All green;
}

/*
**	There can only be one line of INIT_FACTS, and one line of QUERY.
*/

int			InputController::checkTokenDuplicates()
{
	int								nbOfErrors = 0;
	int								nbInitFacts = 0;
	int								nbQueries = 0;
	std::list<t_token>::iterator	next;

	for (std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		if ((*it).TokenType == INIT_FACTS)
		{
			nbInitFacts += 1;
		}
		if ((*it).TokenType == QUERY)
		{
			nbQueries += 1;
		}
	}
	if (nbInitFacts > 1)
	{
		nbOfErrors += 1;
		std::cout << KRED "Parser error: There can only be"
			" one line of fact initialization." KRESET << std::endl;
	}
	if (nbQueries == 0)
	{
		nbOfErrors += 1;
		std::cout << KRED "Parser error: Missing a line of query." KRESET << std::endl;
	}
	if (nbQueries > 1)
	{
		std::cout << KRED "Duplicate error: There can only be"
			" one line of query." KRESET << std::endl;
	}
	if (nbOfErrors != 0)
	{
		return (-1);
	}
	return (0); // All green;
}
