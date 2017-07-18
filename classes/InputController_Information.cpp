#include "ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Debug Information											//
//																//
// ------------------------------------------------------------	//
/*
**	Methods for better development 
**
*/

void						InputController::print(t_ExpSysFile &file)
{
	for(std::map<char, Fact *>::const_iterator it = file.AllFacts.begin();
    	it != file.AllFacts.end(); ++it)
	{
    	std::cout << (*it->second);
	}
}

std::map<char, Fact *>		InputController::getAllFacts(t_ExpSysFile &file)
{
	return (file.AllFacts);
}
