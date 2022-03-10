#include "pch.h"
#include "UserRepository.h"

void UserRepository::save(User user) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("add_user", "insert into users (firstname, lastname, birthday) values ($1, $2, $3)");
	pqxx::work pq(conn);
	pq.exec_prepared("add_user", user.getFirstName(), user.getLastName(), user.getBirthday().toDatabase());
	pq.commit();
}

void UserRepository::remove(User user){
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("remove_from_users", "delete from users where id = $1;");
	pqxx::work pq(conn);
	pq.exec_prepared("remove_from_users", user.getId());
	pq.commit();
}

User UserRepository::findOne() {

	pqxx::connection c{ "postgresql://postgres:parola@localhost:5432/Habits" };
	pqxx::work txn{ c };
	pqxx::result r{ txn.exec("SELECT * FROM users limit 1") };
	auto row = r[0];
	auto dat = row[3].as<string>();
	User user = User(row[0].as<int>(), row[1].as<string>(), row[2].as<string>(), parseDate(row[3].as<string>()));
	txn.commit();
	return user;
}

Date UserRepository::parseDate(string s) {
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
