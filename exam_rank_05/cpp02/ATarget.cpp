#include "ATarget.hpp"

ATarget::ATarget() {}

ATarget::ATarget(std::string const &_type) :
	type(_type) {}
ATarget::ATarget(ATarget const &ref) :
	type(ref.type) {}
ATarget	&ATarget::operator=(ATarget const &ref)
{
	type = ref.type;
	return (*this);
}
ATarget::~ATarget() {}

std::string const	&ATarget::getType() const
{ return (type); }

void			ATarget::setType(std::string const &_type)
{
	type = _type;
}

void			ATarget::getHitBySpell(ASpell const &spell) const
{
	std::cout	<< type << " has been " << spell.getEffects() << "!" << std::endl;
}
