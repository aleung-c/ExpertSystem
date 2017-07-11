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
		// [...]
	}
}
