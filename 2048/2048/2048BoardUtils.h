

typedef struct Board {


	int **table;
	int rows;
	int cols;

}Board;


Board * createBoard(int rows, int cols){

	if (rows != cols)
		return NULL;

	if (rows < 1 && cols < 1)
		return NULL;

	int i = 0;
	Board* newBoard = (Board*)calloc(1, sizeof(Board));

	newBoard->rows = rows;
	newBoard->cols = cols;

	newBoard->table = (int**)calloc(rows, sizeof(int*));

	for (i = 0; i<rows; i++)
		newBoard->table[i] = (int*)calloc(cols, sizeof(int));

	return newBoard;
}



void addRandom(Board* board) {

	static bool initialized = false;
	int i, j;
	int r, len = 0;
	int list[16][2];


	if (!initialized) {
		srand(time(NULL));
		initialized = true;
	}

	for (i = 0; i<board->rows; i++) {
		for (j = 0; j<board->rows; j++) {
			if (board->table[i][j] == 0) {
				list[len][0] = i;
				list[len][1] = j;
				len++;
			}
		}
	}

	if (len>0) {
		r = rand() % len;
		i = list[r][0];
		j = list[r][1];
		board->table[i][j] = 1;
	}
}


void drawBoard(Board* board) {

	int i;
	int j;


	for (i = 0; i<board->rows; i++){
		printf("\n\t");
		for (j = 0; j<board->cols; j++){

			printf("%d\t", board->table[i][j]);
		}

	}

	printf("\n----------[W] UP --- [S] Down --- [A] LEFT --- [D] Right--------------");
}

void initBoard(Board* board) {

	int i;
	int j;

	for (i = 0; i<board->rows; i++) {
		for (j = 0; j<board->cols; j++) {
			board->table[i][j] = 0;
		}
	}
	addRandom(board);
	addRandom(board);
	drawBoard(board);

}


bool checkEndCases(Board* board){

	int i = 0;
	int j = 0;
	int zeroCount = 0;

	for (i = 0; i<board->rows; i++){

		for (j = 0; j<board->rows; j++){
			if (board->table[i][j] == 0)
				zeroCount++;

		}
	}

	if (zeroCount == 0)
		return true;
	return false;



}


bool checkWinner(Board* board, int* fiboArray){


	int n = (2 * (board->rows)*(board->rows));
	int i = 0;
	int j = 0;


	for (i = 0; i<board->rows; i++){
		for (j = 0; j<board->cols; j++){

			if (board->table[i][j] == fiboArray[n - 1])
				return true;
		}
	}
	return false;


}
















