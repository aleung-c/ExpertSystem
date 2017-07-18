#include "../includes/ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	File Opening												//
//																//
// ------------------------------------------------------------	//

int			InputController::getArgs()
{
	// basic nb of arg check
	if (_argc < 2)
	{
		printUsage();
		return (-1);
	}
	// for each arg. check if 1 is option, else try to open file.
	for (int i = 1; _argv[i]; i++)
	{
		if (i == 1 && strncmp(_argv[i], "--verbose", 9) == 0) // position 1 : OPTION ONLY
		{
			_expertSystemDatas->Verbose = true;
			std::cout << KYEL "Verbose mode ON" KRESET << std::endl;
			if (_argc == 2)
			{
				std::cout << KRED "InputController: No file to process!" KRESET << std::endl;
				return (-1);
			}
		}
		else // for all other, try to open the file.
		{
			t_ExpSysFile	CurFile;

			if (strnlen(_argv[i], MAX_FILE_NAME_LEN) >= MAX_FILE_NAME_LEN)
			{
				std::cout << KRED "InputController: File name too long" KRESET << std::endl;
				return (-1);
			}
			CurFile.Str = readFromFile(_argv[i]);
			// put char in path string;
			std::string path(_argv[i]);
			CurFile.Path = path;
			_expertSystemDatas->Files.push_back(CurFile);
			std::cout << KGRN "InputController: File opened." KRESET << std::endl;
		}
	}
	return (0);
}

/*
**	Check the arguments given to the program (classic C)
**	Unused now to implement multi files.
*/

int		InputController::checkArgs()
{
	if (_argc != 2)
	{
		printUsage();
		return (-1);
	}
	if (strnlen(_argv[1], MAX_FILE_NAME_LEN) >= MAX_FILE_NAME_LEN)
	{
		std::cout << KRED "InputController: File name too long" KRESET << std::endl;
	}
	return (0);
}

void		InputController::printUsage()
{
	std::cout << std::endl << "Usage: " << _argv[0] << " [file]" << std::endl;
}

/*
**	The arguments seems good, we must now try to open the file.
**	Concerning the comments in the file, they are NOT taken into the string,
**	as we wont use them.
*/

std::string			InputController::readFromFile(std::string path)
{
	std::string		line;
	std::string		ret;
	size_t			commentPosition;
	struct stat		path_stat;

	
	ret = "";
	// Pre checking with stat to check if it is a directory.
	stat(path.c_str(), &path_stat);
	if (S_ISREG(path_stat.st_mode) != 1)
	{
		perror("InputController");
		throw CustomException(KRED "InputController: File opening error" KRESET);
	}
	// actual opening as fstream.
	_currentFile.open(path);
	if (_currentFile.is_open())
	{
		
		while (getline(_currentFile, line))
		{
			// Comment cleaning at reading.
			if ((commentPosition = line.find("#")) != std::string::npos)
			{
				line.erase(commentPosition, line.size());
			}
			ret += line;
			ret += "\n";
		}
		_currentFile.close();
		return (ret);
	}
	else
	{
		perror("InputController: open()");
		perror("InputController");
		throw CustomException(KRED "InputController: File opening error" KRESET);
	}
}
