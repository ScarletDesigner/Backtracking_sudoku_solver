#include <iostream>
#include <fstream>
using namespace std;

const string fileName = "test2.txt";
	
class Sudoku
{
	static const int gameboardSize = 9;
	static const int boundary = gameboardSize - 1;
	static const int subsquareSize = 3;
	static const int empty = 0;
	int gameboard[gameboardSize][gameboardSize];
	
public:
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
		for(int possibleNumber=1; possibleNumber <= gameboardSize; possibleNumber++)
		{
			if(isPossibleToPutInCell(x, y, possibleNumber))
			{
				gameboard[y][x] = possibleNumber;
				bool nextEmptyCell = solveSudoku(x+1, y);
				if(nextEmptyCell)
				{
					return true;
				}
			}
		}
		gameboard[y][x] = empty;
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
		int startingCellOfSubsquareHorizontal = x - x%subsquareSize;
		int startingCellOfSubsquareVertical = y - y%subsquareSize;
		for(int i=0;i<subsquareSize;i++)
		{
			for(int j=0;j<subsquareSize;j++)
			{
				int currentCellInSubsquare = gameboard[startingCellOfSubsquareVertical + i][startingCellOfSubsquareHorizontal + j];
				if (currentCellInSubsquare == possibleNumberToPutInCell)
					return true;
			}
		}
		return false;
	}
	
};

int main(){
	Sudoku game;
	game.loadFile();
	cout<<"Your starting gameboard:"<<endl;
	game.printGameboard();
	cout<<"Finished gameboard:"<<endl;
	game.solveSudoku(0, 0);
	return 0;
}
