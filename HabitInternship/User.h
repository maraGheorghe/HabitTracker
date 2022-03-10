#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Habit.h"
#include "Date.h"
#include <ostream>

using std::vector;
using std::string;
using std::ostream;

class User
{
private:
	int id;
	string firstName;
	string lastName;
	Date birthday;
	vector<Habit> habitList;
	vector<Habit> toDoList;
	
public:
	User(string firstName, string lastName, Date birthday) : firstName{ firstName }, lastName{ lastName }, birthday{ birthday } { id = NULL; }
	User(int id, string firstName, string lastName, Date birthday) : id{ id }, firstName { firstName }, lastName{ lastName }, birthday{ birthday } {}

	int getId() {
		return id;
	}

	string getFirstName() {
		return firstName;
	}

	string getLastName() {
		return lastName;
	}

	Date getBirthday() {
		return birthday;
	}

	vector<Habit> getHabits() {
		return habitList;
	}

	vector<Habit> getToDos() {
		return toDoList;
	}

	void setId(int id) {
		this->id = id;
	}

	void setFirstName(string firstName) {
		this->firstName = firstName;
	}

	void setLastName(string lastName) {
		this->lastName = lastName;
	}

	void setBirthday(Date birthday) {
		this->birthday = birthday;
	}

	void setHabits(vector<Habit> habits) {
		this->habitList = habits;
	}
	
	void setToDos(vector<Habit> toDos) {
		this->toDoList = toDos;
	}

	ostream& operator << (ostream& os)
	{
		os << this->id << ' ' << this->firstName << ' ' << this->lastName << ' ' << this->birthday.getDay();
		return os;
	}

	string toString() {
		return "Welcome, " + this->firstName + ' ' + this->lastName + " (" + this->birthday.toString() + ") !" ;
	}
};

