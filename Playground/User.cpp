#pragma once;
#include <iostream>
#include <string>

using namespace std;
class User {
public:
	string record = "0-0";
	int wins = 0;
	int losses = 0;
	string name = "";
	int gamesPlayed = 0;
	int loc = -1;
	int score = 0;
	double averageScore = -1;


	void setRecord()
	{
		record = to_string(wins) + "-" + to_string(losses);
		setAverageScore();
	}

	void setAverageScore()
	{
		averageScore = score / gamesPlayed;
	}
	
	double winPercent()
	{
		double winPercent = wins / gamesPlayed;
		winPercent *= 100;
		return winPercent;
	}

};