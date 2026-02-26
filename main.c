/* My roll number is: ED24B017 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"
#define BG_LIGHT "\x1B[47m" // Light background
#define BG_DARK "\x1B[100m" // Dark background

typedef struct PlaceInformation
{
	char color;		 // empty : .
	int typeOfPiece; // empty : -1
	char renderChar; // empty : .
	bool filled;	 // empty : 0
	int x;
	int y;
} PI;

/*rules for moving a piece in chessboard::

1# It should move according to its own rules defined by its piece behavior;
2# It should not jump over other pieces(exception : horse);

i understand that we need to create different functions to do different things.
1# moving a piece.

for moving a piece , we need to know a lot of factors, such as whether there is a piece in the destination place, is it a legal move!!!

Gotcha, the whole point of moving a piece is to make sure that it is a legal move.
So, the function isLegal should be defined.
And in order to be a legal move, we need to check a few stuff.

suppose we are moving a pawn, we first need to see if a pawn exists in that place.
or better, we need to see what kind of piece exists in that place.
The first function which is going to be defined is to determine what is the
piece that is present in that particular spot;

Next, we need to create a function for each piece which checks whether the move is
legal or not particular to that piece. so , we need to create a series of functions
which checks whether the move is legal or not. also, weneed another function which which
checks whether another different pieces are blocking the way of a particular movemnt of the piece.
therefore it must be unique to each different piece.

now, we have identified whether the piece is movable or not.
If it is not, then we ask the user again for the input and try again. If the move is movable,
then we write a new function called the movePiece() which does the pointer function calls and moves the piece.
Also, after moving the piece everytime,

That is about basic moving the piece and stuff. Next we come to the logic of the game, winning and losing side.
how do we declare if one person is lost or won? we need to check if the king is under a checkmate or not;
so, for that, we need 2 functions which check whether the king is under checkmate or not : underCheckMate()
If the function returns true, then we end the game, and call it quits. also we need a function which
displays certain output when a particular player is lost or won. endGame();

We would also need another function which does not allow certain moves, such as jeopardizing the safety of
the king. isMoveLegalForKing(); This function does exactly that;

In order to use the above function, we need to see if the king is under check or not.
for that we declare a new function called underCheck() and it checks whether the king is under check or not!

I think it is better at this point to find out the position of the king using a seperate function which
would reduce the overall redundancy of the program.

Ig at this point, I have covered most of the functions and stuff, the only thing remaining is to code
the logic of the program, and get it ready! There are already a few functions and i have not mentioned them
because they were defined before writing this. We would need input sanitization! we would need another function for that!

we need a function to determine whether a piece exists at that place.!
isPlaceFilled()/

we need to write a new function i guess, since there is movement to killing and movement to empty space.
maybe we need to reconsider this fact and make a better application.

also, we need a function that sanitizes the user input, to avoid segmentation faults or bus crashes or something like that.
Also, we need a function that takes in the input which is in the format of "C2 D5" and convert it to x1, y1, x2, y2;

Function : isPlaceFilled()
arguments: PI board[8][8] , int x, int y;
return type : bool;

Function 1 : userInputClean()
arguments : int x, int y;
return type : bool

Function 2 : convertUserInput()
arguments : char arr[2];
return type : int arr[4];

Function 3 : whatPiece()
arguments :PI board[8][8], int x, int y;
return type : int (the specific type for each piece).

Function 3.1 : isMoveRightPawn()
arguments : PI board[8][8], int x, int y, int h, int k, char color;
return type : bool;

Function 3.2 : isMoveRightKing()
arguments :int x, int y, int h, int k;
return type : bool;

Function 3.3 : isMoveRightQueen()
arguments : PI board[8][8], int x, int y, int h, int k, char color;
return type : bool;

Function 3.4 : isMoveRightBishop()
arguments : PI board[8][8], int x, int y, int h, int k, char color;
return type : bool;

Function 3.5 : isMoveRightRook()
arguments : PI board[8][8], int x, int y, int h, int k, char color;
return type : bool;

Function 3.6 : isMoveRightKnight()
arguments : PI board[8][8], int x, int y, int h, int k, char color;
return type : bool

Function 4.1 : findBlackKing()
arguments : PI board[8][8]
return type : int arr[2]; -> coordinates of the black king;

Function 4.2 : findWhiteKing()
arguments : PI board[8][8]
return type : int arr[2]; -> coordinates of the white king;

Function 5: underCheck ()
arguments : PI board[8][8]
//find the king and check whether he is under check or not!

Function 6 : isMoveLegalForKing()
arguments: PI board[8][8];
//find the kings position and also, take in the next move and check whether it the king is in check
or not. for this use the function underCheck();
return type : bool

Functino 7 : underCheckMate()
arguments : PI board[8][8]
//find the position of both the kings and check whether they are in checkMate or not;
return type : bool;

Function 8 : endGame()
arguments : underCheckMate()
return type : void;

Naming scheme for each of the integer :
	Black:

	Pawn : 0
	Rook : 1
	Bishop : 2
	Knight : 3
	Queen : 4
	King : 5

	White :

	Pawn : 6
	Rook : 7
	Bishop : 8
	Knight : 9
	Queen : 10
	King : 11
*/

