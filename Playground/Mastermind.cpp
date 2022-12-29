#include <iostream>
#include "Board.h"
#include <string>

/* TODO :
* Create a reset Game function
* Create a new function to deal with yes no questions ?
* Create a more efficient way to clear the screen
	* create a reset screen function
*
*
*

*/

using namespace std;
class GameBoard
{
public:

	string pause;
	bool done = false;
	bool duplicates = false;
	char codeArr[CODELENGTH];

	int numOfTurns = NUMOFTURNS;
	int mode;
	int turnNum = 0;
	string headerHash = "#";
	string headerDash = "-";
	string header = "|";
	string columnNumbers = "|";
	string emptyLine = "|   |";
	string flatLine = "_____";
	string bracketFlatLine = "|-----";
	string user;



	// added 2 to account for the number of white and red pins
	int	playingBoard[NUMOFTURNS][CODELENGTH + 2];
	bool yesOrNoQuestion(string guess) {
		string acceptedValues = "Y";
		string rejectValues = "N";
		if (acceptedValues.find(guess) != string::npos)
		{
			return true;
		}
		else if (rejectValues.find(guess) != string::npos)
		{
			return false;
		}
		else
		{
			throw "ERROR : Invalid Input";
		}
	}
	void initBoard() {
		for (int i = 0; i < CODELENGTH + 2; i++)
		{
			for (int j = 0; j < NUMOFTURNS; j++)
			{
				playingBoard[i][j] = 0;
			}
		}
		turnNum = 0;
		// creates a 2D array, maybe make dynamic later
		cout << "Welcome to MasterMind\n";
		cout << "Press enter to continue\n";
		getline(cin, pause, '\n');
		system("CLS");
		setUser();
		system("CLS");
		setMode();
		system("CLS");
		setCode();
		system("CLS");
		{
			for (int i = 0; i < CODELENGTH; i++)
			{
				emptyLine += "   |";
				flatLine += "____";
				bracketFlatLine += "----";
				columnNumbers += " " + to_string(i + 1) + "  ";
				if (i > 2)
				{
					headerHash += "#";
					headerDash += "-";
				}
			}
			bracketFlatLine.pop_back();
			bracketFlatLine.pop_back();
			bracketFlatLine += "|\n";

			flatLine += "\n";

			emptyLine += "\n";

			columnNumbers += "R W| \n";

			header += headerHash + headerDash + "MASTERMINDS" + headerDash + headerHash + "|\n" + columnNumbers;
		}
		drawBoard();
	}

	void resetGame()
	{

	}

	void setMode()
	{
		string modeSelect = "";
		cout << "Single or Multiplayer?\nType 'Y' for Single Player or 'N' for Multiplayer\n";
		getline(cin, modeSelect, '\n');
		while (modeSelect != "Y" && modeSelect != "N")
		{
			system("CLS");
			cout << "Error : Wrong input\n" << "You typed '" << modeSelect << "'" << endl << "Please Type 'Y' for Single Player or 'N' for Multiplayer\n";
			modeSelect = "";
			getline(cin, modeSelect, '\n');
		}
		if (modeSelect == "Y")
		{
			mode = SINGLEPLAYER;
			system("CLS");
			cout << "Allow duplicates?\n'Y' for yes 'N' for no\n";
			modeSelect = "";
			getline(cin, modeSelect, '\n');
			while (modeSelect != "Y" && modeSelect != "N")
			{
				system("CLS");
				cout << "Error : Wrong input\n" << "You typed " << modeSelect << endl << "Please Type 'Y' to allow duplicates or 'N' to not\n";
				modeSelect = "";
				getline(cin, modeSelect, '\n');
			}
			if (modeSelect == "Y")
			{
				duplicates = true;
			}
		}
		else
		{
			mode = MULTIPLAYER;
		}
	}
	// gathers users name
	void setUser()
	{
		cout << "What is your name?" << endl;
		getline(cin, user, '\n');
		if (user == "Hannah" || user == "hannah")
		{
			user = "TIM";
		}
	}

	//sets code to be sought and puts it into an array
	void setCode() {
		string codeStr;
		if (mode == SINGLEPLAYER)
		{
			codeStr = VALID_CHARACTERS;
			for (int i = 0; i < CODELENGTH; i++)
			{
				int randomNum = time(NULL) % codeStr.length();
				codeArr[i] = codeStr.at(randomNum);
				if (!duplicates)
				{
					string str1 = codeStr.substr(randomNum + 1);
					string str2 = codeStr.substr(0, randomNum);
					codeStr = str1 + str2;
				}
			}
		}
		else
		{
			cout << "Please enter " << CODELENGTH << " letters limited to " << VALID_CHARACTERS << endl;
			codeStr = getInput("Code");
			for (int i = CODELENGTH - 1; i >= 0; i--)
			{
				codeArr[i] = codeStr.back();
				codeStr.pop_back();
			}
		}
		// NEEDS ERROR testing baad
		// add testing to getInput, should apply to both
	}

