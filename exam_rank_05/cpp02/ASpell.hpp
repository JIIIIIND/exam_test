#ifndef ASPELL_HPP
# define ASPELL_HPP
# include "ATarget.hpp"
# include <iostream>

class ATarget;

class	ASpell
{
	protected:
		std::string	name;
		std::string	effects;
	public:
		ASpell();
		ASpell(std::string const &_name, std::string const &_effects);
		ASpell(ASpell const &ref);
		ASpell &operator=(ASpell const &ref);
		~ASpell();
		std::string const &getName() const;
		std::string const &getEffects() const;
		virtual ASpell *clone() const = 0;
		void	launch(ATarget const &target) const;
};

#endif
