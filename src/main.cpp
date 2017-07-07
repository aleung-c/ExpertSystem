#include "../includes/ExpertSystem.hpp"

int		main(void)
{
	t_ExpertSystem		ExpertSystemDatas;
	MainController		*MainController;

	MainController = new class MainController(ExpertSystemDatas);
	std::cout << KYEL "Hello ExpertSystem!" KRESET << std::endl;
	return (0);
}
