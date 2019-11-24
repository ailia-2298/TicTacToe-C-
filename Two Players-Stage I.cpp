#include<iostream>
#include<iomanip>
using namespace std;
class tictactoe {
private:
	int **matrix, rows, cols, count = 0;
public:
	//CONSTRUCTOR
	tictactoe() {
		int grid_value;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t\tWELCOME TO TIC-TAC-TOE\n";
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "\nSelect playing grid:\n1. 3x3\n2. 4x4\n3. 5x5\n\n";
		do {
			cout << "Enter your choice : ";
			cin >> grid_value;
			cout << " Invalid.\n";
		} while ((grid_value <= 0 || grid_value > 4));			//grid value must be 1, 2 or 3. else the loop will continue taking input.
		grid_value = grid_value + 2;							//when the user 'll enter 1, the grid must be of 3x3 size. similarly, gridvalue+2 will be the size of the grid the user want to play.
		rows = cols = grid_value;
		matrix = new int*[rows];								//matrix is being assigned rows number of pointer arrays

		for (int i = 0; i < rows; i++)
			matrix[i] = new int[cols];							//each pointer array is now assigned cols number of elements.

		for (int j = 0; j < rows; j++)
			for (int k = 0; k < cols; k++)
				matrix[j][k] = -1;								//each element of the 2D matrix is initialized with -1
		system("cls");											//clears the console screen
		cout << endl;
		displayboard();											//call to a function which will diaplay the matrix constructed on the screen.
	}

	//DESTRUCTOR
	~tictactoe() {
		//cout << " DESTRUCTOR EXECUTED..." << endl;
		for (int i = 0; i < rows; i++)
			delete[]matrix[i];									//delete the 2D arrays
	}

	void insertvalue() {
		int key;
		cout << "Player ";
		if (count % 2 == 0)										//count is initialized with 0. so, the first turn will be of player 1.
			cout << 1;
		else if (count % 2 != 0)								//the second turn and all the even number of turns will be of player 2.
			cout << 2;
		cout << " select a location: ";
		cin >> key;
		key = key - 1;											//key entered will be 1-9 for 3x3 whereas, the indexes of the matrix will be 0-8.
		system("cls");
		if (key >= 0 && key < this->cols*this->rows) {			//if the key is a valid index
			int i = 0, j = 0;
			while (key >= rows) {								//if the key is greater equal to rows then i should be added +1 that indicate that i is 0,1 or 2...
				i++;
				key = key - rows;								//key is then subtracted with number of rows to determine the column(j)
			}
			j = key;
			if (count % 2 == 0 && matrix[i][j] == -1) {			//if it's player1's turn & the position is empty. it will be assigned 1(x) in the grid
				matrix[i][j] = 1;
				count++;										//count is added +1 showing that a valid turn occured and now the second player will make it's turn.
				cout << endl;
			}
			else if (count % 2 != 0 && matrix[i][j] == -1) {	//if it's player2's turn & the position is empty. it will be assigned 0(o) in the grid
				matrix[i][j] = 0;
				count++;										//count is added +1 showing that a valid turn occured and now the second player will make it's turn.
				cout << endl;
			}
			else
				cout << "---- INVALID MOVE ----" << endl;		//if the position is not empty then it's an invalid move.
		}
		else 
			cout << "---- INVALID MOVE ----" << endl;			//if the key is not in between 0-(nxn) then it is also invalid.
		displayboard();											//this will display the board to show where exactly the key is positioned.
	}

	int checkboard() {
		if (this->checkcols() == true || this->checkrows() == true || this->checkdiagonalone() == true || this->checkdiagonaltwo() == true) {
			count--;											//if any of the above function is true, it means we have a winner. count is decremented bcoz the last turn was valid nd count was already incremented for the next player but the winner 'll be the prevoius player.
			return 1;
		}
		else if ((this->checkcols() == false && this->checkrows() == false && this->checkdiagonalone() == false && this->checkdiagonaltwo() == false) && matrixIsFull() == true)
			return -1;											//if there's no winner and the grid is full then the match is draw.
		return 0;												//no winner or draw. means there can be more moves.
	}

