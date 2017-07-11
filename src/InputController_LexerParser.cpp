#include "../includes/ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Lexer Parser												//
//																//
// ------------------------------------------------------------	//
/*
**	Right now, it is only one method. It may be separated in several methods
**	according to the needs and lisibility.
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
		// [...]
	}
}