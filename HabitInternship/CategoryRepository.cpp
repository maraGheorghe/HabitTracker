#include "pch.h"
#include "CategoryRepository.h"

vector<Category> CategoryRepository::find_all_category() {
	vector<Category> all_categories;
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_all_categories", "select * from categories");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("find_all_categories");
	pq.commit();
	for (auto row : res)
		all_categories.push_back({ row[0].as<int>(), row[1].as<string>(), row[2].as<int>() });
	return all_categories;
}

Category CategoryRepository::find_category(string name) {
	pqxx::connection conn{ "postgresql://postgres:parola@localhost:5432/Habits" };
	conn.prepare("find_category", "select * from categories where name like $1");
	pqxx::work pq(conn);
	auto res = pq.exec_prepared("find_category", name);
	pq.commit();
	return Category(res[0][0].as<int>(), res[0][1].as<string>(), res[0][2].as<int>());
}
