#include "ASpell.hpp"

ASpell::ASpell() {}
ASpell::ASpell(std::string const &_name, std::string const &_effects) :
	name(_name), effects(_effects) {}

ASpell::ASpell(ASpell const &ref) :
	name(ref.name), effects(ref.effects) {}

ASpell &ASpell::operator=(ASpell const &ref)
{
	name = ref.name;
	effects = ref.effects;
	return (*this);
}


ASpell::~ASpell() {}

std::string const	&ASpell::getName() const
{ return (name); }
std::string const	&ASpell::getEffects() const
{ return (effects); }

void	ASpell::launch(ATarget const &target) const
{
	target.getHitBySpell(*this);
}