bool canIMove(PI board[8][8], int x, int y, int h, int k);

PI *isCheck(PI board[8][8], PI **whitePtr, PI **blackPtr);

void movePiece(PI board[8][8], int x, int y, int h, int k);

int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

bool isItYourPiece(PI board[8][8], int x, int y, int cnt)
{

	if (cnt)
	{
		if (board[x][y].color == 'w')
			return true;
	}
	else
	{
		if (board[x][y].color == 'b')
			return true;
	}

	return false;
}

bool correctInput(int x, int y, int h, int k)
{
	if (x >= 0 && x < 8 && y >= 0 && y < 8 && h >= 0 && h < 8 && k >= 0 && k < 8)
		return 1;
	return 0;
}

int convertInput(char c)
{
	c = toupper(c);
	return c - 'A';
}

bool isPlaceFilled(PI board[8][8], int x, int y)
{
	if (board[x][y].filled)
		return true;
	return false;
}

int whatPiece(PI board[8][8], int x, int y)
{
	PI *ptr = &(board[x][y]);
	return ptr->typeOfPiece;
}

// we need to figure out whether there is a kill happening and if it is legal to kill or not!

bool isKillLegal(PI board[8][8], int x, int y, int h, int k)
{

	PI *ptrSrc = &(board[x][y]);
	PI *ptrDst = &(board[h][k]);

	if (!ptrDst->filled)
	{
		return true;
	}
	else if (ptrSrc->color != ptrDst->color)
	{
		return true;
	}

	return false;
}

// we are only checking if the move is possible and whether there is a possibility of a potential kill.

bool isMoveRightPawn(PI board[8][8], int x, int y, int h, int k)
{

	char color = board[x][y].color;

	if (color == 'w')
	{
		if (x - h == 1 && y == k)
		{
			if (!board[h][k].filled)
				return true;
		}
		else if (abs(k - y) == 1 && x - h == 1)
		{
			if (board[h][k].filled)
				return true;
		}
	}
	else if (color == 'b')
	{
		if (h - x == 1 && y == k)
		{
			if (!board[h][k].filled)
				return true;
		}
		else if (abs(k - y) == 1 && h - x == 1)
		{
			if (board[h][k].filled)
				return true;
		}
	}
	else
	{
		printf("wrong move or something is wrong with the code.!!\n");
		return false;
	}
	return false;
}

bool isMoveRightBishop(PI board[8][8], int x, int y, int h, int k)
{

	int tx = x, ty = y;

	if (abs(y - k) != abs(h - x))
	{
		return 0;
	}

	while (tx != h && ty != k)
	{
		if (x - h > 0 && y - k > 0)
		{
			tx--;
			ty--;
			if (board[tx][ty].filled)
			{
				return 0;
			}
		}

		else if (x - h < 0 && y - k > 0)
		{
			tx++;
			ty--;
			if (board[tx][ty].filled)
			{
				return 0;
			}
		}

		else if (x - h < 0 && y - k < 0)
		{
			tx++;
			ty++;
			if (board[tx][ty].filled)
			{
				return 0;
			}
		}

		else if (x - h > 0 && y - k < 0)
		{
			tx--;
			ty++;
			if (board[tx][ty].filled)
			{
				return 0;
			}
		}
	}

	return 1;
}

