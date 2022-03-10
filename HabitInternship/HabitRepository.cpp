#include "pch.h"
#include "HabitRepository.h"

void HabitRepository::save_habit(Habit habit){
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("add_habit", "insert into habit (name, description, category) values ($1, $2, $3)");
	pqxx::work pq(conn);
	pq.exec_prepared("add_habit", habit.get_name(), habit.get_description(), habit.get_Category());
	pq.commit();
}

vector<Habit> HabitRepository::find_all_habits() {
	vector<Habit> allHabits;
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_all_habits", "select * from habits");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("find_all_habits");
	pq.commit();
	for (auto row : res)
		allHabits.push_back({row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>()});
	return allHabits; 
}

Habit HabitRepository::find_habit(int ID) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_habit", "select * from habits where id = $1");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("find_habit", ID);
	pq.commit();
	for (auto row : res) 
		return Habit(row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), row[3].as<int>());
	return Habit(0, "", "", 0);
}
