#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}
TargetGenerator::~TargetGenerator()
{
	std::vector<ATarget *>::iterator begin = lst.begin();
	std::vector<ATarget *>::iterator end = lst.end();

	while (begin != end)
	{
		delete (*begin);
		begin++;
	}
	lst.clear();
}

void TargetGenerator::learnTargetType(ATarget *target)
{
	std::vector<ATarget *>::iterator begin = lst.begin();
	std::vector<ATarget *>::iterator end = lst.end();

	while (begin != end)
	{
		if ((*begin)->getType() == target->getType())
			return ;
		begin++;
	}
	lst.push_back(target->clone());
}

void TargetGenerator::forgetTargetType(std::string const &name)
{
	std::vector<ATarget *>::iterator begin = lst.begin();
	std::vector<ATarget *>::iterator end = lst.end();

	while (begin != end)
	{
		if ((*begin)->getType() == name)
		{
			lst.erase(begin);
			return ;
		}
		begin++;
	}
}

ATarget *TargetGenerator::createTarget(std::string const &name)
{
	std::vector<ATarget *>::iterator begin = lst.begin();
	std::vector<ATarget *>::iterator end = lst.end();

	while (begin != end)
	{
		if ((*begin)->getType() == name)
			return (*begin);
		begin++;
	}
	return (NULL);
}
