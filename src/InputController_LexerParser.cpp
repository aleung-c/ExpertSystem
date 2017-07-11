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
		lexInput();
		parseTokenTypes();
		if (tokenTypeCheck() != 0)
			throw CustomException("InputController: Parser: invalid token.");
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
**	authorized types of operands and values. -> semantical check.
*/

void		InputController::parseTokenTypes()
{
	for(std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		(*it).ExitParenthesis = false;
		(*it).EntryParenthesis = false;
		// regexes for VALUE, OPERAND, FACT, QUERY.
		if (std::regex_match((*it).Value, std::regex("^!?\\(?[A-Z]\\)?$")))
		{
			(*it).TokenType = VALUE;
			// CHECKING FOR PARENTHESIS SIDE - Entry or exit ?
			if ((*it).Value.find("(") != std::string::npos)
				(*it).EntryParenthesis = true;
			if ((*it).Value.find(")") != std::string::npos)
				(*it).ExitParenthesis = true;
		}
		else if (std::regex_match((*it).Value, std::regex("^[+|^]$|^=>$|^<=>$")))
		{
			(*it).TokenType = OPERAND;
		}
		else if (std::regex_match((*it).Value, std::regex("^=[A-Z]*$")))
		{
			(*it).TokenType = FACT;
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
	printf("Tokenized file: --------------------------\n");
	for(std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		printf("token : line %d col %d -", (*it).LineNumber,(*it).NumberInLine);
		if ((*it).TokenType == VALUE)
			printf(" type = VALUE");
		else if ((*it).TokenType == OPERAND)
			printf(" type = OPERAND");
		else if ((*it).TokenType == FACT)
			printf(" type = FACT");
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
**	first pass of check : everything has been tokenized.
**	if some of these token are ERROR, we stop here.
*/

int					InputController::tokenTypeCheck()
{
	int nbOfErrors = 0;

	for(std::list<t_token>::iterator it = _tokenList.begin(); it != _tokenList.end() ; it++)
	{
		if ((*it).TokenType == ERROR)
		{
			nbOfErrors += 1;
			std::cout << "Line " << (*it).LineNumber << " col "
			<< (*it).NumberInLine << ": Invalid syntax: \""
			<< (*it).Value << "\"" << std::endl;
		}
	}
	if (nbOfErrors != 0)
	{
		return (-1);
	}
	return (0); // All green;
}