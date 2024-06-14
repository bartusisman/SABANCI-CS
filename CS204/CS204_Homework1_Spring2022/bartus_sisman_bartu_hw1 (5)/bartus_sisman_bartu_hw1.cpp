#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct cell
{
	char letter;
	char color;
};

void FileOperations(string & word, int & attempts)
{
	string filename;

	cout << "Please enter the file name: ";
	cin >> filename;

	ifstream in;
	in.open(filename);

	while (in.fail())
	{
		cout << "Couldn't find the file!" << endl;

		cout << "Please enter the file name: ";
		cin >> filename;
		in.open(filename);
	}
	in >> attempts;
	in >> word;
} 

void PrintMatrix(vector<vector<cell>> matrix)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		cout << "|";
		for (int j = 0; j < matrix[0].size() ; j++)
		{
			cout << "| " << matrix[i][j].letter << " , " << matrix[i][j].color << " |";
			if (!( j+1 == matrix[0].size() ))
			{
				cout << " ";
			}
		}
		cout << "|";
		cout << endl;
	}
}

bool InputCheck1(string &guess, string word)
{
	if (guess.length() > word.length())
	{
		cout << "The word is too long!" << endl;
		return false;
	}

	
	else if (guess.length() < word.length())
	{
		cout << "The word is too short!" << endl;
		return false;
	}
}

bool InputCheck2(string &guess, string word)
{
	for (int i = 0; i < guess.length(); i++)
	{
		if ( !(isalpha(guess[i])) || (isupper(guess[i])) )
		{
			cout << "Your input has illegal letters!" << endl;
			return false;
		}
	}
}

bool InputCheck3(string &guess, string word)
{
	for (int i = 0; i < guess.length(); i++)
	{
		for (int j = i + 1; j < guess.length(); j++)
		{
			if (guess[i] == guess[j])
			{
				cout << "Your input has a duplicate letter!" << endl;
				return false;
			}
		}
	}
}

bool InputCheck4(vector<vector<cell>> matrix, string guess)
{
	string word;
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			word.push_back(matrix[i][j].letter);
		}
		if (word == guess)
		{
			cout << "You've already tried this word!" << endl;
			return false;
		}
	}
}

bool InputCheck5(vector<vector<cell>> matrix, string guess)
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[0].size(); j++)
		{
			if ( (matrix[i][j].color == 'G') && (guess[j] != matrix[i][j].letter))
			{
				cout << "You did not use the green letter in your word!" << endl;
				return false;
			}
		}

	}
}

void InputChecks(string &guess, string word, vector<vector<cell>> & matrix)
{
	cout << "What's your guess? ";
	cin >> guess;
	if (!(InputCheck1(guess, word)))
		{
		InputChecks(guess,word, matrix);
		}

	if (!(InputCheck2(guess, word)))
		{
		InputChecks(guess,word, matrix);
		}

	if (!(InputCheck3(guess, word)))
		{
		InputChecks(guess,word, matrix);
		}

	if (!(InputCheck4(matrix, guess)))
		{
		InputChecks(guess,word, matrix);
		}

	if (!(InputCheck5(matrix, guess)))
		{
		InputChecks(guess,word, matrix);
		}
}

char ReturnColor(string guess, char letter, string word)
{
	for (int i = 0; i < guess.length(); i++)
	{
		if (word.find(letter) == string::npos)
		{
			return 'B';
		}
		else
		{
			if (word.find(letter) == guess.find(letter))
			{
				return 'G';
			}
			else
			{
				return 'Y';
			}
		}
	}
}

void AddToMatrix(vector<vector<cell>> & matrix, string guess, string word, int row)
{
	for (int i = 0; i < word.length(); i++)
	{
		matrix[row][i].letter = guess[i];
		matrix[row][i].color = ReturnColor(guess, guess[i], word);
	}
}

int main()
{
	string word, guess;
	int attempts;
	cout << "Welcome to SWordle!" << endl;

	FileOperations(word, attempts);

	cout << "The word that you will guess has " << word.length() << " letters and you have " << attempts << " attempts." << endl;

	cell null;
	null.letter = '-';
	null.color = '-';

	vector<cell> empty(word.length(), null);
	vector<vector<cell>> matrix(attempts, empty); 

	for (int i = 0; i < attempts; i++)
	{
		InputChecks(guess, word, matrix); 
		
		AddToMatrix(matrix, guess, word, i);
		PrintMatrix(matrix);

		if (word == guess)
		{
			cout << "You win!" << endl;
			break;
		}
		
	}

	if (word != guess)
	{
		cout << "You lose!" << endl;
	}
	return 0;
}