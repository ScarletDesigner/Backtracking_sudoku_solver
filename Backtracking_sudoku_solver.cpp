#include <iostream>
#include <fstream>
using namespace std;

class FileLoader {
	
protected:
	
	static const int gameboardSize = 9;
	int gameboard[gameboardSize][gameboardSize];
	fstream file;
	
	void loadFile(string fileName)
	{
		file.open(fileName.c_str());
		checkIfFileExists();
		importFileIntoGameboard();
		file.close();
	}
	
private:
	
	checkIfFileExists()
	{
		if(file.good() == false)
		{
			cout<<"Failed to load the file"<<endl;
			exit(0);
		}
	}
	importFileIntoGameboard()
	{
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
	}
};

class GameboardPrinter: public FileLoader {
	
protected:
	
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
};

class SudokuSolver : public GameboardPrinter {

	static const int boundary = gameboardSize - 1;
	static const int subsquareSize = 3;
	static const int empty = 0;
	int possibleNumberToPutInCell;
	
protected:
	
	bool solveSudoku(int x, int y)
	{
		int currentCell = gameboard[y][x];
		if (isEnded(y))
			return true;
		if (x > boundary)
			return solveSudoku(0, y+1);
		if (currentCell != empty)
			return solveSudoku(x+1, y);
		if (foundPossibleNumberToPutInCell(x, y))
			return true;
		return false;
	}
	
private:
	
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
			possibleNumberToPutInCell = possibleNumber;
			if(isPossibleToPutInCell(x, y))
			{
				gameboard[y][x] = possibleNumber;
				bool nextEmptyCell = solveSudoku(x+1, y);
				if(nextEmptyCell)
				{
					return true;
				}
			}
		}
		resetCellToDefault(x, y);
		return false;
	}
	
	bool isPossibleToPutInCell(int x, int y)
	{
		if (rowHasThatNumber(x, y))
			return false;
		if (columnHasThatNumber(x, y))
			return false;
		if (subsquareHasThatNumber(x, y))
			return false;
		return true;
	}

	bool rowHasThatNumber(int x, int y)
	{
		for(int i=0;i<gameboardSize;i++)
		{
			int numberInRow = gameboard[y][i];
			if(numberInRow == possibleNumberToPutInCell)
				return true;
		}
		return false;
	}

	bool columnHasThatNumber(int x, int y)
	{
		for(int i=0;i<gameboardSize;i++)
		{
			int numberInColumn = gameboard[i][x];
			if(numberInColumn == possibleNumberToPutInCell)
				return true;
		}
		return false;
	}

	bool subsquareHasThatNumber(int x, int y)
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
	
	resetCellToDefault(int x, int y)
	{
		gameboard[y][x] = empty;
	}
			
};

class Sudoku: public SudokuSolver {
	
public:
	
	Sudoku(string fileName)
	{
		loadFile(fileName);
		cout<<"Your starting gameboard:"<<endl;
		printGameboard();
		cout<<"Finished gameboard:"<<endl;
		solveSudoku(0, 0);
	}

};

int main(){
	
	Sudoku s("test2.txt");

	return 0;
}
