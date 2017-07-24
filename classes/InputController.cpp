#include "ExpertSystem.hpp"

/*
**	First CPP file for the InputController class
**	Input handling steps are separated in several files.
*/

// ------------------------------------------------------------	//
//	Constructor / destructor									//
//																//
// ------------------------------------------------------------	//

InputController::InputController() : _initialized(false)
{

}

InputController::~InputController()
{

}

// ------------------------------------------------------------	//
//	Initialization												//
//																//
// ------------------------------------------------------------	//

void		InputController::Init(t_ExpertSystem *expertSystemDatas, int argc, char **argv)
{
	if (!expertSystemDatas || !argv)
	{
		throw CustomException("InputController: Initialization error (null ptr error)");
	}
	// set class private local pointers.
	_expertSystemDatas = expertSystemDatas;
	_argc = argc;
	_argv = argv;
	_initialized = true;
}

/*
**	Main public method to get the file given in input.
**	This calls the private methods below.
*/

void		InputController::GetInput()
{
	if (!_initialized)
	{
		throw CustomException(KRED "InputController class not initialized!"
			" Use InputController::Init([...]) first!" KRESET);
	}
	else
	{
		if (getArgs() != 0)
		{
			throw CustomException(KRED "InputController: Invalid argument\n" KRESET);
		}
		
		// debug print;
		// std::cout << KYEL "Opened file (comments cleaned): --------------------" KRESET
		// 	<< std::endl << _expertSystemDatas->FileString << std::endl;
	}
}

void		InputController::PrintFile(t_ExpSysFile &file)
{
	std::stringstream		progStream(file.Str);
	std::string				line;

	while (getline(progStream, line))
	{
		if (line[0])
		{
			std::cout << line << std::endl;
		}
	}
	std::cout << std::endl;
}

// ------------------------------------------------------------	//
//	File Opening												//
//																//
// ------------------------------------------------------------	//

// ----->>	See InputController_FileOpening.cpp

// ------------------------------------------------------------	//
//	Lexer Parser												//
//																//
// ------------------------------------------------------------	//

// ----->>	See InputController_LexerParser.cpp

// ------------------------------------------------------------	//
//	Data collecting												//
//																//
// ------------------------------------------------------------	//

// ----->>	See InputController_FillValues.cpp

// ------------------------------------------------------------	//
//	Information													//
//																//
// ------------------------------------------------------------	//

// ----->>	See InputController_Information.cpp
