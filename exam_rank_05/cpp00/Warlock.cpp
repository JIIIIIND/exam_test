#include "Warlock.hpp"

Warlock::Warlock(std::string _name, std::string _title) :
	name(_name), title(_title)
{
	std::cout	<< name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout	<< name << ": My job here is done!" << std::endl;
}

void	Warlock::introduce() const
{
	std::cout	<< name << ": I am " << name << ", " << title << "!" << std::endl;
}

std::string const	&Warlock::getName() const
{ return (name); }

std::string const	&Warlock::getTitle() const
{ return (title); }

void	Warlock::setTitle(const std::string &_title)
{
	title = _title;
}
