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
			try
			{
				if ((*it).NotAFile == false)
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
					Game = GameController((*it).Query, InputController.getAllFacts(*it), ExpertSystemDatas->Verbose);
					std::cout << Game;
					Game.run();
				}
			}
			catch (CustomException &e)
			{
				std::cout << std::endl << KRED "Error in File: " KYEL << (*it).Path << KRESET " : " << e.what() << std::endl;
			}
		}
	}
	catch (CustomException &e)
	{
		std::cout << e.what() << std::endl;
		exit(-1);
	}
}
