bool solveSudoku(int, int);
void loadFile();
void printGameboard();
bool isEnded(int);
bool foundPossibleNumberToPutInCell(int, int);
bool isPossibleToPutInCell(int, int, int);
bool rowHasThatNumber(int, int, int);
bool columnHasThatNumber(int, int, int);
bool subsquareHasThatNumber(int, int, int);
