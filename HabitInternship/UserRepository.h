#pragma once
//#include "postgresql/libpq-fe.h"
#include "User.h"
#include "Date.h"
#include <pqxx/pqxx>

class UserRepository
{
private:
	Date parseDate(string s);
public:
	UserRepository() {}
	void save(User user);
	void remove(User user);
	User findOne();
};

