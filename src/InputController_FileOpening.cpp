#include "../includes/ExpertSystem.hpp"

// ------------------------------------------------------------	//
//	File Opening												//
//																//
// ------------------------------------------------------------	//
/*
**	Main public method to get the file given in input.
**	This calls the private methods below.
*/

void		InputController::GetInput()
{
	if (checkArgs() != 0)
	{
		throw CustomException(KRED "InputController: Invalid argument\n" KRESET);
	}
	_expertSystemDatas->FileString = ReadFromFile(_argv[1]);
	// debug print;
	std::cout << std::endl << "Opened file (comments cleaned):"
		<< std::endl << _expertSystemDatas->FileString << std::endl;
}

/*
** Check the arguments given to the program (classic C)
*/

int		InputController::checkArgs()
{
	if (!_initialized)
	{
		throw CustomException(KRED "InputController class not initialized!"
			" Use InputController::Init([...]) first!" KRESET);
	}
	else
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

std::string			InputController::ReadFromFile(std::string path)
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
		throw CustomException(KRED "InputController: File opening error" KRESET);
	}
	// actual opening as fstream.
	_currentFile.open(path);
	if (_currentFile.is_open())
	{
		std::cout << KGRN " -- Program file opened" KRESET << std::endl;
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
		throw CustomException(KRED "InputController: File opening error" KRESET);
	}
}
