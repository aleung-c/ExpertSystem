#include "../includes/ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	Constructor / destructor									//
//																//
// ------------------------------------------------------------	//

MainController::MainController(t_ExpertSystem &expertSystemDatas)
{
	ExpertSystemDatas = &expertSystemDatas; // publicly available.
	std::cout << KGRN "MainController:: ----- initialized." KRESET << std::endl;
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
		InputController.LexParse();
		InputController.FillValues();
	}
	catch (CustomException &e)
	{
		std::cout << e.what() << std::endl;
		exit(-1);
	}
}