	// draws boar given the state of playingBoard
	void drawBoard() {
		// initial drawing - creates empty board
		cout << flatLine << header << bracketFlatLine;

		string output = "";
		for (int i = 0; i < NUMOFTURNS; i++)
		{

			if (playingBoard[i][0] == 0)
			{
				output += emptyLine;
			}
			else
			{
				for (int j = 0; j < CODELENGTH; j++)
				{
					char ch = playingBoard[i][j];
					output += "| ";
					output += ch;
					output += " ";
				}
				output += "|";
				output += to_string(playingBoard[i][CODELENGTH + 1]);
				output += " ";
				output += to_string(playingBoard[i][CODELENGTH]);
				output += "|\n";
			}

		}
		cout << output;

		cout << bracketFlatLine << endl;
		if (done)
		{
			cout << user << " WINS!!!!";
		}
	}

	//retrieves guess from the user
	void getGuess() {
		string guess = "";
		cout << "What is your Guess" << endl;
		guess = getInput("Guess");
		checkGuess(guess);
		turnNum++;
	}

	//part of the retreival service
	string getInput(string inputName) {
		string input;
		int checkResult;


		getline(cin, input, '\n');

		//Check to make sure guess is valid, then populate array
		checkResult = inputValidation(input);

		if (checkResult != VALID)
		{
			cout << "Error : " << inputName << " " << input << " is";
			switch (checkResult)
			{
			case 0:
				cout << " not valid" << endl;
				break;
			case 2:
				cout << " repeat guess" << endl;
				break;
			case 3:
				cout << " too long" << endl;
				break;
			case 4:
				cout << " too short" << endl;
				break;
			default:
				cout << "Unknown Error : Try again";
				break;
			}
			if (inputName == "Code")
			{
				setCode();
			}
			else
			{
				getGuess();
			}
			checkResult = inputValidation(input);
		}


		//add test to make sure inputs are valid

		//make it smart to predict what you are trying to say

		return input;
	}

	// returns int depending on guess... see Board.h
	int inputValidation(string input) {
		//for now only uses leters A - E
		// doesn't check that it's too short

		int checkResult = INVALID;

		int validResult = 0;

		int guessArr[CODELENGTH];
		int arrLoc = CODELENGTH - 1;

		if (input.length() < CODELENGTH)
		{
			checkResult = TOO_SHORT;
			return checkResult;
		}

		for (int i = input.length(); i > 0; i--)
		{
			char guessChar = input.back();

			if (arrLoc < 0)
			{
				checkResult = TOO_LONG;
				return checkResult;
			}

			if (guessChar == 32)
			{
				checkResult = VALID;
			}
			else if (VALID_CHARACTERS.find(guessChar) == string::npos)
			{
				checkResult = INVALID;
				return checkResult;
			}
			else
			{
				guessArr[arrLoc] = guessChar;
				arrLoc--;
				checkResult = VALID;
			}

			input.pop_back();
		}




		return checkResult;
	}

	// changes the array, implementation of guess
	// also calculates red and white pins
	void checkGuess(string guess)
	{
		int whitePegs = 0;
		int redPegs = 0;
		//checks for redPin
		for (int i = CODELENGTH - 1; i >= 0; i--)
		{
			if (guess.back() == codeArr[i])
			{
				redPegs++;
			}
			else if (find(begin(codeArr), end(codeArr), guess.back()) != codeArr + CODELENGTH)
			{
				whitePegs++;
			}
			playingBoard[turnNum][i] = char(guess.back());
			guess.pop_back();
		}
		//redPegs
		playingBoard[turnNum][CODELENGTH + 1] = redPegs;
		//whitePegs
		playingBoard[turnNum][CODELENGTH] = whitePegs;
		system("CLS");
		if (redPegs == 4)
		{
			done = true;
		}

		drawBoard();
	}
} board;

int main() {
	bool done = false;
	board.initBoard();
	while (!done)
	{
		board.getGuess();
		if (board.done)
		{
			bool ask = true;
			while (ask)
			{
			string answer;
			cout << "Do you want to play again?";
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
					cout << "Wrong input\nYou typed " << answer;
				}
			}


		}
	}


	return 0;
}