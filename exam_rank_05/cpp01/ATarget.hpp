#ifndef ATARGET_HPP
#define ATARGET_HPP
# include "ASpell.hpp"
# include <iostream>

class	ASpell;

class	ATarget
{
	protected:
		std::string	type;
	public:
		ATarget();
		ATarget(std::string const &_type);
		ATarget(ATarget const &ref);
		ATarget &operator=(ATarget const &ref);
		~ATarget();
		std::string const &getType() const;
		void setType(std::string const &_type);
		void getHitBySpell(ASpell const &spell) const;
		virtual ATarget *clone() const = 0;
};

#endif
