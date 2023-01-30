#include "User.cpp"
#include <vector>
using namespace std;

class Leaderboard
{
private:
	string leaderboardName;
	vector <User> users;
	int longestName = 0;
	int longestWinDigs = 0;
	int longestGamesPlayedDigs = 0;
public:
	// gives leaderboard name
	void initLeaderboard(string name)
	{
		//odd number check
		if (name.length() % 2 == 1)
		{
			name.push_back('!');
		}

		leaderboardName = name;
	}

	// adds user to users vector
	void addUser(User newUser)
	{
		users.push_back(newUser);
		
		if (newUser.name.length() > longestName)
		{
			longestName = newUser.name.length();
		}
		
		if ((log10(newUser.wins) + 1) > longestWinDigs)
		{
			longestWinDigs = log10(newUser.wins) + 1;
		}

		if ((log10(newUser.gamesPlayed) + 1) > longestGamesPlayedDigs)
		{
			longestGamesPlayedDigs = log10(newUser.gamesPlayed) + 1;
		}

	}

	// prints the leaderboard to the console
	void printBoard(int sortBy)
	{
		//checks to make sure users exist
		if (!users.size() > 0)
		{
			throw "No users in leaderboard";
		}

		vector <User> sorted = sortUsers(sortBy);
		// vector sorted to greatest value first, reversing it
		reverse(sorted.begin(), sorted.end());

		// formatting for looks - 17
		string titleStuff = "";
		string titleCout;
		int i = 0;
		int width = 31;

		

		/*while (i < (17 - leaderboardName.size()) / 2)
		{
			titleStuff += "*";
			i++;
		}*/

		titleCout += titleStuff + leaderboardName + titleStuff;
		titleCout += "\n";

		string headerCout;
		string headerBuffer;
		for (int i = 0; i < 4; i++)
		{
			string headerName;
			switch (i)
			{
			case 0:
				headerName = "Win%";
				break;
			case 1:
				headerName = "Name";
				break;
			case 2:
				headerName = "Wins";
				break;
			case 3:
				headerName = "Game#";
				break;
			}
			headerCout += headerBuffer + headerName;
		}
		headerCout += headerBuffer + "\n";
	}

	vector <User> sortUsers(int sortBy)
	{
		vector <User> sort = users;
		int changes = 1;
		//User compareUser = nameSort.at(0);

		while (changes != 0)
		{
			for (int i = 0; i < sort.size() - 1; i++)
			{
				User tempUser = sort.at(i + 1);
				int compVal = 0;
				changes = 0;
				double val1_double;
				double val2_double;

				int val1_int;
				int val2_int;

				switch (sortBy)
				{
				case 0:
					//win percent
					val1_double = sort.at(i).winPercent();
					val2_double = sort.at(i + 1).winPercent();
					if (val2_double > val1_double)
					{
						compVal = 1;
						changes++;
					}
					break;
				case 1:
					//name
					compVal = sort.at(i).name.compare(sort.at(i + 1).name);

					break;
				case 2:
					//wins
					val1_int = sort.at(i).wins;
					val2_int = sort.at(i + 1).wins;
					if (val2_int > val1_int)
					{
						compVal = 1;
						changes++;
					}
				case 3:
					//Games Played
					val1_int = sort.at(i).gamesPlayed;
					val2_int = sort.at(i + 1).gamesPlayed;
					if (val2_int > val1_int)
					{
						compVal = 1;
						changes++;
					}
				default:
					throw "no sort";
					break;
				}
				if (compVal > 0)
				{
					// compVal is bigger
					sort.at(i + 1) = sort.at(i);
					sort.at(i) = tempUser;
					changes++;
				}

			}
		}

		return sort;
	}


};