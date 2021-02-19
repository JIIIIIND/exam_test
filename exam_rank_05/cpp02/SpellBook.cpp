#include "SpellBook.hpp"

SpellBook::SpellBook() {}
SpellBook::~SpellBook()
{
	std::vector<ASpell *>::iterator begin = lst.begin();
	std::vector<ASpell *>::iterator end = lst.end();

	while (begin != end);
	{
		delete (*begin);
		begin++;
	}
}

void SpellBook::learnSpell(ASpell *spell)
{
	std::vector<ASpell *>::iterator begin = lst.begin();
	std::vector<ASpell *>::iterator end = lst.end();

	while (begin != end)
	{
		if ((*begin)->getName() == spell->getName())
			return ;
		begin++;
	}
	lst.push_back(spell->clone());
}

void SpellBook::forgetSpell(std::string const &spell)
{
	std::vector<ASpell *>::iterator begin = lst.begin();
	std::vector<ASpell *>::iterator end = lst.end();

	while (begin != end)
	{
		if ((*begin)->getName() == spell)
		{
			lst.erase(begin);
			return ;
		}
		begin++;
	}
}

ASpell *SpellBook::createSpell(std::string const &spell)
{
	std::vector<ASpell *>::iterator begin = lst.begin();
	std::vector<ASpell *>::iterator end = lst.end();

	while (begin != end)
	{
		if ((*begin)->getName() == spell)
			return (*begin);
		begin++;
	}
	return (NULL);
}
