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
		InputController.LexParse();
		InputController.FillValues();

		InputController.print();
		
		// II. Resolution handling
		// std::cout << (InputController.getAllFacts()[0]);
		// Game = GameController("?AB", InputController.getAllFacts());
		// std::cout << Game;
	}
	catch (CustomException &e)
	{
		std::cout << e.what() << std::endl;
		exit(-1);
	}
}
