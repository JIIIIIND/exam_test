#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>

class	Warlock {
	private:
		std::string		name;
		std::string		title;
		Warlock();
		Warlock(Warlock const &copy);
		Warlock	&operator=(Warlock const &copy);
	public:
		Warlock(std::string const &_name, std::string const &_title);
		~Warlock():
		void	introduce() const;
		std::string const &getName() const;
		std::string const &getTitle() const;
		void	setTitle(std::string const &_title);
};

#endif