bool isMoveRightRook(PI board[8][8], int x, int y, int h, int k)
{

	int tx = x, ty = y;

	if (x != h && y != k)
	{
		return 0;
	}

	if (h == x)
	{
		int move = (k > y) ? 1 : -1;

		for (int i = y + move; i != k; i += move)
		{
			if (board[x][i].filled)
			{
				return false;
			}
		}
	}
	else
	{
		int move = (h > x) ? 1 : -1;

		for (int i = x + move; i != h; i += move)
		{
			if (board[i][y].filled)
			{
				return false;
			}
		}
	}

	return 1;
}

bool isMoveRightKnight(int x, int y, int h, int k)
{

	if (abs(h - x) == 2 && abs(k - y) == 1)
		return 1;
	else if (abs(h - x) == 1 && abs(k - y) == 2)
		return 1;

	return 0;
}

bool isMoveRightKing(int x, int y, int h, int k)
{

	if (abs(h - x) == 1 && abs(y - k) == 1)
		return 1;
	else if (abs(h - x) == 1 && y == k)
		return 1;
	else if (x == h && abs(y - k) == 1)
		return 1;

	return 0;
}

bool isMoveRightQueen(PI board[8][8], int x, int y, int h, int k)
{

	if (isMoveRightBishop(board, x, y, h, k) || isMoveRightRook(board, x, y, h, k))
		return 1;
	return 0;
}

bool canWeKillThisPiece(PI board[8][8], int x, int y)
{

	PI *piece = &(board[x][y]);
	char color = piece->color;
	char tempColor;
	if (color == 'w')
		tempColor = 'b';
	else if (color == 'b')
		tempColor = 'w';

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PI *ptr = &(board[i][j]);

			if (ptr->color == tempColor && canIMove(board, ptr->x, ptr->y, x, y))
			{
				return 1;
			}
		}
	}

	return 0;
}

bool canYouComeForMe(PI board[8][8], int x, int y, char ourColor)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			PI *ptr = &(board[i][j]);

			if (ptr->color == ourColor && canIMove(board, ptr->x, ptr->y, x, y))
				return true;
		}
	}

	return false;
}

PI *isCheck(PI board[8][8], PI **whitePtr, PI **blackPtr)
{

	// we need to check if the king is at check or not
	// so we need to iterate through the entire board and make our king piece our final
	// destination and loop through all the remaining pieces as our initial position!
	// finding both the kings;
	// we need to check if the king is under only check or complete mate;

	PI *enemyPtr = NULL;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			PI *ptr = &(board[i][j]);

			if (ptr->typeOfPiece == 11)
			{
				*whitePtr = ptr;
			}
			if (ptr->typeOfPiece == 5)
			{
				*blackPtr = ptr;
			}
		}
	}

	int wx = (*whitePtr)->x;
	int wy = (*whitePtr)->y;

	int bx = (*blackPtr)->x;
	int by = (*blackPtr)->y;

	bool isUnderCheck = 0;

	// we need a figure out a function where it takes in input as the char of the piece to be
	// moved and tells whether it can move it or not!
	// checking if white king is in danger:

	for (int i = 0; i < 8 && !isUnderCheck; i++)
	{
		for (int j = 0; j < 8 && !isUnderCheck; j++)
		{
			PI *ptr = &(board[i][j]);

			if (ptr != *whitePtr)
			{
				if (canIMove(board, ptr->x, ptr->y, wx, wy) && ptr->color == 'b')
				{
					isUnderCheck = 1;
					enemyPtr = ptr;
					break;
				}
			}
		}
	}

	// black king time.

	for (int i = 0; i < 8 && !isUnderCheck; i++)
	{
		for (int j = 0; j < 8 && !isUnderCheck; j++)
		{
			PI *ptr = &(board[i][j]);

			if (ptr != *blackPtr)
			{
				if (canIMove(board, ptr->x, ptr->y, bx, by) && ptr->color == 'w')
				{
					isUnderCheck = 2;
					enemyPtr = ptr;
					break;
				}
			}
		}
	}

	return enemyPtr;
}

