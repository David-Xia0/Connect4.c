/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"


/*
 David Xiao 
 StudentID: 139114362
 UserID: dxia063
*/

int SecondPlacePrize (int prize1, int prize2, int prize3)
{
	//This function takes three input integers and returns the middle value

	int prize[3] = { 0 };
	int low, high, med;
	med = 0;
	int i,j,k;

	//store input variables into array
	prize[0] = prize1;
	prize[1] = prize2;
	prize[2] = prize3;

	// find the lowest prize
	low = 0;
	for (i = 1; i < 3; i++){
		if (prize[i] <= prize[low])
			low = i;
	}

	// find the highest prize
	high = 0;
	for (j = 1; j < 3; j++){
		if (prize[j] >= prize[high])
			high = j;
	}

	// find the prize that is not either the highest or the lowest
	for (k = 0; k < 3; k++){
		if (k != high && k != low)
			med=k;
	}
	return prize[med];
}

int FourInARow(int values[], int length)
{
	// This function checks a 1D array for 4 in a rows
	// This function takes two inputs: an array of integers and the length of the array.
    // The function returns the index position of the first element in the array that begins a four in a row sequence
    // If the array does not contian a 4 in a row the function returns -1.
	
	int i, j;
	j = 0;
	int temp;// stores the current value that is being checked for 4 in a rows
	int pos=0;
	temp = values[0];

	for (i = 1; i < length; i++){
		//check if the previous value is the same as the current value
		if (temp != values[i]){
			pos = i;// stores position of the first repeating value
			j = 1;

			temp = values[i];
		}
		else {// if value is the same, j records how many in a  rowB
			j++;
		}
		if (j == 4)// if 4 in a row are the same the position of the first is returned
			return pos;
	}
	return -1;
}

int BinaryToDecimal(int binary)
{
	//This function Converts from binary to decimal
	// the input is a single binary number 
	// the output returns the decimal value of the binary number

	int i;
	int length=0;
	int decimal,temp;
	int bin[100] = { 0 }; //int array used to store 1 and 0
	
	length = 0;
	// find the number of digits, and store the digits in an array
	do {
		bin[length]=binary%2;//determines if current digit is 1 or 0
		
		binary=binary/10;// finds out how many digits there are in the binary

		length++;
	} while (binary > 0);
	
	// calculate the decimal value of the binary number
	decimal = 0;
	temp = 1;
	for (i = 0; i<length; i++){
		if (bin[i] == 1){
			decimal = decimal + temp;
		}
		temp = 2 * temp;//each increasing digit value increases the power of the 2
	}
	
	return decimal;
}

double MedianAbility (double abilities[], int length)
{

	//This function finds the median in an array
	//the 2 inputs: an array of double values and the length of the array
	//The output is the median value of the array

	int i, j;
	double temp;
	j = 0;

	//while loop only stops if all the values are in order of increaseing magnitude
	while (j == 0){
		temp = abilities[0];
		j = 1;
		
		for (i = 1; i < length; i++){
			// checks if values are increasing in order of magnitude, and swaps if they are not
			if (abilities[i] < temp){
				abilities[i - 1] = abilities[i];
				abilities[i] = temp;
				j = 0;
			}
			temp = abilities[i];
		}
	}

	//checks if length of array is even, median is then mean of the 2 middle values
	if (length % 2 == 0){
		return (abilities[length / 2] + abilities[length / 2 - 1]) / 2;
	}

	//returns median value
	return abilities[length/2];
}

