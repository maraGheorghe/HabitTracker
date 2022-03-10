#pragma once
#include "Category.h"

class Habit {
private:

	int ID;
	string name;
	string description;
	int categoryID;

public:

	Habit() {}
	
	Habit(const string& name, const string& description, int categoryID) : name{ name }, description{ description }, categoryID{ categoryID } {}

	Habit(int ID, const string& name, const string& description, int categoryID) {
		this->ID = ID;
		this->name = name;
		this->description = description;
		this->categoryID = categoryID;
	}

	int get_ID() {
		return ID;
	}

	string get_name() {
		return name;
	}

	string get_description() {
		return description;
	}

	int get_Category() {
		return categoryID;
	}

	void set_name(const string& n) {
		this->name = n;
	}

	void set_description(const string& d) {
		this->description = d;
	}

	void set_Category(int c) {
		this->categoryID = c;
	}

	~Habit() {};

	Habit(const Habit& h1) { ID = h1.ID; name = h1.name; description = h1.description; categoryID = h1.categoryID; }

	Habit& operator=(const Habit& other){
		if (this != &other) { 
			ID = other.ID;
			name = other.name;
			description = other.description;
			categoryID = other.categoryID;
		}
		return *this;
	}

	ostream& operator<<(ostream& os) {
		os << ID << " " << name << " " << description << " " << categoryID;
	}

	string toString() {
		return this->name + " -> " + this->description;
	}
};
