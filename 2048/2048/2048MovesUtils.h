

bool isValidBoard(int choice);
int takeBoardInput();
bool isValidMove(char letter);
char getInput();
bool play2048(Board* board, char direction, int* fiboArray);
bool performNorth(Board* board, int* fiboArray);
bool performSouth(Board* board, int* fiboArray);
bool performWest(Board* board, int* fiboArray);
bool performEast(Board* board, int* fiboArray);
void mergeRow(int*, int, char, int*);


void rotateLeft(Board* board) {

	int i, j, n = board->rows;
	int tmp;
	for (i = 0; i<n / 2; i++) {
		for (j = i; j<n - i - 1; j++) {
			tmp = board->table[i][j];
			board->table[i][j] = board->table[j][n - i - 1];
			board->table[j][n - i - 1] = board->table[n - i - 1][n - j - 1];
			board->table[n - i - 1][n - j - 1] = board->table[n - j - 1][i];
			board->table[n - j - 1][i] = tmp;
		}
	}

}

void rotateRight(Board* board) {


	int i, j, n = board->rows;
	int tmp;
	for (i = 0; i<n / 2; i++) {
		for (j = i; j<n - i - 1; j++) {
			tmp = board->table[i][j];
			board->table[i][j] = board->table[n - j - 1][i];
			board->table[n - j - 1][i] = board->table[n - i - 1][n - j - 1];
			board->table[n - i - 1][n - j - 1] = board->table[j][n - i - 1];
			board->table[j][n - i - 1] = tmp;
		}
	}
}


bool performNorth(Board* board, int* fiboArray){


	int i = 0;

	rotateRight(board);

	for (i = 0; i<board->rows; i++){

		mergeRow(board->table[i], board->rows, 'r', fiboArray);

	}

	rotateLeft(board);

	return true;

}

bool performSouth(Board* board, int* fiboArray){


	int i = 0;

	rotateRight(board);

	for (i = 0; i<board->rows; i++){

		mergeRow(board->table[i], board->rows, 'l', fiboArray);

	}

	rotateLeft(board);

	return true;

}


bool performWest(Board* board, int* fiboArray){


	int i = 0;


	for (i = 0; i<board->rows; i++){

		mergeRow(board->table[i], board->rows, 'l', fiboArray);

	}


	return true;

}

bool performEast(Board* board, int* fiboArray){


	int i = 0;


	for (i = 0; i<board->rows; i++){

		mergeRow(board->table[i], board->rows, 'r', fiboArray);

	}


	return true;

}



bool play2048(Board* board, char direction, int* fiboArray){

	bool success;

	if (direction == 'W' || direction == 'w'){

		success = performNorth(board, fiboArray);
		return success;

	}


	else if (direction == 'S' || direction == 's'){

		success = performSouth(board, fiboArray);
		return success;
	}

	else if (direction == 'A' || direction == 'a'){

		success = performWest(board, fiboArray);
		return success;
	}

	else if (direction == 'D' || direction == 'd'){

		success = performEast(board, fiboArray);
		return success;

	}

	else
		return false;

}




bool isPairFibo(int n1, int n2, int* fibo, int n){

	int i;
	

	if (n1 == n2 && n1 != 1 && n2 != 1)
		return false;

	if (n1 == 1 && n2 == 1)
		return true;

	if (n1 == 1 && n2 == 2)
		return true;

	if (n1 == 2 && n1 == 1)
		return true;

	for (i = 0; i <= (2 * n*n); i++){

		if (fibo[i] == n1){

			if (i>0 && fibo[i - 1] == n2)
				return true;

			else if (i<(2 * n*n) && fibo[i + 1] == n2)
				return true;

			else
				return false;

		}
	}

	return false;
}


int* getFibo(int boardSize){

	int i;
	int* array = (int*)malloc(((2 * boardSize*boardSize) + 1)*sizeof(int));

	array[0] = 1;
	array[1] = 1;

	for (i = 2; i <= (2 * boardSize*boardSize); i++){

		array[i] = array[i - 1] + array[i - 2];

	}

	return array;

}



