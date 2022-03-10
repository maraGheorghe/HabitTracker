#include "pch.h"
#include "SuggestionsRepository.h"

void SuggestionsRepository::save_suggestion(Habit habit) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("add_suggestion", "insert into suggestions (name, description, categoryID) values ($1, $2, $3)");
	pqxx::work pq(conn);
	pq.exec_prepared("add_suggestion", habit.get_name(), habit.get_description(), habit.get_Category());
	pq.commit();
}

void SuggestionsRepository::delete_suggestion(int ID) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("remove_suggestion", "delete from suggestions where id = $1;");
	pqxx::work pq(conn);
	pq.exec_prepared("remove_suggestion", ID);
	pq.commit();
}

vector<Habit> SuggestionsRepository::find_all_suggestions() {
	vector<Habit> habits;
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	pqxx::work txn{ conn };
	pqxx::result r{ txn.exec("SELECT * FROM suggestions") };
	for (auto row : r) {
		Habit habit = Habit(row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>());
		habits.push_back(habit);
	}
	txn.commit();
	return habits;
}

Habit SuggestionsRepository::find_suggestion(int ID) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_suggestion", "SELECT * FROM suggestions where id = $1");
	pqxx::work pq(conn);
	auto r = pq.exec_prepared("find_suggestion", ID);
	pq.commit();
	auto row = r[0];
	Habit habit = Habit(row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>());
	return habit;
}

vector<Habit> SuggestionsRepository::find_by_category(int categoryID) {
	vector<Habit> habits;
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_suggestions", "SELECT * FROM suggestions WHERE categoryid = $1");
	pqxx::work pq(conn);
	auto r = pq.exec_prepared("find_suggestions", categoryID);
	for (auto row : r) {
		Habit habit = Habit(row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>());
		habits.push_back(habit);
	}
	pq.commit();
	return habits;
}

vector<Habit> SuggestionsRepository::find_all_starting_with(string name)
{
	vector<Habit> habits;
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_suggestions", "SELECT * FROM suggestions WHERE name like $1");
	pqxx::work pq(conn);
	auto r = pq.exec_prepared("find_suggestions", name + "%");
	pq.commit();
	for (auto row : r) {
		Habit habit = Habit(row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>());
		habits.push_back(habit);
	}
	return habits;
}
