#pragma once
#include "Habit.h"
#include "Date.h"
class ToDo : public Habit
{
private:
	int idToDo;
	bool done;
	Date date;

public:

	ToDo() : Habit(1, "a", "a", 1) {}

	ToDo(const string& name, const string& description, int categoryID, bool done, Date date) : Habit(name, description, categoryID), idToDo{ 0 }, done{ done }, date{ date } {} 

	ToDo(int idHabit, const string& name, const string& description, int categoryID, bool done, Date date) : Habit(idHabit, name, description, categoryID), idToDo{ 0 }, done{ done }, date{ date } {}

	ToDo(int idToDo, int idHabit, const string& name, const string& description, int categoryID, bool done, Date date) : Habit(idHabit, name, description, categoryID), idToDo{ idToDo }, done{ done }, date{ date } {}

	int getId() {
		return idToDo;
	}

	bool getDone() {
		return done;
	}

	Date getDate() {
		return date;
	}

	void setId(int id) {
		this->idToDo = id;
	}

	void setDone(bool done) {
		this->done = done;
	}

	void setDate(Date date) {
		this->date = date;
	}
};
