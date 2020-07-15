/* ENGGEN131 Project - C Project - 2019 */
/* The Warehouse */
/*
Author: Holly Knowles
Username: hkno470
ID: 281861078
*/
#include "project.h"

/*
TimeWorked function takes in the clock in and clock out times (in minutes and seconds)
and then returns the number of seconds a given worker has worked. the clock in/out times
can be inputted in any order.
*/
int TimeWorked(int minuteA, int secondA, int minuteB, int secondB)
{
	int totalA, totalB, total;
	// converting everything to one unit first (seconds)
	totalA = secondA + minuteA * 60;
	totalB = secondB + minuteB * 60;
	// if statements account for the fact that the order in which the times are inputted can change
	// by taking the difference between highest and lowest magnitude times
	if (totalA > totalB) {
		total = totalA - totalB;
	} else {
		total = totalB - totalA;
	}
	return total;
}

/*
helper function created to determine whether a given number is prime
returns 1 if number is prime, 0 if not
*/
int PrimeHelper(int number) {
	// starts at 2 as 2 is the lowest prime number possible
	int i = 2;
	while((i < number) && (number % i != 0)) {
		i++;
	}
	if (i == number) {
		return 1;
	} else {
		return 0;
	}
}
/*
WarehouseAddress function locates the largest address which is a prime number based on the upper 
bound of addresses on the street
goes through all values starting from the number one less than the maximum (to ensure that if the maximum is prime it will not be returned) 
til 2, as soon as a prime number is detected that number will be returned. calls the PrimeHelper helper function
*/
int WarehouseAddress(int maximum)
{
	for (int j = maximum - 1; j >= 2; j--) {
		if (PrimeHelper(j) == 1) {
			return j;
		}
	}
	return 0;
}

/*
Advertise function rotates the characters in an array to the left by one and the final
character will end up in the first space in the array (words[0])
*/
void Advertise(char *words)
{
	int i = 0;
	int temp = words[0];
	while (i < strlen(words) - 1) {
		words[i] = words[i + 1];
		i++;
	}
	words[strlen(words) - 1] = temp;
}

/*
The WinningBid function determines the lowest unique integer within a given array
*/

int WinningBid(int *values, int length)
{
	// this loop sorts through the values array and changes it to be in accending order
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			if (values[j] > values[i]) {
				int temp = values[i];
				values[i] = values[j];
				values[j] = temp;
			}
		}
	}
	// goes through sorted array from lowest to highest and returns the lowest value that is not similar to
	// the rest of the array
	for (int i = 0; i <= length - 1; i++) {
		if (i < length - 1) {
			if ((values[i] != values[i-1]) && (values[i] != values[i+1])) {
				return values[i];
			}
		// accounts for if the smallest unique element is the final element in the array
		// (as you cant compare i + 1 to i as its out of array bounds)
		} else if (i == length - 1) {
			if (values[i] != values[i - 1]) {
				return values[i];
			}
		} 
	}
	// if there is no unique element will just return -1
	return -1;
}

