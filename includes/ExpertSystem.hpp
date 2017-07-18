// ------------------------------------------------------------	//
//	Global HPP for Expert System								//
//																//
// ------------------------------------------------------------	//

#ifndef PARTICLESYSTEM_HPP
# define PARTICLESYSTEM_HPP

// Defines for color in shell.
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\x1B[0m"

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iterator>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <random>
# include <algorithm>
# include <math.h>
# include <map>
# include <regex>


// ------------------------------------------------------------	//
//	Defines for the Program										//
//																//
// ------------------------------------------------------------	//

# define MAX_FILE_NAME_LEN 50

// ------------------------------------------------------------	//
//	Classes forward declarations								//
//																//
// ------------------------------------------------------------	//

class							Rule;
class							Fact;
class							InputController;
class							GameController;
class							MainController;

// ------------------------------------------------------------	//
//	Typedef forward declarations								//
//				for conveniant purposes							//
// ------------------------------------------------------------	//

typedef std::map<char, Fact *> mapFacts;

// ------------------------------------------------------------	//
//	Enum														//
//																//
// ------------------------------------------------------------	//

typedef enum					e_TokenType
{
	FACT,
	SYMBOL,
	INIT_FACTS,
	QUERY,
	ERROR
}								t_TokenType;

// ------------------------------------------------------------	//
//	Structs														//
//																//
// ------------------------------------------------------------	//

typedef struct					s_token
{
	std::string					Value;
	t_TokenType					TokenType;
	int							LineNumber;
	int							NumberInLine;
	bool						EntryParenthesis;
	bool						ExitParenthesis;
}								t_token;

typedef struct					s_ExpSysFile
{
	std::string					Path;
	std::string					Str;
	std::string					Query;
	std::map<char, Fact *>		AllFacts;
	std::list<t_token>			TokenList;
}								t_ExpSysFile;

typedef struct					s_ExpertSystem
{
	bool						Verbose;
	std::vector<t_ExpSysFile>	Files;
	
}								t_ExpertSystem;



/*
**	Include for classes. Order matters for dependencies.
**	Being the top most class, MainController should always be at
**	the LOWEST position, as it will call all the others.
*/

# include "Rule.hpp"
# include "Fact.hpp"
# include "InputController.hpp"
# include "ExceptionsHandler.hpp"

# include "GameController.hpp"
# include "MainController.hpp"

#endif