	bool matrixIsFull() {
		bool check = false;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (matrix[i][j] == 1 || matrix[i][j] == 0)		//if the matrix have 0 or 1 it means it's full
					check = true;
				else {
					check = false;								//if any other value is found (-1) then it's not empty nd will jump out of loop
					break;
				}
			}
			if (check == false)									//if check is false (there is -1) then break out of this loop as well
				break;
		}
		return check;
	}

	bool checkrows() {
		bool check = false;
		for (int i = 0; i < rows; i++) {
			int c = 1, d = 1;									//c and d are initialized with 1 because the first element will always be taken in 'value'
			if (!this->rowisEmpty(i)) {							//if the row is not empty
				int value = matrix[i][0];						//first element of every row is taken
				for (int j = 1; j < cols; j++) {
					if (matrix[i][j] == value && value == 0)	//if the first element of the row is 0 and the next is equal to 'value' then c is inremented
						c++;									
					else if (matrix[i][j] == value && value== 1)//if the first element of the row is 1 and the next is equal to 'value' then d is inremented
						d++;
				}
				if (c == rows || d == rows) {					//if all the elements of the row are same (either 0 or 1) then a row is same and we have a winner else the loop will continue to check the other row.
					check = true;
					return check;
				}
			}
			else												//if the row is not empty then there's no winner yet(no need to check row)
				check = false;
		}
		return check;
	}

	bool rowisEmpty(int i) {
		bool empty = false;
		int value;
		value = matrix[i][0];									//first element of the row is taken
		for (int j = 1; j < cols; j++) {
			if (matrix[i][j] == value && value == -1)			//all other elements of the row is compared with the first one and will be true if its -1
				empty = true;
			else {
				empty = false;									//if any element is not empty(-1) then break out of the loop
				break;
			}
		}
		return empty;
	}
	
	bool checkcols() {
		bool check = false;
		for (int i = 0; i < cols; i++) {
			int c = 1, d = 1;									//c and d are initialized with 1 because the first element will always be taken in 'value'
			if (!this->colisEmpty(i)) {							//if the cols is not empty then perform the following instructions
				int value = matrix[0][i];						//first element of every column is taken
				for (int j = 1; j < rows; j++) {
					if (matrix[j][i] == value && value == 0)	//if the first element of the column is 0 and the next element in the column is equal to 'value' then c is inremented
						c++;
					else if (matrix[j][i] == value && value== 1)//if the first element of the column is 1 and the next element in the column is equal to 'value' then d is inremented
						d++;
				}
				if (c == cols || d == cols) {					//if all the elements of the column are same(either 0 or 1) then a col is same & we have a winner else the loop will continue to check the other col.
					check = true;
					return check;
				}
			}
			else												//if the column is not empty then there's no winner yet(no need to check the col)
				check = false;
		}
		return check;
	}

	bool colisEmpty(int i) {
		bool empty = false;
		int value;
		value = matrix[0][i];									//first element of the column is taken
		for (int j = 1; j < rows; j++) {
			if (matrix[j][i] == value && value == -1)			//all other elements of the column is compared with the first one and will be true if its empty(-1)
				empty = true;
			else {
				empty = false;									//if any element is not empty(-1) then break out of the loop
				break;
			}
		}
		return empty;
	}

	bool checkdiagonalone() {
		int value = matrix[0][0], c = 1, d = 1;					//the first element of first row is taken & c,d are initialized with 1 bcoz the first elemnt is already counted
		for (int i = 1; i < rows; i++) {
			if (matrix[i][i] == value && value == 0)			//if 'value' is 0 and the next element in the diagonal is equal to it, then c is inremented
				c++;
			else if (matrix[i][i] == value && value == 1)		//if 'value' is 1 and the next element in the diagonal is equal to it, then d is inremented
				d++;
			else												//if 'value' is -1 then return false coz the diagonal is still empty(no winner)
				return false;
		}
		if (c == rows || d == rows)								//if all the elements of the diagonal are same(either 0 or 1) then we have a winner else return false.
			return true;
		return false;
	}

	bool checkdiagonaltwo() {
		int value = matrix[0][cols-1], c = 1, d = 1;			//the last element of first row is taken & c,d are initialized with 1 bcoz the first elemnt is already counted
		for (int i = cols - 1 - 1, j = 1; i <= 0, j < rows; i--, j++) {
			if (matrix[j][i] == value && value == 0)			//if 'value' is 0 and the next element in the diagonal is equal to it, then c is inremented
				c++;
			else if (matrix[j][i] == value && value == 1)		//if 'value' is 1 and the next element in the diagonal is equal to it, then d is inremented
				d++;
			else												//if 'value' is -1 then return false coz the diagonal is still empty(no winner)
				return false;
		}
		if (c == rows || d == rows)								//if all the elements of the diagonal are same(either 0 or 1) then we have a winner else return false.
			return true;
		return false;
	}

	void displayboard() {
		cout << "\n\tPLAYER 1: x\n\tPLAYER 2: o\n";				//will be displayed to show which player has which mark
		//following lines print the box around the grid.(hardcoded for 3x3, 4x4 & 5x5)
		if (rows == 3) {
			cout << setw(4) << " _____ _____ _____ " << endl;
			cout << setw(4) << "|     |     |     |" << endl;
		}
		else if (rows == 4) {
			cout << setw(4) << " _____ _____ _____ _____ " << endl;
			cout << setw(4) << "|     |     |     |     |" << endl;
		}
		else if (rows == 5) {
			cout << setw(4) << " _____ _____ _____ _____ _____ " << endl;
			cout << setw(4) << "|     |     |     |     |     |" << endl;
		}
		else if (rows == 6) {
			cout << setw(4) << " _____ _____ _____ _____ _____ _____ " << endl;
			cout << setw(4) << "|     |     |     |     |     |     |" << endl;
		}
		int c = 0;
		for (int j = 0; j < rows; j++) {
			for (int k = 0; k < cols; k++) {
				if (matrix[j][k] == -1)							//if the position is empty then print its index+1
					cout << '|' << setw(3) << (j*cols + k) + 1 << "  ";
				else if (matrix[j][k] == 1)						//if the position have 1 then print x
					cout << '|' << setw(3) << 'x' << "  ";
				else if (matrix[j][k] == 0)						//if the position have 0 then print o
					cout << '|' << setw(3) << 'o' << "  ";
			}
			if (rows == 3) {
				cout << '|' << endl << setw(4) << "|_____|_____|_____|" << endl;
				if (c != rows - 1)
					cout << setw(4) << "|     |     |     |" << endl;
				c++;
			}
			else if (rows == 4) {
				cout << '|' << endl << setw(4) << "|_____|_____|_____|_____|" << endl;
				if (c != rows - 1)
					cout << setw(4) << "|     |     |     |     |" << endl;
				c++;
			}
			else if (rows == 5) {
				cout << '|' << endl << setw(4) << "|_____|_____|_____|_____|_____|" << endl;
				if (c != rows - 1)
					cout << setw(4) << "|     |     |     |     |     |" << endl;
				c++;
			}
			else if (rows == 6) {
				cout << '|' << endl << setw(4) << "|_____|_____|_____|_____|_____|_____|" << endl;
				if (c != rows - 1)
					cout << setw(4) << "|     |     |     |     |     |     |" << endl;
				c++;
			}
		}
		cout << endl;
		//after displaying check the board, whether we have a winner yet or not.
		if (checkboard() == 1) {								//if the function returns 1 then we have a winner. output accordingly
			cout << "!---- PLAYER ";
			if (count % 2 == 0)
				cout << 1 << " WINS ----!\n" << endl;
			else if (count % 2 != 0)
				cout << 2 << " WINS ----!\n" << endl;
		}
		else if (checkboard() == 0)								//if there's no winner yet then again take input from user
			insertvalue();
		else if (checkboard() == -1)							//if -1 returns, it means the match is draw
			cout << "!---- MATCH IS DRAW. ----!\n" << endl;
	}

	bool playAgain() {
		system("pause");
		system("cls");											//clears the screen
		cout << "\nDo you want to play again? (y/n): ";			//ask the user if he/she want to play again
		char ch;
		cin >> ch;
		if (ch == 'y' || ch == 'Y')								//if she wants to play return true else false
			return true;
		else 
			return false;
	}
};
int main() {

	int i = 0;
	do {
		tictactoe obj;
		i = obj.playAgain();
	} while (i);												//continue playing while the user press y or Y. End the game otherwise.
	cout << "\n\t\t\tTHANK YOU FOR PLAYING\n\n";
	
	return 0;
}
