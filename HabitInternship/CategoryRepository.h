#pragma once
#include "Category.h"
#include <vector>
#include <pqxx/pqxx>

using std::vector;

class CategoryRepository {
public:
	CategoryRepository() {};
	vector<Category> find_all_category();
	Category find_category(string name);
	~CategoryRepository() {};
};

