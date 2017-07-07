#include "../includes/ExpertSystem.hpp"

MainController::MainController(t_ExpertSystem &expertSystemDatas)
{
	ExpertSystemDatas = &expertSystemDatas;
	std::cout << KGRN "MainController:: ----- initialized." KRESET << std::endl;
}

MainController::~MainController()
{

}