int isGameOver(PI board[8][8], PI **whitePtr, PI **blackPtr, PI **enemyPtr)
{
	if (*enemyPtr == NULL)
	{
		return 0;
	}

	int ex = (*enemyPtr)->x;
	int ey = (*enemyPtr)->y;
	int wx = (*whitePtr)->x;
	int wy = (*whitePtr)->y;
	int bx = (*blackPtr)->x;
	int by = (*blackPtr)->y;

	char attackedColor = (*enemyPtr)->color == 'w' ? 'b' : 'w';

	int kX = attackedColor == 'w' ? wx : bx;
	int kY = attackedColor == 'w' ? wy : by;

	bool canKingEscape = false;

	int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

	for (int i = 0; i < 8 && !canKingEscape; i++)
	{

		int newX = kX + dx[i];
		int newY = kY + dy[i];

		if (!correctInput(kX, kY, newX, newY))
		{
			continue;
		}

		if (canIMove(board, kX, kY, newX, newY))
		{

			PI tempDest = board[newX][newY];
			movePiece(board, kX, kY, newX, newY);

			PI *check = isCheck(board, whitePtr, blackPtr);

			if (check == NULL)
			{
				canKingEscape = true;
			}

			if (attackedColor == 'w')
			{
				**whitePtr = board[newX][newY];
				(*whitePtr)->x = kX;
				(*whitePtr)->y = kY;
			}
			else
			{
				**blackPtr = board[newX][newY];
				(*blackPtr)->x = kX;
				(*blackPtr)->y = kY;
			}
			board[newX][newY] = tempDest;
			board[newX][newY].x = newX;
			board[newX][newY].y = newY;
		}
	}

	if (canKingEscape)
	{
		return 0;
	}
	if (canWeKillThisPiece(board, ex, ey))
	{
		return 0;
	}
	char attackingPiece = (*enemyPtr)->renderChar;

	if (attackingPiece != 'N' && attackingPiece != 'P')
	{
		printf("!");
		int xStep = ex > kX ? 1 : (ex < kX ? -1 : 0);

		int yStep = ey > kY ? 1 : (ey < kY ? -1 : 0);

		for (int x = kX + xStep, y = kY + yStep; x != ex && y != ey; x += xStep, y += yStep)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board[i][j].color == attackedColor && canIMove(board, i, j, x, y))
					{

						PI tempDest = board[x][y];

						movePiece(board, i, j, x, y);

						PI *check = isCheck(board, whitePtr, blackPtr);

						board[i][j] = board[x][y];
						board[i][j].x = i;
						board[i][j].y = j;
						board[x][y] = tempDest;
						board[x][y].x = x;
						board[x][y].y = y;

						if (check == NULL)
						{
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}

bool canIMove(PI board[8][8], int x, int y, int h, int k)
{

	char piece = board[x][y].renderChar;

	if (piece == 'P')
	{
		if (!isMoveRightPawn(board, x, y, h, k) || !isKillLegal(board, x, y, h, k))
		{
			return 0;
		}
	}

	// 2 //if the selected piece is Bishop:

	else if (piece == 'B')
	{
		if (!isMoveRightBishop(board, x, y, h, k) || !isKillLegal(board, x, y, h, k))
		{
			return 0;
		}
	}

	// 3 //if the selected piece is Rook:

	else if (piece == 'R')
	{
		if (!isMoveRightRook(board, x, y, h, k) || !isKillLegal(board, x, y, h, k))
		{
			return 0;
		}
	}

	// 4 ///if the selected piece is knight!!!

	else if (piece == 'N')
	{
		if (!isMoveRightKnight(x, y, h, k) || !isKillLegal(board, x, y, h, k))
		{
			return 0;
		}
	}

	// 5 //if the selected piece is king :

	else if (piece == 'K')
	{
		if (!isMoveRightKing(x, y, h, k) || !isKillLegal(board, x, y, h, k))
		{
			return 0;
		}
	}
	// 6 //if the selected piece is queen :

	else if (piece == 'Q')
	{
		if (!isMoveRightQueen(board, x, y, h, k) || !isKillLegal(board, x, y, h, k))
		{
			return 0;
		}
	}
	return 1;
}

void movePiece(PI board[8][8], int x, int y, int h, int k)
{
	PI *src = &(board[x][y]), *dst = &(board[h][k]);

	*(dst) = *(src);

	dst->x = h;
	dst->y = k;

	src->color = '.';
	src->filled = 0;
	src->renderChar = '.';
	src->typeOfPiece = -1;
}

void renderBoard(char arr[10][10], PI board[8][8])
{

	for (int i = 0; i < 10; i++)
	{
		printf("\n");
		for (int j = 0; j < 10; j++)
		{

			if (i > 0 && i < 9 && j > 0 && j < 9)
			{
				PI *ptr = &(board[i - 1][j - 1]);

				if (ptr->color == 'w')
				{
					printf("%s%c%s   ", KYEL, arr[i][j], KNRM);
				}
				else if (ptr->color == 'b')
				{
					printf("%s%c%s   ", KCYN, arr[i][j], KNRM);
				}
				else
				{
					printf("%s%c%s   ", KWHT, arr[i][j], KNRM);
				}
			}
			else
			{
				printf("%s%c%s   ", KWHT, arr[i][j], KNRM);
			}

			if (j == 0 || j == 8)
			{
				printf("   ");
			}
		}
		if (i == 0 || i == 8)
		{
			printf("   ");
		}
		printf("\n");
	}
}

void initialSetup(char board[10][10], PI tempBoard[8][8])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			board[i][j] = '.';
			if ((i == 0 || i == 9) && j > 0 && j < 9)
			{
				board[i][j] = 'a' + j - 1;
			}
			else if ((j == 0 || j == 9) && i > 0 && i < 9)
			{
				board[i][j] = '9' - i;
			}
			else if (i > 0 && j > 0 && i < 9 && j < 9)
			{
				board[i][j] = tempBoard[i - 1][j - 1].renderChar;
			}
		}
	}
}

