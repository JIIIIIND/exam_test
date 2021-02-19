#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <vector>
# include "ASpell.hpp"
# include "ATarget.hpp"
# include "SpellBook.hpp"

class	Warlock {
	private:
		std::string		name;
		std::string		title;
		SpellBook		book;
		Warlock();
		Warlock(Warlock const &copy);
		Warlock	&operator=(Warlock const &copy);
	public:
		Warlock(std::string const &_name, std::string const &_title);
		~Warlock();
		void	introduce() const;
		std::string const &getName() const;
		std::string const &getTitle() const;
		void	setTitle(std::string const &_title);
		void	learnSpell(ASpell *_spell);
		void	forgetSpell(std::string _spell);
		void	launchSpell(std::string _spell, ATarget &target);
};

#endif
