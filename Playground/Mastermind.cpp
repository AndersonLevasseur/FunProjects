#include <iostream>
#include <string>
#include "User.cpp"
#include "MastermindGameboard.cpp"

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

int main() {
	bool done = false;
	GameBoard board;
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