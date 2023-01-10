#include "MastermindGameboard.cpp"
#include <fstream>

/* TODO :
* Write a method to search for files
*
*
*/

using namespace std;
string files[MAXNUMOFBOARDS];
User userArr[9];
int numOfUsers;

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
		while (j < 5 && !userFile.eof())
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
			default:
				throw "not a complete user";
				break;
			}
			j++;
		}
		if (tempUser.name.length() > 1)
		{
		userArr[i] = tempUser;
		i++;
		numOfUsers++;
		}
	}
	userArr;
	userFile.close();
}

User writeUser(string userName)
{
	ofstream userFile;
	userFile.open("allUsers.txt", ios::app);
	if (userFile.fail())
	{
		throw "Open failed";
	}
	User user;
	user.name = userName;

	userFile << user.name << "\n";
	userFile << to_string(user.wins) << "\n";
	userFile << to_string(user.losses) << "\n";
	userFile << to_string(user.gamesPlayed) << "\n";
	userFile << user.record << "\n";

	userFile.close();
	return user;
}

void setUser(GameBoard board)
{
	string userStr = board.setUser();
	bool newUser = false;
	for (int i = 0; i <= numOfUsers; i++)
	{
		if (userArr[i].name == userStr)
		{
			board.currentUser = userArr[i];
			i = numOfUsers;
			newUser = false;
		}
		else
		{
			newUser = true;
		}
	}
	if (newUser)
	{
		//board.currentUser = writeUser(userStr);
		board.setCurrentUser(writeUser(userStr));
	}
}

int main() {
	/*
	* files one that conatins all file names?
	* Or should they contain pointers to the files themselves?
	*
	*/
	bool done = false;
	GameBoard board;
	fileStartup();
	userStartup();
	board.initBoard();
	setUser(board);
	board.clearBoard();
	board.setMode();
	board.clearBoard();
	board.setCode();
	board.clearBoard();
	board.drawBoard();

	while (!done)
	{
		board.getGuess();
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
				try
				{
					if (board.yesOrNoQuestion(answer))
					{
						board.resetGame();
					}
					else
					{
						done = true;
					}
				}
				catch (const std::exception&)
				{
					ask = true;
					system("CLS");
					cout << "Wrong input\nYou typed " << answer << endl;
				}
			}
		}
	}
	return 0;
}