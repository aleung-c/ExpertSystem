#include "ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Debug Information											//
//																//
// ------------------------------------------------------------	//
/*
**	Methods for better development 
**
*/

void		InputController::print(void)
{
	for(std::map<char, Fact *>::const_iterator it = _expertSystemDatas->AllFacts.begin();
    	it != _expertSystemDatas->AllFacts.end(); ++it)
	{
    	std::cout << (*it->second);
	}
}
