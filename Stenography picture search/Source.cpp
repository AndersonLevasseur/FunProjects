//#include "Header.h";
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/// <summary>
/// Problems
///		not grabbing right ones
/// </summary>
using namespace std;

int evenOrOdd(string value, string type)
{
	if (type == "hex")
	{
		if (value == "0x00")
		{
			return 69;
		}
		if (char(value.back()) <= 57 && char(value.back()) >= 48)
		{
			//number
			if (char(value.back()) % 2 == 0)
			{
				//even
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else if (char(value.back()) <= 123 && char(value.back()) >= 65)
		{
			//char
			if (char(value.back()) == 'A' || char(value.back()) == 'C' || char(value.back()) == 'E')
			{
				return 0;
			}
			else if (char(value.back()) == 'B' || char(value.back()) == 'D' || char(value.back()) == 'F')
			{
				return 1;
			}
		}
	}
	else
	{
		throw "not hex";
	}
	return 69;
}

void read(vector <vector <int>>& bitmap)
{
	vector <int> temp;
	string tempStr;
	int vectorFirstLevel = 0;
	int vectorSecondLevel = 0;

	ifstream imageFile;
	imageFile.open("image.txt");

	getline(imageFile, tempStr, ',');
	bitmap.push_back(temp);
	bitmap.at(vectorFirstLevel).push_back(evenOrOdd(tempStr, "hex"));

	while (!imageFile.eof())
	{
		getline(imageFile, tempStr, ',');
		if (vectorSecondLevel >= 15)
		{
			vectorFirstLevel++;
			vectorSecondLevel = 0;
			bitmap.push_back(temp);
		}
		else
		{
			vectorSecondLevel++;
		}
		bitmap.at(vectorFirstLevel).push_back(evenOrOdd(tempStr, "hex"));
	}
	imageFile.close();
}

vector <vector <int>> findMessage(int whatBit, int messageStartInt, int charLength, int howLong, vector <vector <int>> bitmap)
{
	vector <vector <int>> message;
	int i = messageStartInt;
	int j = 0;
	int k = 0;
	int newCharLength = charLength;
	int numOfIt = 1;
	vector <int> temp;
	message.push_back(temp);
	while (numOfIt < (howLong * charLength) + 1)
	{
		while (i > 15)
		{
			j++;
			i -= 16;
		}
		if (numOfIt > newCharLength)
		{
			newCharLength += newCharLength / (k + 1);
			vector <int> temp;
			message.push_back(temp);
			k++;
		}
		message.at(k).push_back(bitmap.at(j).at(i));
		i += whatBit;
		numOfIt++;

	}

	return message;
}

int main() {
	vector <vector <int>> bitmap;
	vector <vector <int>> messageVect;

	string message;
	string messageStartStr;
	int messageStartInt;
	int whatBit;
	int howLong;
	int chars;
	read(bitmap);

	cout << "WELCOME TO STENOGRAPHY PICTURE SEARCH\n"
	cout << "Where does the message start?" << endl;
	getline(cin, messageStartStr, '\n');
	messageStartInt = stoi(messageStartStr);

	cout << "Every what bit" << endl;
	getline(cin, messageStartStr, '\n');
	whatBit = stoi(messageStartStr);

	cout << "How many bits per character" << endl;
	getline(cin, messageStartStr, '\n');
	howLong = stoi(messageStartStr);

	cout << "How many characters" << endl;
	getline(cin, messageStartStr, '\n');
	chars = stoi(messageStartStr);
	system("CLS");

	messageVect = findMessage(whatBit, messageStartInt, howLong, chars, bitmap);
	int firstLevel = 0;
	int secondLevel = 0;
	for (int i = 0; i < howLong * chars; i++)
	{
		if (i % howLong == 0 && i != 0)
		{
			firstLevel++;
			secondLevel = 0;
			cout << endl;
		}
		cout << messageVect.at(firstLevel).at(secondLevel);
		secondLevel++;
	}
	cout << endl << "done";
}

