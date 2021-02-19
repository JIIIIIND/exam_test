#include "Warlock.hpp"

Warlock::Warlock(std::string const &_name, std::string const &_title) :
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

void	Warlock::learnSpell(ASpell *_spell)
{
	std::vector<ASpell *>::iterator begin = spells.begin();
	std::vector<ASpell *>::iterator end = spells.end();

	while (begin != end)
	{
		if ((*begin)->getName() == _spell->getName())
			return ;
		begin++;
	}
	spells.push_back(_spell->clone());
}

void	Warlock::forgetSpell(std::string _spell)
{
	std::vector<ASpell *>::iterator begin = spells.begin();
	std::vector<ASpell *>::iterator end = spells.end();

	while (begin != end)
	{
		if ((*begin)->getName() == _spell)
		{
			spells.erase(begin);
			return ;
		}
		begin++;
	}
}

void	Warlock::launchSpell(std::string _spell, ATarget &target)
{
	std::vector<ASpell *>::iterator begin = spells.begin();
	std::vector<ASpell *>::iterator end = spells.end();

	while (begin != end)
	{
		if ((*begin)->getName() == _spell)
		{
			(*begin)->launch(target);
			return ;
		}
		begin++;
	}
}
