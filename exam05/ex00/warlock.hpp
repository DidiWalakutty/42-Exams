#pragma once

#include <iostream>

class Warlock
{
	private:
		std::string _name;
		std::string _title;

	public:
		// Warlock() = default;									// needed?
		Warlock(const std::string& name, const std::string& title);
		// Warlock(const Warlock& copy) = default;					// needed?
		// Warlock& operator=(const Warlock& assign) = default;	// needed?
		~Warlock();
		
		const std::string& getName() const;
		const std::string& getTitle() const;

		void introduce() const;
		void setTitle(const std::string &title);
};