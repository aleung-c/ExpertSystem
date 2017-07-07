#ifndef MAINCONTROLLER_HPP
# define MAINCONTROLLER_HPP

/*
**	Class that will handle all other class controllers instance.
**	-> the top central controller that will activate the sub classes methods.
*/

class MainController
{
	public:
		t_ExpertSystem		*ExpertSystemDatas;

		// TODO:
		//Parser				Parser;

		MainController(t_ExpertSystem &expertSystemDatas);
		~MainController();
	
};

#endif