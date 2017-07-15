#include "../includes/ExpertSystem.hpp"

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

void		InputController::print(void) /* ONLY DEBUG PURPOSE, WILL BE REMOVE */
{
	for(std::map<char, Fact *>::const_iterator it = _expertSystemDatas->AllFacts.begin();
    	it != _expertSystemDatas->AllFacts.end(); ++it)
	{
    	std::cout << (*it->second);
	}
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
