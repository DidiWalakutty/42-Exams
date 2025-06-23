#pragma once

#include <iostream>

class Warlock
{
	private:
		std::string _name;
		std::string _title;

	public:
		Warlock() = delete;									// needed?
		Warlock(const std::string& name, const std::string& title);
		Warlock(const Warlock& copy) = delete;					// needed?
		Warlock& operator=(const Warlock& assign) = delete;	// needed?
		~Warlock();
		
		const std::string& getName() const;
		const std::string& getTitle() const;

		void introduce() const;
		void setTitle(const std::string &title);
};