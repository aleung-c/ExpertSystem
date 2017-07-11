#ifndef MAINCONTROLLER_HPP
# define MAINCONTROLLER_HPP

# include "ExpertSystem.hpp"

/*
**	Class that will handle all other class controllers instance.
**	-> the top central controller that will activate the sub classes methods.
*/

class MainController
{
	public:
		t_ExpertSystem		*ExpertSystemDatas;

		InputController		InputController;

		MainController(t_ExpertSystem &expertSystemDatas);
		~MainController();

		void				Run(int argc, char **argv);
	
};

#endif