#include "Warlock.hpp"

Warlock::Warlock(const std::string& name, const std::string& title) :
	_name(name), _title(title)
{
	std::cout << _name << ": This looks like another boring day." << std::endl;
} 

Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!" << std::endl;
}

void Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
}

const std::string& Warlock::getName() const
{
	return _name;
}

const std::string& Warlock::getTitle() const
{
	return this->_title;
}

void Warlock::setTitle(const std::string &title)
{
	this->_title = title;
}

int main()
{
  Warlock const richard("Richard", "Mistress of Magma");
  richard.introduce();
  std::cout << richard.getName() << " - " << richard.getTitle() << std::endl;

  Warlock* jack = new Warlock("Jack", "the Long");
  jack->introduce();
  jack->setTitle("the Mighty");
  jack->introduce();

  delete jack;

  return (0);
}