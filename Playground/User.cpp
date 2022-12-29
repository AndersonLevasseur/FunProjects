#include <iostream>
#include <string>

using namespace std;
class User {
	string name;
	string record;
	int wins;
	int losses;
	int gamesPlayed;

	void setName(string newName) 
	{
		name = newName;
	}

	void setRecord()
	{
		record = to_string(wins) + "-" + to_string(losses);
	}
};