#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

# include "ASpell.hpp"
# include <vector>

class	SpellBook
{
	private:
		std::vector<ASpell *> lst;
		SpellBook(SpellBook const &ref);
		SpellBook &operator=(SpellBook const &ref);
	public:
		SpellBook();
		~SpellBook();
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string const &spell);
		ASpell *createSpell(std::string const &spell);
};

#endif
