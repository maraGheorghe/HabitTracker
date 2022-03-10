#pragma once
#include "Habit.h"
#include <vector>
#include <pqxx/pqxx>

using std::vector;

class HabitRepository {

public:
	void save_habit(Habit habit);
	vector<Habit> find_all_habits();
	Habit find_habit(int ID);
};
