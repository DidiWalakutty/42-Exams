#pragma once

#include <iostream>

class Warlock
{
	private:
		std::string _name;
		std::string _title;

	public:
		Warlock() = delete;
		Warlock(const Warlock& copy) = delete;
		Warlock& operator=(const Warlock& assign) = delete;
		Warlock(const std::string& name, const std::string& title);
		~Warlock();
		
		const std::string& getName() const;
		const std::string& getTitle() const;

		void introduce() const;
		void setTitle(const std::string &title);
};