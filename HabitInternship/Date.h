#pragma once
#include <string>
using std::string;

class Date
{
private:
	int day;
	int year;
	int mounth;

public:
	Date(int day, int mounth, int year) : day{ day }, mounth{ mounth }, year{ year } {}
	Date() {}

	int getDay() {
		return day;
	}

	int getMounth() {
		return mounth;
	}

	int getYear() {
		return year;
	}

	void setDay(int day) {
		this->day = day;
	}

	void setMounth(int mounth) {
		this->mounth = mounth;
	}

	void setYear(int year) {
		this->year = year;
	}

	int days(Date date) {
		return (- date.getYear() + this->year) * 365 + (- date.getMounth() + this->mounth) * 30 - date.getDay() + this->day;
	}

	Date operator-(const Date& date) {
		int days = date.day - this->day;
		return Date{days, 0, 0};
	}

	string toString() {
		return string{ std::to_string(day) + '/' + std::to_string(mounth) + '/' + std::to_string(year) };
	}

	string toDatabase() {
		return string{ std::to_string(year) + '-' + std::to_string(mounth) + '-' + std::to_string(day) };
	}
};

