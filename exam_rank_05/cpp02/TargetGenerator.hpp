#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include "ATarget.hpp"
# include <vector>

class	TargetGenerator
{
	private:
		std::vector<ATarget *> lst;
		TargetGenerator(TargetGenerator const &ref);
		TargetGenerator &operator=(TargetGenerator const &ref);
	public:
		TargetGenerator();
		~TargetGenerator();
		void learnTargetType(ATarget *target);
		void forgetTargetType(std::string const &name);
		ATarget *createTarget(std::string const &name);
};

#endif
