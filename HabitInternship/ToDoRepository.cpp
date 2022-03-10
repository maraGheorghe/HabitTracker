#include "pch.h"
#include "ToDoRepository.h"

int ToDoRepository::save_to_do(Habit habit) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("add_toDo", "insert into todos (id_habit) values ($1) returning id");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("add_toDo", habit.get_ID());
	pq.commit();
	return res[0][0].as<int>();
}

int ToDoRepository::save_sugestion(Habit habit) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("add_sugestion", "insert into suggestions (name, description, categoryid) values ($1, $2, $3) returning id");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("add_sugestion", habit.get_name(), habit.get_description(), habit.get_Category());
	pq.commit();
	return res[0][0].as<int>();
}

void ToDoRepository::save_to_do(ToDo toDo) {
	auto id = save_sugestion(toDo);
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("add_toDo", "insert into todos (id_habit) values ($1);");
	pqxx::work pq(conn);
	pq.exec_prepared("add_toDo", id);
	pq.commit();
}

void ToDoRepository::delete_to_do(int ID) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("delete_toDo", "delete from todos where id = $1;");
	pqxx::work pq(conn);
	pq.exec_prepared("delete_toDo", ID);
	pq.commit();
}

void ToDoRepository::done_to_do(int ID) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("done_toDo", "update todos set done = true where id = $1;");
	pqxx::work pq(conn);
	pq.exec_prepared("done_toDo", ID);
	pq.commit();
	verify_if_habit(find_one_to_do(ID));
}

void ToDoRepository::verify_if_habit(Habit habit) {
	vector<Date> dates;
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("isHabit", "select date from todos where id_habit = $1 and done = true order by date");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("isHabit", habit.get_ID());
	pq.commit();
	for (auto row : res) 
		dates.push_back(parseDate(row[0].as<string>()));
	if (dates.size() >= 3 && dates[dates.size() - 1].days(dates[0]) / 2 <= dates.size()) {
		conn.prepare("addNewHabit", "insert into habits (name, description, category) values ($1, $2, $3)");
		pqxx::work pg(conn);
		pg.exec_prepared("addNewHabit", habit.get_name(), habit.get_description(), habit.get_Category());
		pg.commit();
	}
}

vector<ToDo> ToDoRepository::find_all_to_dos() {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("findAll", "select t.id, t.id_habit, s.name, s.description, s.categoryid, t.done, t.date from todos t inner join suggestions s on t.id_habit = s.id where done = false;");
	pqxx::work pq{ conn };
	auto res = pq.exec_prepared("findAll");
	pq.commit();
	vector<ToDo> todos;
	for (auto row : res)
		todos.push_back({ row[0].as<int>(), row[1].as<int>(), row[2].as<string>(), row[3].as<string>(), row[4].as<int>(), row[5].as<bool>(), parseDate(row[6].as<string>()) });
	return todos;
}

int ToDoRepository::find_score() {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("score", "select sum(c.score) from categories c inner join suggestions s on c.id = s.categoryid inner join todos t on s.id = t.id_habit where t.done = true; ");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("score");
	pq.commit();
	return res[0][0].as<int>();

}

ToDo ToDoRepository::find_one_to_do(int ID) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find", "select t.id, t.id_habit, s.name, s.description, s.categoryid, t.done, t.date from todos t inner join suggestions s on t.id_habit = s.id where t.id = $1;");
	pqxx::work pq{ conn };
	auto res = pq.exec_prepared("find", ID);
	pq.commit();
	auto row = res[0];
	return ToDo(row[0].as<int>(), row[1].as<int>(), row[2].as<string>(), row[3].as<string>(), row[4].as<int>(), row[5].as<bool>(), parseDate(row[6].as<string>()));
}

Date ToDoRepository::parseDate(string s) {
	string delimiter = "-";
	size_t pos = 0;
	string token;
	vector<int> date(3);
	int i = 2;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		date[i--] = std::stoi(token);
		s.erase(0, pos + delimiter.length());
	}
	date[i] = std::stoi(s);
	return Date(date[0], date[1], date[2]);
}
