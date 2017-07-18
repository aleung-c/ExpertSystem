#ifndef INPUTCONTROLLER_HPP
# define INPUTCONTROLLER_HPP

# include "ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Input handling class										//
//																//
// ------------------------------------------------------------	//
/*
**	This class will handle everything concerning the input for
**	the expert system.
**
**	Here, I'll get the file, lex it, parse it, and put it into
**	variables that will be processed in the second stage of the program. 
*/

class InputController
{
	public:
		InputController();
		~InputController();

		void					Init(t_ExpertSystem *expertSystemDatas,
										int argc, char **argv);
		void					GetInput();
		void					LexParse(t_ExpSysFile &file);
		void					FillValues(t_ExpSysFile &file);
		void					fillFactsWithMap(t_ExpSysFile &file);

		// Information
		std::map<char, Fact *>	getAllFacts(t_ExpSysFile &file);
		void					print(t_ExpSysFile &file);

	private:
		bool					_initialized;
		t_ExpertSystem			*_expertSystemDatas;
		int						_argc;
		char					**_argv;		
		std::ifstream			_currentFile;

		int						getArgs();

		// File Opening
		int						checkArgs(); // (unused)
		void					printUsage();
		std::string				readFromFile(std::string path);

		// Lexer Parser
		void					lexInput(t_ExpSysFile &file);
		void					parseTokenTypes(t_ExpSysFile &file);
		int						tokenTypeCheck(t_ExpSysFile &file);
		int						checkTokenPositions(t_ExpSysFile &file);
		int						checkTokenDuplicates(t_ExpSysFile &file);
		void					printTokens(t_ExpSysFile &file);

		void					collectFacts(t_ExpSysFile &file);
		void					setInitFacts(t_ExpSysFile &file);
		void					printFacts(t_ExpSysFile &file);

		void					collectRules(t_ExpSysFile &file);
		void					formatRule(Rule &newRule);

		void					collectQuery(t_ExpSysFile &file);
};

#endif
