#ifndef EXCEPTIONSHANDLER_HPP
# define EXCEPTIONSHANDLER_HPP

# include "ExpertSystem.hpp"

class CustomException: public std::runtime_error
{
	public:
		CustomException(const std::string &what_arg);
};

#endif
