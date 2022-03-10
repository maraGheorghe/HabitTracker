#pragma once
#include "Habit.h"
#include <vector>
#include <string>
#include <pqxx/pqxx>
using std::string;
using std::vector;

class SuggestionsRepository {

public:
	SuggestionsRepository() {};
	void save_suggestion(Habit habit);
	void delete_suggestion(int ID);
	vector<Habit> find_all_suggestions();
	Habit find_suggestion(int ID);
	vector<Habit> find_by_category(int categoryID);
	vector<Habit> find_all_starting_with(string name);
	~SuggestionsRepository() {};
};

