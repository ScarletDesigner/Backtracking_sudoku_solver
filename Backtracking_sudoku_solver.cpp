#include <iostream>
#include <fstream>
using namespace std;

const int gameboardSize = 9;
const int boundary = gameboardSize - 1;
const int squareSize = 3;
const int empty = 0;
const string fileName = "test2.txt";
int gameboard[gameboardSize][gameboardSize];

bool solveSudoku(int, int);

void loadFile()
{
	fstream file(fileName.c_str());
	if(file.good()==false)
	{
		cout<<"Failed to load the file"<<endl;
		exit(0);
	}
	for(int i=0;i<gameboardSize;i++)
	{
		for(int j=0;j<gameboardSize;j++)
		{
			char importingCell;
			file>>importingCell;
			int valueOfCell = importingCell - '0';
			gameboard[i][j] = valueOfCell;
		}
	}
	file.close();
}

void printGameboard()
{	
	for(int i=0;i<gameboardSize;i++)
	{
		for(int j=0;j<gameboardSize;j++)
		{
			cout<<gameboard[i][j];
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}

bool rowHasThatNumber(int x, int y, int possibleNumberToPutInCell)
{
	for(int i=0;i<gameboardSize;i++)
	{
		int numberInRow = gameboard[y][i];
		if(numberInRow == possibleNumberToPutInCell)
			return true;
	}
	return false;
}
bool columnHasThatNumber(int x, int y, int possibleNumberToPutInCell)
{
	for(int i=0;i<gameboardSize;i++)
	{
		int numberInColumn = gameboard[i][x];
		if(numberInColumn == possibleNumberToPutInCell)
			return true;
	}
	return false;
}
bool subsquareHasThatNumber(int x, int y, int possibleNumberToPutInCell)
{
	int startingCellOfSquareHorizontal = x - x%squareSize;
	int startingCellOfSquareVertical = y - y%squareSize;
	for(int i=0;i<squareSize;i++)
	{
		for(int j=0;j<squareSize;j++)
		{
			int currentCellInSquare = gameboard[startingCellOfSquareVertical + i][startingCellOfSquareHorizontal + j];
			if (currentCellInSquare == possibleNumberToPutInCell)
				return true;
		}
	}
	return false;
}
bool isPossibleToPutInCell(int x, int y, int possibleNumberToPutInCell)
{
	if (rowHasThatNumber(x, y, possibleNumberToPutInCell))
		return false;
	if (columnHasThatNumber(x, y, possibleNumberToPutInCell))
		return false;
	if (subsquareHasThatNumber(x, y, possibleNumberToPutInCell))
		return false;
	return true;
}

bool isEnded(int y)
{
	if (y > boundary)
	{
		printGameboard();
		return true;
	}
	return false;
}

bool foundPossibleNumberToPutInCell(int x, int y)
{
	for(int i=1;i<=gameboardSize;i++)
	{
		if(isPossibleToPutInCell(x, y, i))
		{
			gameboard[y][x] = i;
			bool nextEmptyCell = solveSudoku(x+1, y);
			if(nextEmptyCell)
			{
				return true;
			}
		}
	}
	gameboard[y][x] = 0;
	return false;
}

bool solveSudoku(int x, int y)
{
	int currentCell = gameboard[y][x];
	if (isEnded(y))
		return true;
	if (x > boundary)
		return solveSudoku(0, y+1);
	if (currentCell != empty)
		return solveSudoku(x+1, y);
	if(foundPossibleNumberToPutInCell(x, y))
		return true;
	return false;
}

int main(){
	loadFile();
	cout<<"Your starting gameboard:"<<endl;
	printGameboard();
	cout<<"Finished gameboard:"<<endl;
	solveSudoku(0, 0);
	return 0;
}
