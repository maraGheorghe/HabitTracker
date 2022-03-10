#pragma once
#include <string>
#include <ostream>
using std::string;
using std::ostream;
class Category {
private:

	int ID;
	string namee;
	int score;

public:
	Category(int ID, string name, int score) {
		this->ID = ID;
		this->namee = name;
		this->score = score;
	}

	int get_ID() {
		return ID;
	}

	string get_name() {
		return namee;
	}


	int get_score() {
		return score;
	}

	void set_name(string n) {
		this->namee = n;
	}


	void set_score(int s) {
		this->score = s;
	}

	~Category() {};

	Category(const Category& c1) { ID = c1.ID; namee = c1.namee; score = c1.score; }

	Category& operator=(const Category& other) {
		if (this != &other) {
			ID = other.ID;
			namee = other.namee;
			score = other.score;
		}
		return *this;
	}

	ostream& operator<<(ostream& os) {
		os << ID << " " << namee << " " << score;
	}
};