void updateBoard(PI board[8][8], char tempBoard[10][10])
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			tempBoard[i + 1][j + 1] = board[i][j].renderChar;
		}
	}
}

int isItRightMoveUnderCheck(PI board[8][8], PI *whitePtr, PI *blackPtr, PI *enemyPtr, int x, int y, int h, int k)
{

	PI *src = &(board[x][y]);
	PI *dst = &(board[h][k]);

	int ans = 0;

	// canIMove is already checked!

	movePiece(board, x, y, h, k);

	if (isCheck(board, &whitePtr, &blackPtr) != NULL)
	{
		ans = 0;
	}
	else
	{
		ans = 1;
	}

	*src = board[h][k];
	src->x = x;
	src->y = y;

	board[h][k] = *dst;
	board[h][k].x = h;
	board[h][k].y = k;

	return ans;
}

void mainWorking(PI initBoard[8][8], char board[10][10], PI *whitePtr, PI *blackPtr, PI *enemyPtr)
{

	renderBoard(board, initBoard);

	printf("\nWelcome to Chess!!!!!. First, its white's turn.\nEnter the input in the specific format only according to the coordinates given to you!!!\n Example : \"C6 D7\"\n ");
	printf("This is the initial setup:\n");
	printf("Do you want to begin? (y/n)\n");
	char temp;

	scanf("%c", &temp);
	char a;
	int a1;
	char b;
	int b1;

	if (temp == 'y')
	{
		int cnt = 1;
		bool gameInProgress = 1;

		do
		{
			if (cnt)
			{
				printf("\nWhites turn: \n");
			}
			else
			{
				printf("\nBlacks turn: \n");
			}

			printf("Enter the characters : ");
			scanf(" %c %d %c %d", &a, &a1, &b, &b1);

			int y = convertInput(a);
			int x = 8 - a1;
			int k = convertInput(b);
			int h = 8 - b1;

			if (!correctInput(x, y, h, k))
			{
				printf("Please enter correct input!!!\n");
				continue;
			}

			if (!isPlaceFilled(initBoard, x, y))
			{
				printf("Enter a position which is occupied by an actual piece!!\n");
				continue;
			}

			// we need to check the position of destination if it is filled by another piece or not
			// we also need to make sure that during a blacks' move, only black pieces can be moved!!!

			if (!isItYourPiece(initBoard, x, y, cnt))
			{
				printf("Select your own pieces!!!\n");
				continue;
			}

			if (!canIMove(initBoard, x, y, h, k))
			{
				printf("Invalid Move! Please try again!!!\n");
				continue;
			}
			else
			{

				if (isCheck(initBoard, &whitePtr, &blackPtr) != NULL)
				{
					if (isItRightMoveUnderCheck(initBoard, whitePtr, blackPtr, enemyPtr, x, y, h, k))
					{

						movePiece(initBoard, x, y, h, k);
					}
					else
					{

						printf("Wrong move under check! Please try again!\n");
						continue;
					}
				}
				else
				{
					movePiece(initBoard, x, y, h, k);
				}
			}

			// before calling move function, we need to do sanity checks, such as, is the move legal or not.
			// so, i understand that move function is just a very small function

			cnt = (cnt ? cnt - 1 : cnt + 1);

			updateBoard(initBoard, board);
			renderBoard(board, initBoard);

			enemyPtr = isCheck(initBoard, &whitePtr, &blackPtr);

			if (isGameOver(initBoard, &whitePtr, &blackPtr, &enemyPtr))
			{
				gameInProgress = false;
				if (cnt)
				{
					printf("Game Over! Black wins.");
				}
				else
				{
					printf("Game Over! White wins.");
				}

				printf("\nIf you want to play again, run the code again!\n");
				break;
			}

		} while (gameInProgress);
	}
	else
	{
		printf("Well, Game over! Nobody won!\n");
	}
}

