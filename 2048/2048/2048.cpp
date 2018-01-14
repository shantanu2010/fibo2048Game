#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "2048UserUtils.h"
#include "2048BoardUtils.h"
#include "2048MovesUtils.h"


void playGame(Board* board, User* user,int boardSize){


	char bitStart[5] = "0110";
	char bitStop[5] = "1001";

	FILE* outfile;
	char input;
	bool check = false;
	bool end = false;
	bool winner = false;
	int* fibo = getFibo(boardSize);

	do{

		input = getInput();
		check = play2048(board, input, fibo);

		winner = checkWinner(board, fibo);
		end = checkEndCases(board);

		if (check) {

			user->movesCount = user->movesCount + 1;
			addRandom(board);
			drawBoard(board);
			outfile = fopen("previous.dat", "w");
			if (outfile == NULL){
				printf("\nError In Autosave\n");
				return;
			}

			//fwrite(&bitStart, sizeof(char), 5, outfile);
			fwrite(user, sizeof(User), 1, outfile);
			fwrite(board, sizeof(Board), 1, outfile);
			fclose(outfile);


		}

	} while (check && !winner && !end);

	if (end){

		printf("\n\t\tGame Over!!!");
		printf("\n\t\tYou Lost the game");

		getchar();
		getchar();
	}

	if (winner){

		printf("\n\tGreat Job!.....You Made It!");

		outfile = fopen("database.dat", "a+");
		if (outfile == NULL){
			fprintf(stderr, "\nError opend file\n");
			getchar();
			exit(1);
		}


		fseek(outfile, 0, SEEK_END);
		fwrite(user, sizeof(User), 1, outfile);
		fclose(outfile);

		getchar();
		getchar();

	}

}



int main(void){

	int boardSize;
	int welcome;
	char* name = (char*)malloc(35*sizeof(char));
	bool flag = false;
	FILE *outfile;
	
	

	do{
		welcomeScreenLevel3(flag);
		welcome = getWelcomeOption();

		if (welcome == 1){
			printf("\n\tEnter Name of the Player : ");
			scanf_s(" %[^\n]", name, 35);

			User* user = createUser(name);
			greetUser(user);

			time_t now = time(NULL);
			struct tm *t = localtime(&now);

			strftime(user->date, sizeof(user->date) - 1, "%d %m %Y %H:%M", t);

			boardSize = takeBoardInput();

			Board* board = createBoard(boardSize, boardSize);
			user->gameType = boardSize;
			initBoard(board);

			playGame(board, user, boardSize);

			flag = true;
		}

		else if (welcome == 2){

			FILE *infile;
			User array[100];
			int i = 0;
			int j = 0;
			User input;

			infile = fopen("database.dat", "r");
			if (infile == NULL)
			{
				printf("\nError opening file\n");
				getchar();
				exit(1);
			}

			while (fread(&input, sizeof(User), 1, infile) != NULL){

				strcpy(array[i].name, input.name);
				array[i].movesCount = input.movesCount;
				array[i].gameType = input.gameType;
				strcpy(array[i].date, input.date);

				i++;
			}


			qsort(array, i, sizeof(User), compare);

			printf("\n\n\t\tWelcome To LeaderBoard!!");

			printf("\n|===================================================|");
			printf("\n| Name\t\t||Date\t\t\t||GameType\t||movesCount|");

			for (j = 0; j < i; j++){
				printf("\n|%s\t||%s\t||%d X %d \t||%d\t    |", array[j].name,
					array[j].date, array[j].gameType, array[j].gameType, array[j].movesCount);

			}

			
			
		}

		else if (welcome == 3 && flag){

			outfile = fopen("previous.dat", "r");

			char str[5];
			Board board;
			User user;

			
			fread(&user, sizeof(User), 1, outfile);
			fread(&board, sizeof(Board), 1, outfile);

			drawBoard(&board);
			playGame(&board, &user, board.rows);

			getchar();
			getchar();

		}

	}while (welcome != 4);


	return 0;
}