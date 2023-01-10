#include <iostream>
#include <string>

using namespace std;
class User {
public:
	string record;
	int wins = 0;
	int losses = 0;
	string name = "";
	int gamesPlayed = 0;


	void setRecord()
	{
		record = to_string(wins) + "-" + to_string(losses);
	}

	/*void setLocation(int loc)
	{
		location = loc;
		locationChanged++;
	}*/
};