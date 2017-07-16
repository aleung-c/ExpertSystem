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
		void					LexParse();
		void					FillValues();
		void					fillFactsWithMap();


		// Information
		std::map<char, Fact *>	getAllFacts();
		void					print();

	private:
		bool					_initialized;
		t_ExpertSystem			*_expertSystemDatas;
		int						_argc;
		char					**_argv;		
		std::ifstream			_currentFile;

		// File Opening
		int						checkArgs();
		void					printUsage();
		std::string				readFromFile(std::string path);

		// Lexer Parser
		std::list<t_token>		_tokenList; // local list of tokens.

		void					lexInput();
		void					parseTokenTypes();
		int						tokenTypeCheck();
		int						checkTokenPositions();
		int						checkTokenDuplicates();
		void					printTokens();

		void					collectFacts();
		void					printFacts();

		void					collectRules();
};

#endif