int main()
{

	char board[10][10];

	PI initBoard[8][8];

	PI(*ptrToBoard)
	[8][8] = &initBoard;

	PI *whitePtr = NULL;
	PI *blackPtr = NULL;
	PI *enemyPtr = NULL;

	/////////////////////////////
	// Initialization of Board////
	/////////////////////////////

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			initBoard[i][j].x = i;
			initBoard[i][j].y = j;

			int *tempPtr = &(initBoard[i][j].typeOfPiece);
			char *tempPtr2 = &(initBoard[i][j].renderChar);
			bool *tempPtr3 = &(initBoard[i][j].filled);
			char *colorPtr = &(initBoard[i][j]).color;

			// Initializing case.
			*tempPtr3 = 0;
			*tempPtr2 = '.';
			*tempPtr = -1;
			*colorPtr = '.';

			// Initializing the pawns :

			if (i == 0 || i == 1)
			{
				*colorPtr = 'b';
			}
			else if (i == 6 || i == 7)
			{
				*colorPtr = 'w';
			}

			if (i == 1)
			{
				*tempPtr = 0;
				*tempPtr2 = 'P';
				*tempPtr3 = 1;
			}
			if (i == 6)
			{
				*tempPtr = 6;
				*tempPtr2 = 'P';
				*tempPtr3 = 1;
			}

			// Initializing the rest of the pieces :

			if (i == 0 && (j == 0 || j == 7))
			{
				*tempPtr = 1;
				*tempPtr2 = 'R';
				*tempPtr3 = 1;
			}
			if (i == 0 && (j == 1 || j == 6))
			{
				*tempPtr = 2;
				*tempPtr2 = 'N';
				*tempPtr3 = 1;
			}
			if (i == 0 && (j == 2 || j == 5))
			{
				*tempPtr = 3;
				*tempPtr2 = 'B';
				*tempPtr3 = 1;
			}
			if (i == 7 && (j == 0 || j == 7))
			{
				*tempPtr = 7;
				*tempPtr2 = 'R';
				*tempPtr3 = 1;
			}
			if (i == 7 && (j == 1 || j == 6))
			{
				*tempPtr = 8;
				*tempPtr2 = 'N';
				*tempPtr3 = 1;
			}
			if (i == 7 && (j == 2 || j == 5))
			{
				*tempPtr = 9;
				*tempPtr2 = 'B';
				*tempPtr3 = 1;
			}

			if ((i == 0 && (j == 3 || j == 4)) || (i == 7 && (j == 4 || j == 3)))
			{
				*tempPtr3 = 1;
			}
		}
	}

	// Initializing the kings and queens.

	initBoard[0][3].typeOfPiece = 4;
	initBoard[0][3].renderChar = 'Q';
	initBoard[0][3].filled = 1;

	initBoard[0][4].typeOfPiece = 5;
	initBoard[0][4].renderChar = 'K';
	initBoard[0][4].filled = 1;

	initBoard[7][3].typeOfPiece = 10;
	initBoard[7][3].renderChar = 'Q';
	initBoard[7][3].filled = 1;

	initBoard[7][4].typeOfPiece = 11;
	initBoard[7][4].renderChar = 'K';
	initBoard[7][4].filled = 1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (initBoard[i][j].typeOfPiece == 11)
			{
				whitePtr = &initBoard[i][j];
			}
			else if (initBoard[i][j].typeOfPiece == 5)
			{
				blackPtr = &initBoard[i][j];
			}
		}
	}

	//////// Initialization of Board only !!! \////////////

	initialSetup(board, initBoard);
	mainWorking(initBoard, board, whitePtr, blackPtr, enemyPtr);

	return 0;
}