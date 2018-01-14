

typedef struct user{
	char name[35];
	int movesCount;
	int gameType;
	char date[20];
}User;


User * createUser(char *name){

	int i = 0;
	User* newUser = (User*)malloc(sizeof(User));

	newUser->movesCount = 0;
	strcpy(newUser->name, name);
	
	return newUser;
}

void greetUser(User* user){

	printf("\n\n\t\tHey %s, Welcome To the 2048 Fibo Game\n", user->name);
	printf("\n\tChoose the Board Size : ");
	printf("\n\t\t2X2 or 4X4");
	

}
void printUser(User *user){

	printf("Hey %s , You have played %d Moves", user->name, user->movesCount);
}

void welcomeScreenLevel3(bool flag){

	printf("\n\t\tWelcome,To Fibo 2048.... ");
	printf("\n\t1.Play Game");
	printf("\n\t2.View Leaderboard");
	if (flag)
	printf("\n\t3.Replay");
	printf("\n\t4.Exit");
}

int compare(const void * a, const void * b){

	User* orderA = (User *)a;
	User* orderB = (User *)b;

	return (orderA->movesCount - orderB->movesCount);
}