void moveLeft(int* arr, int n){

	int count = 0;
	int i = 0;

	for (i = 0; i < n; i++)
		if (arr[i] != 0)
			arr[count++] = arr[i];

	while (count < n)
		arr[count++] = 0;

}

void moveRight(int* arr, int n){

	int count = n - 1;
	int i = n - 1;

	for (i; i >= 0; i--)
		if (arr[i] != 0)
			arr[count--] = arr[i];

	while (count >= 0)
		arr[count--] = 0;
}


void mergeRow(int *row, int len, char direction, int* fiboArray) {


	if (row == NULL)
		return;

	if (len <= 0)
		return;

	bool flag = false;

	if (direction == 'l' || direction == 'r')
		flag = true;


	if (!flag)
		return;

	int* arr = fiboArray;

	int i;
	

	if (direction == 'l'){

		for (i = len - 1; i>0; i--){

			if (row[i] == 0)
				continue;

			if (row[i] == row[i - 1]){

				if (row[i] == 1 && row[i - 1] == 1){

					row[i - 1] = 2;
					row[i] = 0;
				}
				else
					continue;
			}

			else{

				if (row[i - 1] == 0){

					int j = i - 1;
					for (j; j >= 0; j--){

						if (row[j] == 0)
							continue;
						else if (isPairFibo(row[i], row[j], arr, len)){

							row[j] = row[j] + row[i];
							row[i] = 0;
							i = j;
							break;
						}
						else
							break;

					}
				}

				else if (isPairFibo(row[i], row[i - 1], arr, len)){

					row[i - 1] = row[i - 1] + row[i];
					row[i] = 0;

				}
			}
		}


		moveLeft(row, len);
	}


	else if (direction == 'r'){

		for (i = 0; i < len - 1; i++){

			if (row[i] == 0)
				continue;

			if (row[i] == row[i + 1]){

				if (row[i] == 1 && row[i + 1] == 1){

					row[i + 1] = 2;
					row[i] = 0;
				}
				else
					continue;
			}


			else{

				if (row[i + 1] == 0){

					int j = i + 1;
					for (j; j<len; j++){

						if (row[j] == 0)
							continue;

						else if (isPairFibo(row[i], row[j], arr, len)){

							row[j] = row[j] + row[i];
							row[i] = 0;
							i = j;
							break;
						}
						else
							break;

					}
				}

				else if (isPairFibo(row[i], row[i + 1], arr, len)){

					row[i + 1] = row[i + 1] + row[i];
					row[i] = 0;

				}
			}
		}
		moveRight(row, len);
	}


	return;


}



int takeBoardInput(){

	int input;

	bool flag = false;
	bool check = false;


	do{

		if (check)
			printf("\n\tWrong Choice Selected! Enter Choice(2 or 4) ");
		check = true;
		printf("\n\tEnter Choice : ");
		scanf_s(" %d", &input);
		flag = isValidBoard(input);

	} while (flag != true);

	return input;

}


char getInput(){

	char input;

	bool flag = false;
	bool check = false;

	do{

		if (check==true)
			printf("\n\tWrong Move Selected! Enter Move Again ");
		check = true;
		printf("\n\tEnter Choice : ");
		scanf_s(" %c", &input);
		flag = isValidMove(input);

	} while (flag != true);

	return input;


}
bool isValidBoard(int choice){

	if (choice == 2 || choice == 4)
		return true;


	return false;

}


bool isValidMove(char letter){

	if (letter == 'a' || letter == 's' || letter == 'd' || letter == 'w')
		return true;

	else if (letter == 'A' || letter == 'S' || letter == 'D' || letter == 'W')
		return true;

	return false;


}

bool isValidWelcome(int choice){

	if (choice == 1 || choice == 2 || choice ==3 || choice == 4)
		return true;


	return false;

}


int getWelcomeOption(){

	int input;

	bool flag = false;
	bool check = false;


	do{

		if (check)
			printf("\n\tWrong Choice Selected! Enter Choice(1 to 4) ");
		check = true;
		printf("\n\n\tEnter Choice (1-4): ");
		scanf_s(" %d", &input);
		flag = isValidWelcome(input);

	} while (flag != true);

	return input;

}
