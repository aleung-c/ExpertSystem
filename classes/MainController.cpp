#include "ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Constructor / destructor									//
//																//
// ------------------------------------------------------------	//

MainController::MainController(t_ExpertSystem &expertSystemDatas)
{
	ExpertSystemDatas = &expertSystemDatas; // publicly available.
}

MainController::~MainController()
{

}

// ------------------------------------------------------------	//
//	Main Run method -> Will call other controllers				//
//																//
// ------------------------------------------------------------	//
/*
**	If at some point something goes wrong, a custom exception
**	will be thrown and the program will terminate.
*/

void	MainController::Run(int argc, char **argv)
{
	try
	{
		// I. Input handling
		InputController.Init(ExpertSystemDatas, argc, argv);
		InputController.GetInput();
		for (std::vector<t_ExpSysFile>::iterator it = ExpertSystemDatas->Files.begin();
			it != ExpertSystemDatas->Files.end(); it++)
		{
			std::cout << std::endl << KCYN "------------------------------------------- " KRESET << std::endl;
			std::cout << KCYN "  File: " << (*it).Path << std::endl;
			std::cout << KCYN "------------------------------------------- " KRESET << std::endl;
			InputController.print(*it);
			InputController.LexParse(*it);
			InputController.FillValues(*it);

			std::cout << KYEL "After Input: ------------" KRESET << std::endl;
			InputController.print(*it);
		
			// II. Resolution handling
			Game = GameController((*it).Query, InputController.getAllFacts(*it), ExpertSystemDatas->Verbose);	// first arg is the query needed
			std::cout << Game;												// Once the query, the = and the Proposition (see Rule.cpp l.150) are stored correctly 
			Game.run();													// you can uncomment the RUN ()
		}
	}
	catch (CustomException &e)
	{
		std::cout << e.what() << std::endl;
		exit(-1);
	}
}
