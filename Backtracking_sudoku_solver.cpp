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
	int x, y;
	
protected:
	bool solveSudoku(int x, int y)
	{
		this -> x = x;
		this -> y = y;
		int currentCell = gameboard[y][x];
		
		if (isEnded())
			return true;
			
		if (x > boundary)
			return solveSudoku(0, y + 1);
			
		if (currentCell != empty)
			return solveSudoku(x + 1, y);
			
		if (hasSolutionForCurrentCell(x, y))
			return true;
			
		return false;
	}
	
private:
	bool isEnded()
	{
		if (y > boundary)
		{
			printGameboard();
			return true;
		}
		return false;
	}

	bool hasSolutionForCurrentCell(int x, int y)
	{
		for(int i = 1; i <= gameboardSize; i++)
		{
			possibleNumberToPutInCell = i;
			if(isPossibleToPutInCell(x, y))
			{
				replaceCellWithPossibleNumber();
				bool nextCellHasSolution = solveSudoku(x+1, y);
				if(nextCellHasSolution)
					return true;
			}
		}
		resetCellToDefault(x, y);
		return false;
	}
	
	void resetCellToDefault(int x, int y)
	{
		gameboard[y][x] = empty;
	}
	void replaceCellWithPossibleNumber()
	{
		gameboard[y][x] = possibleNumberToPutInCell;
	}
	
	
	bool isPossibleToPutInCell(int x, int y)
	{
		this -> x = x;
		this -> y = y;
		if (rowHasThatNumber())
			return false;
		if (columnHasThatNumber())
			return false;
		if (subsquareHasThatNumber())
			return false;
		return true;
	}

	bool rowHasThatNumber()
	{
		for(int i=0;i<gameboardSize;i++)
		{
			int numberInRow = gameboard[y][i];
			if(numberInRow == possibleNumberToPutInCell)
				return true;
		}
		return false;
	}

	bool columnHasThatNumber()
	{
		for(int i = 0; i < gameboardSize; i++)
		{
			int numberInColumn = gameboard[i][x];
			if(numberInColumn == possibleNumberToPutInCell)
				return true;
		}
		return false;
	}

	bool subsquareHasThatNumber()
	{
		int startingCellOfSubsquareHorizontal = x - x%subsquareSize;
		int startingCellOfSubsquareVertical = y - y%subsquareSize;
		for(int i=0; i < subsquareSize; i++)
		{
			for(int j=0; j < subsquareSize; j++)
			{
				int currentCellInSubsquare = gameboard[startingCellOfSubsquareVertical + i][startingCellOfSubsquareHorizontal + j];
				if (currentCellInSubsquare == possibleNumberToPutInCell)
					return true;
			}
		}
		return false;
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
	
	Sudoku s("test1.txt");

	return 0;
}
