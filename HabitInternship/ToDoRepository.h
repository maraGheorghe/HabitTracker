#pragma once
#include "Habit.h"
#include "ToDo.h"
#include <vector>
#include <pqxx/pqxx>
using std::vector;

class ToDoRepository {
private:
	int save_sugestion(Habit habit);

public:
	ToDoRepository() {};
	int save_to_do(Habit habit);
	void save_to_do(ToDo toDo);
	void delete_to_do(int ID);
	void done_to_do(int ID);
	void verify_if_habit(Habit habit);
	vector<ToDo> find_all_to_dos();
	int find_score();
	ToDo find_one_to_do(int ID);
	Date parseDate(string s);
	~ToDoRepository() {};
};
