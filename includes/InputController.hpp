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

		void					Init(t_ExpertSystem *expertSystemDatas, int argc, char **argv);
		void					GetInput();
		void					LexParse();
		void					FillValues();

	private:
		int						checkArgs();
		void					printUsage();

		std::string				ReadFromFile(std::string path);

		t_ExpertSystem			*_expertSystemDatas;
		int						_argc;
		char					**_argv;

		bool					_initialized;

		std::ifstream			_currentFile;
};

#endif