void RemoveSpaces(char *name)
{

	// This function removes all unnecessary spacing in a string array
	// Single input of a pointer string array


	int length = strlen (name);
	int i;
	int j;
	
	for (i=0;i<length;i++){
		//cycles through each element and checks if there are repeating spaces
		if ((name[i] == ' ')&&(name[i + 1] == ' ')){

			//removes repeating space, by shifting whole array after space to the left
			for (j = i; j < length; j++){
				name[j] = name[j + 1];
			}
			i--;//scan for same i value again, incase there are more than 1 repeating space
		}
	}
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	//This function creates our connect 4 board depending ont he size wanted
	// The 2 inputs: board array that the connect 4 is to be played on, and the size of our board
	
	int i,j;

	for (i = 0; i < size; i++){
		for (j = 0; j < size; j++){
			board[i][j] = 0; 
			// goes through the wanted board size and sets all elements to 0 in the board of desired size

			//finds mid point 
			if (i == size / 2 && j == size / 2){
				//sets midpoints to 3
				if (size % 2) {
					board[i][j] = 3;
				}
				else{//checks for multiple or single midpoints
					board[i][j] = 3;
					board[i - 1][j] = 3;
					board[i - 1][j - 1] = 3;
					board[i][j - 1] = 3;
				}
			}
		}
	}
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{

	// This function adds a move to our board array depending on the side and move input by the player
	//The function returns the co-ordinate position of the place token through pointers lastRow and lastCol
	   
	int i;
	
	
	//checks to determine which side of the board to input from
	if (side == 'N'){
		for (i = 0; i < size; i++){

			if (board[i][move] != 0){//check if current/next space is clear
				*lastRow = i - 1;
				*lastCol = move;
				i = size;
				
			}
			else if ((i == size-1) && (board [i][move]==0)){ //if end of board is reached without obsticles place token
				*lastRow = i;
				*lastCol = move;
				
			}
		}
	}
	else if (side == 'E'){
		for (i = size-1; i >=0; i--){
			if (board[move][i] != 0){//check if current/next space is clear
				*lastRow = move;
				*lastCol = i+1;
				i = -1;
				
			}
			else if (i == 0 && board[move][i] == 0){//if end of board is reached without obsticles place token
				*lastRow = move;
					* lastCol = 0;
					
			}
		}
	}
	else if (side == 'S'){
		for (i = size-1; i >= 0; i--){
			if (board[i][move] != 0){//check if current/next space is clear
				*lastRow = i + 1;
				*lastCol = move;
				i = -1;
				
			}
			else if (i == 0 && board[i][move] == 0){//if end of board is reached without obsticles place token
				*lastRow = 0;
				*lastCol = move;
				
			}
		}
	}
	else if (side == 'W'){
		

		for (i = 0; i < size; i++){
			if (board[move][i] != 0){//check if current/next space is clear
				*lastRow = move;
				*lastCol = i-1;
				i = size;
			}
			else if ((i == size - 1) && (board[move][i] == 0)){//if end of board is reached without obsticles place token
				*lastRow = move;
				*lastCol = i;
			}
		}
	}

	// if the move results in no place of the token -1 and -1 are returned
	if (*lastRow == size || *lastCol ==size || *lastRow ==-1 || *lastCol==-1){
		*lastCol = -1;
		*lastRow = -1;
	}
	else{
		board[*lastRow][*lastCol ] = player;//else a move is made and printed onto the board
		
	}
}

int FourNotZero (int slice[], int size)
{
	//HELPER FUNCTION
	//This function checks if there is a four in a row for any number, excluding zero
	// inputs: slice array and size of array
	// output: true or false depending on if there are any 4 in a rows

	int i;
	int j = 1;
	int temp;// stores the previous value in the array, used to check for 4 in a rows
	

	temp = slice[0];
	for (i = 0; i < size-1; i++) {
		
		//check if the previous value is the same as the current value
		if (temp != slice[i+1]) {
			
			j = 1;

			temp = slice[i+1];
		}
		else{// if value is the same, j records how many in a  rowB
			j++;
		}
        // if 4 in a row are the same the position of the first is returned
		if (j == 4 && temp != 0){
			return 1;
		}
	}
	return 0;
}

int CheckGameOver (int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{

	//This fucntion scans around the last move made by the player to check for any four in a rows 
	//If there are 4 in a rows, then the game is over and the player who won is returned 

	int i,j;
	int times = 0;
	
	//checks to see if last counter input was valid
	if (row == -1 || col == -1){
		return 0;
	}

	//checks if there are anymore possible moves
	for (i = 0; i < size; i++) {
			if ((board[0][i] != 0)&& (board[size - 1][i] != 0) && (board[i][0] != 0) && (board[i][size - 1] != 0) ){
				times++;
			}
	}
	if (times == size) {
		return player;
	}

	int slice[MAX_SIZE];// take slices of the board(horizontally, vertically and diagonally) and check for 4 in a rows

	for (i = 0; i < size; i++) {
		slice[i] = board[row][i];
	}
	if (FourNotZero (slice, size)) { //horizontal slice is checked for 4 in a rows

		return player;
	}


	for (i = 0; i < size; i++) {
		slice[i] = board[i][col];
	}
	if (FourNotZero (slice, size)) {// vertical slice is checked for 4 ina  rows
		return player;
	}
	
	
	for (i = 0; i < MAX_SIZE; i++){
		slice[i] = 0;
	}

	// check diagonals from last placed token, with co-ordinates row and col
	int shift;
	// top left to bottom right diagonals
	if (row >= col) {
		shift = row - col;
		j = shift;
		for (i = 0; i < size - shift; i++) {
			slice[i] = board[j][i];// the diagonal the last played token is sitting on
			j++;
		}
		if (FourNotZero (slice, size)) {
			return player;
		}
	}
	else if (row < col) {
		shift = col - row;
		j = shift;
		for (i = 0; i < size - shift; i++) {
			slice[i] = board[i][j];// the diagonal the last played token is sitting on
			j++;
		}
		if (FourNotZero (slice, size)) {
			return player;
		}
	}

	j = 0;
	for (i = 0; i < MAX_SIZE; i++) {
		slice[i] = 0;
	}


	//bottom left to top right diagonals
	if ((row + col >= size) && (row + col < 2 * size - 4)) {

		shift = col + row;
		for (i = size; i > shift - size; i--) {
			slice[j] = board[shift - i][i];// the diagonal the last played token is sitting on
			j++;
		}
		if (FourNotZero (slice, size)) {
			return player;
		}
	}
	else if ((row + col > 2)&&(row+col<2*size-4)) {
		shift = col + row;
		for (i = 0; i < shift + 1; i++) {
			slice[j] = board[i][shift - i];// the diagonal the last played token is sitting on
			j++;
		}
		if (FourNotZero (slice, size)) {
			return player;
		}
	}

	
	return 0;

}

void GetDisplayBoardString (int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	//This function takes the board playing board and  size and a string buffer
	//and writes out a string array to be displayed into the string buffer
	//the string array produced will be the visualisation of the playing board

	// declare outer boarders for the different possible sizes boards
	char board4[] = "--NNNN--\n--0123--\nW0%%%%0E\nW1%%%%1E\nW2%%%%2E\nW3%%%%3E\n--0123--\n--SSSS--\n\0";
	char board5[] = "--NNNNN--\n--01234--\nW0%%%%%0E\nW1%%%%%1E\nW2%%%%%2E\nW3%%%%%3E\nW4%%%%%4E\n--01234--\n--SSSSS--\n\0";
	char board6[] = "--NNNNNN--\n--012345--\nW0%%%%%%0E\nW1%%%%%%1E\nW2%%%%%%2E\nW3%%%%%%3E\nW4%%%%%%4E\nW5%%%%%%5E\n--012345--\n--SSSSSS--\n";
	char board7[] = "--NNNNNNN--\n--0123456--\nW0%%%%%%%0E\nW1%%%%%%%1E\nW2%%%%%%%2E\nW3%%%%%%%3E\nW4%%%%%%%4E\nW5%%%%%%%5E\nW6%%%%%%%6E\n--0123456--\n--SSSSSSS--\n\0";
	char board8[] = "--NNNNNNNN--\n--01234567--\nW0%%%%%%%%0E\nW1%%%%%%%%1E\nW2%%%%%%%%2E\nW3%%%%%%%%3E\nW4%%%%%%%%4E\nW5%%%%%%%%5E\nW6%%%%%%%%6E\nW7%%%%%%%%7E\n--01234567--\n--SSSSSSSS--\n\0";
	char board9[] = "--NNNNNNNNN--\n--012345678--\nW0%%%%%%%%%0E\nW1%%%%%%%%%1E\nW2%%%%%%%%%2E\nW3%%%%%%%%%3E\nW4%%%%%%%%%4E\nW5%%%%%%%%%5E\nW6%%%%%%%%%6E\nW7%%%%%%%%%7E\nW8%%%%%%%%%8E\n--012345678--\n--SSSSSSSSS--\n\0";
	char board10[] = "--NNNNNNNNNN--\n--0123456789--\nW0%%%%%%%%%%0E\nW1%%%%%%%%%%1E\nW2%%%%%%%%%%2E\nW3%%%%%%%%%%3E\nW4%%%%%%%%%%4E\nW5%%%%%%%%%%5E\nW6%%%%%%%%%%6E\nW7%%%%%%%%%%7E\nW8%%%%%%%%%%8E\nW9%%%%%%%%%%9E\n--0123456789--\n--SSSSSSSSSS--\n\0";

	// depending on board size assign an outer layer
	if (size == 4){
		strcpy (boardString, board4);
	}
	else if (size == 5){
		strcpy (boardString, board5);
	}
	else if (size == 6){
		strcpy (boardString, board6);
	}
	else if (size == 7){
		strcpy (boardString, board7);
	}
	else if (size == 8){
		strcpy (boardString, board8);
	}
	else if (size == 9){
		strcpy (boardString, board9);
	}
	else if (size == 10){
		strcpy (boardString, board10);
	}

	int i = 0;
	int j = 0;
	int k;

	// fill the rest of the board in according the the 'board' array
	do {
		if (boardString[i] == '%') {
			k = j / size;
			if (board[k][j % (size)] == 0){
				boardString[i] = '.';
			}
			else if (board[k][j%size] == 1){
				boardString[i] = 'X';
			}
			else if (board[k][j%size] == 2){
				boardString[i] = 'O';
			}
			else if (board[k][j%size]==3){
				boardString[i] = '#';
			}
			j++;
		}
		i++;
	} while (j < size * size);// while loop finishes when all extra board pieces have been placed
}

int validMove (int board[MAX_SIZE][MAX_SIZE], int size, char side, int move)
{
	//This function checks if the move made by bot is valid
	// inputs: playing board, size and move to be made
	// output: true or false, whether move is valid or not


	int i, j;
	int lastRow = 0;
	int lastCol=0;
	//checks to determine which side of the board to input from
	if (side == 'N') {
		for (i = 0; i < size; i++) {
			if (board[i][move] != 0) {//check if current/next space is clear
				lastRow = i - 1;
				lastCol = move;
				i = size;
			}
			else if ((i == size - 1) && (board[i][move] == 0)) {
				lastRow = i;
				lastCol = move;
			}
		}
	}
	else if (side == 'E') {
		for (j = size - 1; j >= 0; j--) {
			if (board[move][j] != 0) {//check if current/next space is clear
				lastRow = move;
				lastCol = j + 1;
				j = -1;
			}
			else if (j == 0 && board[move][0] == 0) {
				lastRow = move;
				lastCol = 0;
			}
		}
	}
	else if (side == 'S') {
		for (i = size - 1; i >= 0; i--) {
			if (board[i][move] != 0) {//check if current/next space is clear
				lastRow = i + 1;
				lastCol = move;
				i = -1;
			}
			else if (i == 0 && board[0][move] == 0) {
				lastRow = 0;
				lastCol = move;
			}
		}
	}
	else if (side == 'W') {
		for (j = 0; j < size; j++) {
			if (board[move][j] != 0) {//check if current/next space is clear
				lastRow = move;
				lastCol = j - 1;
				j = size;
			}
			else if ((j == size - 1) && (board[move][j] == 0)) {
				lastRow = move;
				lastCol = j;
			}
		}
	}

	if (lastRow >= size || lastCol >= size || lastRow <= -1 || lastCol <= -1) {//checks if move valid
		lastCol = -1;
		lastRow = -1;
	}

	if (lastRow < 0 || lastCol < 0 || lastCol>=size ||lastRow>=size){// if move is invalid 0 is returned
		return 0;
	}
	else{// if move is valied true is returned
		return 1;
	}	
}

int WinningMove (int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	//THis function performs every move possible and checks if there is a move that will end the game
	//If there is a winning move then the output will produce true, else false.
	int i,j,k;
	char direction;
	int Row, Col;
	int Newboard[MAX_SIZE][MAX_SIZE];

	 
	for (i = 0; i < size; i++) {
	//cycle through each possible move and check if any result in win
	//if winning move is possible play that move
		
		for (k = 0; k < MAX_SIZE; k++) {
			for (j = 0; j < MAX_SIZE; j++) {
				Newboard[k][j] = board[k][j];
			}
		}
		
		direction = 'N';
		// Adds move to a test board and sees if game is won
		AddMoveToBoard (Newboard, size, direction, i, player, &Row, &Col);
		if (CheckGameOver (Newboard, size, player, Row, Col) > 0)// if game is won, move is returned from function
		{
			*side = direction;
			*move = i;
			return 1;
		}

		for (k = 0; k < MAX_SIZE; k++) {
			for (j = 0; j < MAX_SIZE; j++) {
				Newboard[k][j] = board[k][j];
			}
		}

		direction = 'W';
		// Adds move to a test board and sees if game is won
		AddMoveToBoard (Newboard, size, direction, i, player, &Row, &Col);
		if (CheckGameOver (Newboard, size, player, Row, Col) > 0)// if game is won, move is returned from function
		{
			*side = direction;
			*move = i;
			return 1;
		}
		
		for (k = 0; k < MAX_SIZE; k++) {
			for (j = 0; j < MAX_SIZE; j++) {
				Newboard[k][j] = board[k][j];
			}
		}

		direction = 'E';
		// Adds move to a test board and sees if game is won
		AddMoveToBoard (Newboard, size, direction, i, player, &Row, &Col);
		if (CheckGameOver (Newboard, size, player, Row, Col) > 0)// if game is won, move is returned from function
		{
			*side = direction;
			*move = i;
			return 1;
		}
		
		for (k = 0; k < MAX_SIZE; k++) {
			for (j = 0; j < MAX_SIZE; j++) {
				Newboard[k][j] = board[k][j];
			}
		}
		
		direction = 'S';
		// Adds move to a test board and sees if game is won
		AddMoveToBoard (Newboard, size, direction, i, player, &Row, &Col);
		if (CheckGameOver (Newboard, size, player, Row, Col) > 0)// if game is won, move is returned from function
		{
			*side = direction;
			*move = i;
			return 1;
		}
	}
	return 0;// no winning move and false is returned
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	//This function produces my bot move
	//the bot produces a random move unless there is a winning move that can be made

	srand ((unsigned int)time (NULL));// srand is seeded

	int direction;
	int position;
	

	if (WinningMove(board, size, player, side, move)){//check if there is a winning move and play the move
		WinningMove (board, size, player, side, move);
		return;
	}

	do {// produce a random move
		position = (rand () % size);
		direction = (rand () % 4);

		if (direction == 0) {
			*side = 'N';
		}
		else if (direction == 1) {
			*side = 'E';
		}
		else if (direction == 2) {
			*side = 'S';
		}
		else if (direction == 3) {
			*side = 'W';
		}

		*move = position;
	}while(!validMove (board, size, *side, *move));// checks if move is valid, if invalid another move is generated
	return;
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	//This function produces my bot move
	//the bot produces a random move unless there is a winning move that can be made

	srand ((unsigned int)time (NULL));// srand is seeded

	int direction;
	int position;


	if (WinningMove (board, size, player, side, move)) {//check if there is a winning move and play the move
		WinningMove (board, size, player, side, move);
		return;
	}

	do {// produce a random move
		position = (rand () % size);
		direction = (rand () % 4);

		if (direction == 0) {
			*side = 'N';
		}
		else if (direction == 1) {
			*side = 'E';
		}
		else if (direction == 2) {
			*side = 'S';
		}
		else if (direction == 3) {
			*side = 'W';
		}

		*move = position;
	} while (!validMove (board, size, *side, *move));// checks if move is valid, if invalid another move is generated
	return;
}
