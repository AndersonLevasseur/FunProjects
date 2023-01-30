#include "MastermindGameboard.cpp"
#include "User.cpp"
#include "Leaderboard.cpp"
#include <fstream>
#include <vector>

/* TODO :
* Write a method to search for files
*
*
*/



string files[MAXNUMOFBOARDS];
vector <User> userVect;
int numOfUsers = 0;
Leaderboard all_time;
Leaderboard today;

//seraches for existing board files in fileNames.txt
void fileStartup()
{
	ifstream fileNames;
	string file;
	fileNames.open("boardNames.txt", ios::in);
	if (fileNames.fail())
	{
		throw "Open failed";
	}
	int i = 0;
	while (!fileNames.eof())
	{
		getline(fileNames, file, '\n');
		files[i] = file;
		file = "";
		i++;
	}
	fileNames.close();
}

void userStartup() {
	//User initialize
	ifstream userFile;
	userFile.open("allUsers.txt", ios::in);
	if (userFile.fail())
	{
		throw "Open failed";
	}
	int i = 0;
	numOfUsers = 0;
	User tempUser;
	while (!userFile.eof())
	{
		int j = 0;
		while (j < 6 && !userFile.eof())
		{
			string str;
			getline(userFile, str, '\n');

			switch (j)
			{
			case 0:
				tempUser.name = str;
				break;
			case 1:
				tempUser.wins = stoi(str);
				break;
			case 2:
				tempUser.losses = stoi(str);
				break;
			case 3:
				tempUser.gamesPlayed = stoi(str);
				break;
			case 4:
				tempUser.record = str;
				break;
			case 5:
				tempUser.averageScore = stoi(str);
				break;
			default:
				throw "not a complete user";
				break;
			}
			j++;
		}
		if (tempUser.name.length() > 1)
		{
			tempUser.loc = i;
			if (userVect.size() <= i)
			{
				userVect.push_back(tempUser);
			}
			else
			{
				userVect.at(i) = tempUser;
			}
			i++;
			numOfUsers++;
		}
	}
	userFile.close();
}

void writeUser(User user)
{
	ofstream userFile;
	userFile.open("allUsers.txt", ios::app);
	if (userFile.fail())
	{
		throw "Open failed";
	}

	userFile << user.name << "\n";
	userFile << to_string(user.wins) << "\n";
	userFile << to_string(user.losses) << "\n";
	userFile << to_string(user.gamesPlayed) << "\n";
	userFile << user.record << "\n";
	userFile << to_string(user.averageScore) << "\n";

	userFile.close();
}

void gameEnd(GameBoard& board)
{
	if (board.currentUser.loc == -1)
	{
		board.currentUser.loc = userVect.size() - 1;
		userVect.push_back(board.currentUser);
		gameEnd(board);
		userStartup();
	}
	else
	{
		userVect.at(board.currentUser.loc) = board.currentUser;
	}

	ofstream userFile;
	//Should clear file?
	userFile.open("allUsers.txt");

	if (userFile.fail())
	{
		throw "Couldn't allUser in close()";
	}
	for (int i = 0; i < userVect.size(); i++)
	{
		writeUser(userVect.at(i));
	}
	userFile.close();
}

void setUser(GameBoard& board)
{
	string userStr = board.setUser();
	bool newUser_bool = true;
	for (int i = 0; i < numOfUsers; i++)
	{
		if (userVect.at(i).name == userStr)
		{
			board.currentUser = userVect.at(i);
			board.currentUser.loc = i;
			i = userVect.size();
			newUser_bool = false;
		}
		else
		{
			newUser_bool = true;
		}
	}
	if (newUser_bool)
	{
		User newUser;
		newUser.name = userStr;
		writeUser(newUser);
		board.currentUser = newUser;
	}
}

//doesn't quite work

void leaderBoard(Leaderboard& leaderboard, GameBoard& board)
{
	board.clearBoard();
	string sortByStr;
	string welcomeMessage = "Welcome to the Leaderboard page\nWhat do you want to sort by?\nYour options for inputs are as follows\n*******\nWin Percent\nName\nWins\nGames Played\n*******\nPlease enter inputs exactly as you see them\n";

	int sortByInt;
	cout << welcomeMessage;
	cout << "";
	getline(cin, sortByStr, '\n');
	board.clearBoard();
	//converts sortByStr into sortByint
	{
		if (sortByStr == "Win Percentage" || sortByStr == "win percentage")
		{
			sortByInt = 0;
		}
		else if (sortByStr == "Name" || sortByStr == "name")
		{
			sortByInt = 1;
		}
		else if (sortByStr == "Wins" || sortByStr == "wins")
		{
			sortByInt = 2;
		}
		else if (sortByStr == "Games Played" || sortByStr == "games played")
		{
			sortByInt = 3;
		}
		else
		{
			cout << "Wrong input" << endl;
			cout << "You entered : " << sortByStr << endl;
			cout << "Please press enter to try again";

			string pause;
			getline(cin, pause, '\n');

			return leaderBoard(leaderboard, board);
		}
	}

	leaderboard.printBoard(sortByInt);
	string pause;
	getline(cin, pause, '\n');
	board.clearBoard();
}

void resetGame(GameBoard& board)
{
	//do you want to see the leaderboard
	cout << "Do you want to see the leaderboard?" << endl;
	string leaderboard;
	getline(cin, leaderboard, '\n');

	if (board.yesOrNoQuestion(leaderboard))
	{
		leaderBoard(all_time, board);
	}

	if (board.currentUser.loc == -1)
	{
		userVect.push_back(board.currentUser);
		gameEnd(board);
		userStartup();
	}
	else
	{
		userVect.at(board.currentUser.loc) = board.currentUser;
	}


	board.clearBoard();
	board.resetBoard();
	//include in initBoard?
	{
		board.clearBoard();
		cout << "Same person?" << endl;
		string question;
		getline(cin, question, '\n');
		bool yesNo = board.yesOrNoQuestion(question);
		if (!yesNo)
		{
			setUser(board);
		}
		board.clearBoard();
		board.setMode();
		board.clearBoard();
		board.setCode(true);
		board.clearBoard();
		board.drawBoard();
	}
}

void startUp(GameBoard& board)
{
	fileStartup();
	userStartup();
	all_time.initLeaderboard("LEADERBOARD");
	for(int i = 0; i < userVect.size(); i++)
	{
		all_time.addUser(userVect.at(i));
	}
	today.initLeaderboard("TODAY-LEADERBOARD");
	board.initBoard();
	setUser(board);
	board.clearBoard();
	board.setMode();
	board.clearBoard();
	board.setCode(true);
	board.clearBoard();
	board.drawBoard();

}

int main() {
	/*
	* files one that conatins all file names?
	* Or should they contain pointers to the files themselves?
	*
	*/
	bool done = false;
	GameBoard board;


	startUp(board);

	while (!done)
	{
		board.getGuess(true);
		board.drawBoard();
		if (board.done)
		{
			bool ask = true;
			while (ask)
			{
				string answer;
				cout << "Do you want to play again?\n";
				getline(cin, answer, '\n');
				ask = false;
				//try
				//{
					if (board.yesOrNoQuestion(answer))
					{
						resetGame(board);
					}
					else
					{
						done = true;
						gameEnd(board);
					}
				//}
				//catch (const std::exception&)
				//{
				//	ask = true;
				//	system("CLS");
				//	cout << "ERROR : Reset Board \n" <<"Wrong input\nYou typed " << answer << endl;
				//}
			}
		}
	}
	return 0;
}