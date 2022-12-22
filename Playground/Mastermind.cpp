#include <iostream>
#include "Board.h"
#include <string>

using namespace std;
class GameBoard
{
public:

	string code;
	string pause;
	bool done = false;

	int whitePegs = 0;
	int redPegs = 0;
	int numOfTurns = NUMOFTURNS;
	int mode = GAMEMODE;
	int turnNum = 0;
	string headerHash = "#";
	string headerDash = "-";
	string header = "|";
	string columnNumbers = "| ";
	string emptyLine = "|   |";
	string flatLine = "_____";
	string bracketFlatLine = "|-----";



	// added 2 to account for the number of white and red pins
	int	playingBoard[NUMOFTURNS][CODELENGTH + 2];
	void initBoard() {
		for (int i = 0; i < CODELENGTH + 2; i++)
		{
			for (int j = 0; j < NUMOFTURNS; j++)
			{
				playingBoard[i][j] = 0;
			}
		}
		// creates a 2D array, maybe make dynamic later
		cout << "Welcome to MasterMind\n";
		cout << "Press enter to continue\n";
		getline(cin, pause, '\n');
		system("CLS");

		setCode();
		system("CLS");
		{
			for (int i = 0; i < CODELENGTH; i++)
			{
				emptyLine += "   |";
				flatLine += "____";
				bracketFlatLine += "----";
				columnNumbers += to_string(i + 1) + "   ";
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

			columnNumbers += "? | \n";

			header += headerHash + headerDash + "MASTERMINDS" + headerDash + headerHash + "|\n" + columnNumbers;
		}
		drawBoard();
	}

	//sets code to be sought	
	void setCode() {
		cout << "Please enter " << CODELENGTH << " letters llimited to " << VALID_CHARACTERS << endl;
		getline(cin, code, '\n');
		// NEEDS ERROR testing
	}

	// draws boar given the state of playingBoard
	void drawBoard() {
		// initaial drawing - creates empty board
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
					output += "| " + playingBoard[i][j];
					output += " ";
				}
				output += "|\n";
			}

		}
		cout << output;
		cout << bracketFlatLine << endl;
		/*for (int i = 0; i < NUMOFTURNS; i++)
		{
			cout <<
		}*/
	}

	//void populateBoard(int turnNum, string guess) {
	//	
	//}

	string getGuess() {
		string guess;
		int checkResult;

		cout << "What is your Guess" << endl;

		getline(cin, guess, '\n');

		//Check to make sure guess is valid, then populate array
		checkResult = guessCheck(guess);

		while (checkResult != VALID)
		{
			cout << "Error : Guess " << guess << " is";
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
			default:
				cout << "Unknown Error : Try again";
				break;
			}
		}


		//add test to make sure inputs are valid

		//make it smart to predict what you are trying to say

		return guess;
	}

	// returns int depending on guess... see Board.h
	int guessCheck(string guess) {
		//for now only uses leters A - E
		// doesn't check that it's too short

		int checkResult;

		int validResults = 0;

		int guessArr[CODELENGTH];
		int arrLoc = CODELENGTH - 1;

		for (int i = guess.length(); i > 0; i--)
		{
			char guessChar = guess.back();
			if (validResults > CODELENGTH)
			{
				return checkResult = TOO_LONG;
			}

			if (arrLoc < 0)
			{
				return checkResult;
			}

			if (guessChar == 32)
			{
				checkResult = VALID;
			}
			else if (VALID_CHARACTERS.find(guessChar) == string::npos)
			{
				return checkResult = INVALID;
			}
			else
			{
				guessArr[arrLoc] = guessChar;
				arrLoc--;
				validResults++;
				checkResult = VALID;
			}
		}


		guess.pop_back();


		return checkResult;
	}

} board;

int main() {
	bool done = false;
	int turnNum = 0;
	int numOfTurns = 8;


	board.initBoard();



	while (!done && turnNum < numOfTurns) {
		board.getGuess();


	}


	return 0;
}