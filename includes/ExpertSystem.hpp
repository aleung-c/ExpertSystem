// ------------------------------------------------------------	//
//	Global HPP for Expert System								//
//																//
// ------------------------------------------------------------	//

#ifndef PARTICLESYSTEM_HPP
# define PARTICLESYSTEM_HPP

// Defines for color in shell.
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\x1B[0m"

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iterator>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <random>
# include <algorithm>
# include <math.h>
# include <map>


// ------------------------------------------------------------	//
//	Defines for the Program										//
//																//
// ------------------------------------------------------------	//

# define DEF_VAL_EXAMPLE 0

// ------------------------------------------------------------	//
//	Enum														//
//																//
// ------------------------------------------------------------	//

typedef enum		e_ExampleEnum
{
	VAL1,
	VAL2
}					t_example_enum;

// ------------------------------------------------------------	//
//	Structs														//
//																//
// ------------------------------------------------------------	//

typedef struct			s_ExpertSystem
{



}						t_ExpertSystem;

// ------------------------------------------------------------	//
//	Classes forward declarations								//
//																//
// ------------------------------------------------------------	//

class					MainController;

/*
**	Include for classes. Order matters for dependencies.
*/

# include "../includes/MainController.hpp"

#endif