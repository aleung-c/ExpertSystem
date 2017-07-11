#include "../includes/ExpertSystem.hpp"

int		main(int argc, char **argv)
{
	t_ExpertSystem		ExpertSystemDatas;
	MainController		*MainController;

	MainController = new class MainController(ExpertSystemDatas);
	MainController->Run(argc, argv);
	return (0);
}