/*
BoxDesign function creates a box of dimensions widthxheight and inputs the characters 
into the design string. the top and bottom consist of astrixes (the amount is the width),new line
characters at the end of each row and the left and right sides will consist of astrixes (the amount is the
height). there will also be 'X's' denoting the middle of the box
*/
void BoxDesign(char *design, int width, int height)
{
	int length = (width + 1) * height;
	for (int i = 0; i < length; i++) {
		// top row
		if (i < width) {
			design[i] = '*';
		// first new line is a doesnt follow pattern of the rest as index starts at 0
		} else if (i == width) {
			design[i] = '\n';
		// new lines for all but the first one
		} else if ((i - width)%(width + 1) == 0) {
			design[i] = '\n';
		// bottom row
		} else if (i >= (length - width - 1)) {
			design[i] = '*';
		// left row
		} else if (i % (width + 1) == 0){
			design[i] = '*';
		// right row
		} else if ((i - width)%(width + 1) == width) {
			design[i] = '*';
		// every other part of string is a space
		} else {
			design[i] = ' ';
		}
	}

	// code for the X's in the centre of the box
	// middle of the string (- 1 as index starts at 0)
	int middle = (length / 2) - 1;
	// when width & height are both odd there will be one X denoting the centre
	// happens when the remainder isnt 0 when divided by 2
	if ((height % 2 != 0) && (width % 2 != 0)) {
		if ((width >= 3) && (height >= 3)) {
			if ((width % 2 != 0) && (height % 2 != 0)) {
			design[middle] = 'X';
			}
		}// when width and height are both odd
		
	// when they both even
	} else if ((height % 2 == 0) && (width % 2 == 0)) {
		if ((width >= 3) && (height >= 3)) {
			design[(length / 2) + ((width / 2))] = 'X';
			design[((length / 2) + (width/ 2) - 1)] = 'X';
			design[((length / 2) - (width / 2) - 1)] = 'X';
			design[((length / 2) - (width / 2) - 2)] = 'X';
		}
	// when height odd width even
	} else if ((height % 2 != 0) && (width % 2 == 0)) {
		if ((width >= 3) && (height >= 3)) {
			design[(length / 2)] = 'X';
			design[(length / 2) - 1] = 'X';
		}
	// when height even width odd
	} else if ((height % 2 == 0) && (width % 2 != 0)) {
		if ((width >= 3) && (height >= 3)) {
			design[((length / 2) + (width - 1) / 2)] = 'X';
			design[((length / 2) - (width + 1) / 2 - 1)] = 'X';
		}
	}
}

/*
WorkerRoute function finds the most efficient route for a worker ('1') to take of a 10x10 array (warehouse)
to a box ('2'). the path that the worker takes will be represented by '3's in the new array (warehouse).
If the worker has to move both horizontally and vertically then it must move horizontally first.
*/

