#include "MastermindGameboard.cpp"
#include <fstream>
#include <vector>

/* TODO :
* Write a method to search for files
*
*
*/

using namespace std;
string files[MAXNUMOFBOARDS];
vector <User> userVect;
int numOfUsers = 0;

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

User writeUser(User user)
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

	userFile.close();
	return user;
}

void close(GameBoard &board)
{
	if (board.currentUser.loc == -1)
	{
		userVect.push_back(board.currentUser);
		close(board);
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
	bool newUser = false;
	for (int i = 0; i < numOfUsers; i++)
	{
		if (userVect.at(i).name == userStr)
		{
			board.currentUser = userVect.at(i);
			board.currentUser.loc = i;
			i = userVect.size();
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
		User newUser;
		newUser.name = userStr;
		newUser.loc = -1;

		board.setCurrentUser(writeUser(newUser));
	}
}

//doesn't quite work
void resetGame(GameBoard& board)
{
	if (board.currentUser.loc == -1)
	{
		userVect.push_back(board.currentUser);
		close(board);
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
	board.setCode(true);
	board.clearBoard();
	board.drawBoard();

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
				try
				{
					if (board.yesOrNoQuestion(answer))
					{
						resetGame(board);
					}
					else
					{
						done = true;
						close(board);
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