// will mean that the x and y component of the location of the worker and box will be stored
void WorkerRoute(int warehouse[10][10])
{
	int i, j, positionWorkerRows, positionWorkerCols, positionBoxRows, positionBoxCols;
	// goes through array to locate the position of the worker ('1') and box ('2')
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (warehouse[i][j] == 1) {
				positionWorkerRows = i;
				positionWorkerCols = j;
			} 
			if (warehouse[i][j] == 2) {
				positionBoxRows = i;
				positionBoxCols = j;
			}
		}
	}
	/* there is 3 conitions that the worker and box will have: not in same row or column, in same row but not column, and 
	in same colunm but not row. if the worker and box are next to eachother then the code wont execute and there will be no
	'3's on the board */
	if ((positionBoxRows != positionWorkerRows) && (positionBoxCols != positionWorkerCols)) {
	// declaring varibles that will store the last index position of the rows and columns
	// used when the worker has to move horizontally and then vertically
	int lastIndexCols, lastIndexRows;
	// have to move horixontally first
	// condition for when the '1' is on the left of the '2'
		if (positionWorkerCols < positionBoxCols) {
			for (j = positionWorkerCols + 1; j < positionBoxCols + 1; j++) {
				i = positionWorkerRows;
				warehouse[i][j] = 3;
			}
			lastIndexCols = j;
			lastIndexRows = i;
		// condtion for when the '1' is on the right of the '2'
		} else if (positionWorkerCols > positionBoxCols){
			for (j = positionBoxCols; j < positionWorkerCols; j++) {
				i = positionWorkerRows;
				warehouse[i][j] = 3;
			}
			lastIndexRows = i;
			lastIndexCols = j;
		}
		
	// moves vertically second
	// condition for when '1' is above '2'
		if (positionWorkerRows < positionBoxRows) {
			for (i = positionWorkerRows + 1; i < positionBoxRows; i++) {
				j = positionBoxCols;
				warehouse[i][j] = 3;
			}
		// condition for where '1' is below '2'
		} else if (positionWorkerRows > positionBoxRows) {
			for (i = positionBoxRows + 1; i < positionWorkerRows; i++) {
				j = positionBoxCols;
				warehouse[i][j] = 3;
			}
		}
		
	// when in same colunm but not row, the worker needs to only move vertically
	} else if ((positionBoxRows != positionWorkerRows) && (positionBoxCols == positionWorkerCols)) {
		// condition for where '1' is above '2'
		if (positionWorkerRows < positionBoxRows) {
			for (i = positionWorkerRows + 1; i < positionBoxRows; i++) {
				j = positionWorkerCols;
				warehouse[i][j] = 3;
			}
		// condition for where '1' is below '2'
		} else if (positionWorkerRows > positionBoxRows) {
			for (i = positionBoxRows + 1; i < positionWorkerRows; i++) {
				j = positionWorkerCols;
				warehouse[i][j] = 3;
			}
		}
	// when the worker and box are in the same row but not column the worker only has to move horizontally
	} else if ((positionBoxCols != positionWorkerCols) && (positionBoxRows == positionWorkerRows)) {
		// condition for where the '1' is to the left of the '2'
		if (positionWorkerCols < positionBoxCols) {
			for (j = positionWorkerCols + 1; j < positionBoxCols; j++) {
				i = positionWorkerRows;
				warehouse[i][j] = 3;
			}
		// condition for where the '1' is to the right of the '2'
		} else if (positionWorkerCols > positionBoxCols) {
			for (j = positionBoxCols + 1; j < positionWorkerCols; j++) {
				i = positionBoxRows;
				warehouse[i][j] = 3;
			}
		}
	}
}
/*
MakeMove function moves the worker around the warehouse based on whether they input w a s or d
the location of the worker (or worker on target) is found using nested for loops and the movement is
done using pointers and changing the position of given pointer varibles
*/
int MakeMove(int warehouse[10][10], char move)
{
	// workerLocation = the location of the worker
	// position1 = the position of the place adjacent the worker
	// position2 = the position of the place adjacent position1
	int workerRow, workerCol, *workerLocation, *position1, *position2;
	for (int rows = 0; rows < 10; rows++) {
		for (int cols = 0; cols < 10; cols++) {
			// each time there will be only one worker or worker on target
			if ((warehouse[rows][cols] == WORKER) || (warehouse[rows][cols] == WORKER_ON_TARGET)) {
				workerRow = rows;
				workerCol = cols;
			}
		}
	}
	// stores the row and column location of the worker within the warehouse
	workerLocation = &warehouse[workerRow][workerCol];
	// up (which corresponds to a -1 move in row direction)
	if (move == 'w') {
		position1 = &warehouse[workerRow - 1][workerCol];
		position2 = &warehouse[workerRow - 2][workerCol];
	// left (which corresponds to a -1 move in the column direction)
	} else if (move == 'a') {
		position1 = &warehouse[workerRow][workerCol - 1];
		position2 = &warehouse[workerRow][workerCol - 2];
	// down (which corresponds to a +1 move in the rows direction)
	} else if (move == 's') {
		position1 = &warehouse[workerRow + 1][workerCol];
		position2 = &warehouse[workerRow + 2][workerCol];
	// right (which corresponds to a +1 move in the columns direction)
	} else if (move == 'd') {
		position1 = &warehouse[workerRow][workerCol + 1];
		position2 = &warehouse[workerRow][workerCol + 2];
	}
	// condition for where the worker is not on a target and adjacent to a space (position 1) which is also adjacent to a space (position 2)
	// where the adjacent position (either up left down right) is determined by the input (either w a s or d)
	if ((*position1 == SPACE) && (*workerLocation == WORKER)) {
			*position1 = WORKER;
			*workerLocation = SPACE;
	} 
	// condition for where the worker is on a target and adjacent to a space (position 1) which is also adjacent to a space (position 2)
	// where the adjacent position (either up left down right) is determined by the input (either w a s or d)
	else if ((*position1 == SPACE) && (*workerLocation == WORKER_ON_TARGET)) {
			*position1 = WORKER;
			*workerLocation = TARGET;
	// condition for where the worker  on a target and is adjacent to a target (position1)
	} else if ((*position1 == TARGET) && (*workerLocation == WORKER_ON_TARGET)) {
			*position1 = WORKER_ON_TARGET;
			*workerLocation = TARGET;	
	// condition for where the worker is not on a target and is adjacent to a target (position1)
	} else if ((*position1 == TARGET) && (*workerLocation == WORKER)) {
			*position1 = WORKER_ON_TARGET;
			*workerLocation = SPACE;
	}	
	// condition for where the worker is adjacent to a box (position 1) which is adjacent to a space (position 2)
	else if ((*position1 == BOX) && (*position2 == SPACE) && (*workerLocation == WORKER)) {
		*workerLocation = SPACE;
		*position1 = WORKER;
		*position2 = BOX;
	// condition for where worker is not on target, which is adjacent to a box on a target (position1), which is adjacent to a 
	// space (position2)
	} else if ((*position1 == BOX_ON_TARGET) && (*position2 == SPACE) && (*workerLocation == WORKER)) {
		*workerLocation = SPACE;
		*position1 = WORKER_ON_TARGET;
		*position2 = BOX;
	// condition where worker is not on a target, which is adjacent to a box not on a target (position1), which is adjacent to a
	// target (position2)
	} else if ((*position1 == BOX) && (*position2 == TARGET) && (*workerLocation == WORKER)) {
		*workerLocation = SPACE;
		*position1 = WORKER;
		*position2 = BOX_ON_TARGET;
	} 
	// condition for where the worker is on a target which is adjacent to a box which is not on a target (position 1), which is 
	// adjacent to a space (position 2)
	else if ((*position1 == BOX) && (*position2 == SPACE) && (*workerLocation == WORKER_ON_TARGET)) {
		*workerLocation = TARGET;
		*position1 = WORKER;
		*position2 = BOX;
	}
	// condition where the worker is on a target and is adjacent to a box which is on a target (position 1), which is adjacent to
	// a space
	else if ((*position1 == BOX_ON_TARGET) && (*position2 == SPACE) && (*workerLocation == WORKER_ON_TARGET)) {
		*workerLocation = TARGET;
		*position1 = WORKER_ON_TARGET;
		*position2 = BOX;
	}
	// condition for where the worker is on a target which is adjacent to a box which is not on a target (position 1), which is adjacent
	// to a target (position2)
	else if ((*position1 == BOX) && (*position2 == TARGET) && (*workerLocation == WORKER_ON_TARGET)) {
		*workerLocation = TARGET;
		*position1 = WORKER;
		*position2 = BOX_ON_TARGET;
	}
	// condition for where the worker is not on a target which is adjacent to a box which is on a target (position 1) which is adjacent
	// to a target (position 2)
	else if ((*position1 == BOX_ON_TARGET) && (*position2 == TARGET) && (*workerLocation == WORKER)) {
		*workerLocation = SPACE;
		*position1 = WORKER_ON_TARGET;
		*position2 = BOX_ON_TARGET;
	}
	// condition for where the worker is on a target which is adjacent to a box which is on a target (position1) which is adjacent to a target
	// (position 2)
	else if ((*position1 == BOX_ON_TARGET) && (*position2 == TARGET) && (*workerLocation == WORKER_ON_TARGET)) {
		*workerLocation = TARGET;
		*position1 = WORKER_ON_TARGET;
		*position2 = BOX_ON_TARGET;
	}
	// the game is complete once the worker is on a target and all of the boxes are on targets
	// i.e there is no 'WORKER', 'BOX' or 'TARGET' on the board
	// loop goes through array to find them, if a worker box or target is found the counter variable is incremented by 1
	int counter = 0;
	for (int rows = 0; rows < 10; rows++) {
		for (int cols = 0; cols < 10; cols++) {
			if ((warehouse[rows][cols] == WORKER) || (warehouse[rows][cols] == BOX) || (warehouse[rows][cols] == TARGET)) {
				counter++;
			}
		}
	}
	// if counter is 0 then there is no WORKER, BOX or TARGET in the warehouse array and hence the game is complete
	if (counter == 0) {
		return 1;
	} else {
		return 0;
	}
}

