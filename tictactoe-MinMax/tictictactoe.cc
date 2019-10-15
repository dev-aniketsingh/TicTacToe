/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: John Sullins
 *
 * Created on February 19, 2018, 4:45 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define MAXLEVEL 2
float evaluate(char[4][4], char);

/* Functions to play TicTicTacToe game */
int getScore(char[4][4], char);
int winner(char[4][4], char);
void display(char[4][4]);
int run(int[2], char);

/* Functions to run minmax tree */
void choose(int &, int &, char[4][4], char);
float getmax(int &, int &, char[4][4], int, char);
float getmin(int &, int &, char[4][4], int, char);
void copy(char[4][4], char[4][4]);

/****************** YOUR CODE GOES HERE ****************************/

/* User provided function to evaluate how good a situation is */

int countSymbol(char board[4][4], int index, char &who, bool isRow) {
	int count = 0;
 		for(int i = 0; i < 4; i++) {
 			if(isRow) {
 				if(board[index][i] == who) {
 					count++;
 				}
 			}
 			else {
 				if(board[i][index] == who) {
 					count++;
 				}
 			}
 		}
	return count;
}

float evaluate(char board[4][4], char who)
{
 float result = 0.0, rewardValue = 0.0, penalityValue = 0.0;
 float exceptionCase = 1;
 int friendlyMarks = 0, enemyMarks = 0;
 char other;
 if (who == 'X') {
 	other = 'O';
 } 
 	
 else {
 	other = 'X';
 }
 	
 //REWARD  VARIABLES
 float VERY_VERY_LOW = 5.0,SLIGHTLY_LOW = 30.0,BETTER_THAN_SLIGHTLY_LOW = 60.0, LOW_REWARD = 150.0, MORE_THAN_LOW = 400.0, MID_REWARD = 600.0, HIGH_REWARD = 900.0;
//PENALITY VARIABLES
 float VERY_VERY_LOW_PEN = 3.0,SLIGHTLY_LOW_PEN = 5.0,BETTER_THAN_SLIGHTLY_LOW_PEN = 20.0, LOW_REWARD_PEN = 80.0, MORE_THAN_LOW_PEN = 220.0, MID_LEVEL_PEN = 400.0, HIGH_PEN = 850.0;

 // Rewarding & Penality  for LOOP for ROW
 for(int i = 0; i < 4; i++) {
 	friendlyMarks = countSymbol(board,i,who,true);
 	enemyMarks = countSymbol(board,i,other,true);
 	 	//REWARD CODE
 		if(friendlyMarks == 0 && enemyMarks == 0) {
 			rewardValue += VERY_VERY_LOW;
 		}
 		if(friendlyMarks == 1 && enemyMarks == 0) {
 			rewardValue += SLIGHTLY_LOW;
 		}
 		if(friendlyMarks == 2 && enemyMarks == 0) {
 			rewardValue += MID_REWARD;
 		}
 		if(friendlyMarks == 3 && enemyMarks == 0) {
 			rewardValue += HIGH_REWARD;
 		}
 		if(friendlyMarks == 1 && enemyMarks == 1) {
 			rewardValue += BETTER_THAN_SLIGHTLY_LOW;
 		}
 		if(friendlyMarks == 2 && enemyMarks == 1) {
 			rewardValue += SLIGHTLY_LOW;
 		}
 		if(friendlyMarks == 3 && enemyMarks == 1) {
 			rewardValue += MORE_THAN_LOW;
 		}
 		if(friendlyMarks == 2 && enemyMarks == 2) {
 			rewardValue += SLIGHTLY_LOW;
 		}
 	
 	//PENALITY CODE
	 	if(friendlyMarks == 0 && enemyMarks == 2) {
			penalityValue += MORE_THAN_LOW_PEN;
		}
		if(friendlyMarks == 1 && enemyMarks == 2) {
			penalityValue += SLIGHTLY_LOW_PEN;
		}
		if(friendlyMarks == 0 && enemyMarks == 3) {
			penalityValue += HIGH_PEN;
		}
		if(friendlyMarks == 1 && enemyMarks == 3) {
			penalityValue += MID_LEVEL_PEN;
		}
  }
  //  Rewarding & Penality  for LOOP for COL
  for(int i = 0; i < 4; i++) {
  	friendlyMarks = countSymbol(board,i,other,false);
 	enemyMarks = countSymbol(board,i,who,false);

 	//REWARD CODE
		if(friendlyMarks == 0 && enemyMarks == 0) {
 			rewardValue += VERY_VERY_LOW;
 		}
 		if(friendlyMarks == 1 && enemyMarks == 0) {
 			rewardValue += SLIGHTLY_LOW;
 		}
 		if(friendlyMarks == 2 && enemyMarks == 0) {
 			rewardValue += MID_REWARD;
 		}
 		if(friendlyMarks == 3 && enemyMarks == 0) {
 			rewardValue += HIGH_REWARD;
 		}
 		if(friendlyMarks == 1 && enemyMarks == 1) {
 			rewardValue += BETTER_THAN_SLIGHTLY_LOW;
 		}
 		if(friendlyMarks == 2 && enemyMarks == 1) {
 			rewardValue += SLIGHTLY_LOW;
 		}
 		if(friendlyMarks == 3 && enemyMarks == 1) {
 			rewardValue += MORE_THAN_LOW;
 		}
 		if(friendlyMarks == 2 && enemyMarks == 2) {
 			rewardValue += SLIGHTLY_LOW;
 		}
 	//PENALITY CODE
	 	if(friendlyMarks == 0 && enemyMarks == 2) {
			penalityValue += MORE_THAN_LOW_PEN;
		}
		if(friendlyMarks == 1 && enemyMarks == 2) {
			penalityValue += SLIGHTLY_LOW_PEN;
		}
		if(friendlyMarks == 0 && enemyMarks == 3) {
			penalityValue += MID_LEVEL_PEN;
		}
		if(friendlyMarks == 1 && enemyMarks == 3) {
			penalityValue += MID_LEVEL_PEN;
		}
  }
  		  /*if(board[1][1] == other && board[2][2] == other && board[3][3] == other) {
        	return exceptionCase;    
        }
        else if (board[0][0] == other && board[1][1] == other && board[2][2] == other) {
        	return exceptionCase;
        }
        else if (board[0][0] == other && board[2][2] == other && board[3][3] == other) {
        	return exceptionCase;    
        }

        else if (board[1][2] == other && board[2][1] == other && board[3][0] == other) {
            return exceptionCase;
        }
        else if (board[0][3] == other && board[2][1] == other && board[3][0] == other) {
            return exceptionCase;
        }
        else if (board[0][3] == other && board[1][2] == other && board[2][1] == other) {
            return exceptionCase;
        }
        else {
        	penalityValue += VERY_VERY_LOW;
        }*/
  result = rewardValue - penalityValue;
  if(penalityValue > rewardValue) {
  	result = 20;
  } 
  if (winner(board, who)) 
  	result = 10000;
  if (winner(board, other)) 
  	result = 0;

  cout << result << endl;
  return result;
}
  

/***************** END OF YOUR CODE ********************************/





/***************** END OF YOUR CODE ********************************/

/* This is the main function for playing the game. It alternatively
   prompts the user for a move, and uses the minmax algorithm in 
   conjunction with the given evaluation function to determine the
   opposing move. This continues until the board is full. It returns
   the number scored by X minus the number scored by O. */

int run(int scores[2], char who) { 
  int i, j;
  char board[4][4];
  int row, col; 
  char current, other;
  int move = 1;

  /* Initialize the board */
  for (i = 0; i < 4; i++) { 
    for (j = 0; j < 4; j++) {
      board[i][j] = ' ';
      }
    }

  if (who == 'O') display(board);

  while (move <= 16) {
      if (move % 2 == 1) {
          current = 'X';
          other = 'O';
      }
      else {
          current = 'O';
          other = 'X';          
      }
      
      if (current == who) {        /* The computer's move */
        choose(row, col, board, who);  /* Call function to compute move */
        cout << "Computer chooses " << row+1 << ", " << col+1 << endl;
        if (board[row][col] == ' ') 
            board[row][col] = current;
        else {
          cout << "BUG! " << row+1 << ", " << col+1 << " OCCUPIED!!!\n";
          exit(0);
          }
        if (winner(board, who)) {
            cout << "Computer has 4 in a row! Computer wins!";
            display(board);
            return 1;
            }
        }

      else { 
        cout << "Player " << current << ", enter your move: ";
        cin >> row >> col;
        while (board[row-1][col-1] != ' ' ||
               row < 1 || row > 4 ||
               col < 1 || col > 4) {
          cout << "Illegal move! You cannot use that square!\n";
          cin >> row >> col;
          }
        col--; row--;
        board[row][col] = current;
        if (winner(board, current)) {
            cout << "Player has 4 in a row! Player wins!";
            display(board);
            return 1;            
            }
        
      }
 
    display(board);    /* Redisplay board to show the move */

    move++; /* Increment the move number and do next move. */
    }
  scores[0] = getScore(board, 'X');
  scores[1] = getScore(board, 'O');
  return 0;
  }

/* This function determines if there is a winner (based on 4 in a row) */
int winner(char board[4][4], char who) {
    for (int i = 0; i < 4; i++) {
        if (board[i][0] == who && 
            board[i][1] == who &&
            board[i][2] == who &&
            board[i][3] == who) {
            //cout << "Win in row " << i << "\n";
            return 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (board[0][i] == who && 
            board[1][i] == who &&
            board[2][i] == who &&
            board[3][i] == who) {            
            //cout << "Win in row " << i << "\n";
            return 1;
        }
    }
        if (board[0][0] == who && 
            board[1][1] == who &&
            board[2][2] == who &&
            board[3][3] == who) {
            // cout << "Win along main diagonal\n";
            return 1;
            }
        
        if (board[0][3] == who && 
            board[1][2] == who &&
            board[2][1] == who &&
            board[3][0] == who) {
            // cout << "Win along other diagonal\n";
            return 1;
            }
    return 0;
}


/* This function exhaustively searches the current board to count the
   sets of 3 a player has in a row. */

    int getScore(char board[4][4], char who) {
      int row, col;
      int score = 0;

      /* check all rows */
      for (row = 0; row < 4; row++)
        for (col = 0; col < 2; col++)
          if (board[row][col] == who &&
              board[row][col+1] == who &&
              board[row][col+2] == who) score++;

      /* check all columns */
      for (row = 0; row < 2; row++)
        for (col = 0; col < 4; col++)
          if (board[row][col] == who &&
              board[row+1][col] == who &&
              board[row+2][col] == who) score++;

      /* check all diagonals */
      for (row = 0; row < 2; row++)
        for (col = 0; col < 2; col++)
          if (board[row][col] == who &&
              board[row+1][col+1] == who &&
              board[row+2][col+2] == who) score++;
      for (row = 0; row < 2; row++)
        for (col = 2; col < 4; col++)
          if (board[row][col] == who &&
              board[row+1][col-1] == who &&
              board[row+2][col-2] == who) score++;
        
        return score;
      }

/* This displays the current configuration of the board. */

void display(char board[4][4]) {
  int row, col, X, O;
  cout << "\n";
  for (row = 3; row >= 0; row--) {
    cout << "  +-+-+-+-+\n";
    cout << row+1 << " ";
    for (col = 0; col < 4; col++) {
      if (board[row][col] == 'X')  /* if contents are 0, print space */
        cout << "|X";
      else if (board[row][col] == 'O')
        cout << "|0";
      else cout << "| ";
      }
    cout << "|\n";
    }
  cout << "  +-+-+-+-+\n";  /* print base, and indices */
  cout << "   1 2 3 4\n";
  cout << "X: " << getScore(board, 'X') << endl;
  cout << "O: " << getScore(board, 'O') << endl;
  }
   
/* Basic function for choosing the computer's move. It essentially
   initiates the first level of the MINMAX algorithm, and returns
   the column number it chooses. */

void choose(int &row, int &col, char board[4][4], char who) {
   int move; 
   float value;
   getmax(row, col, board, 1, who);
   }


/* This handles any MAX level of a MINMAX tree. Using a pointer to move
   is a hack to deal with not being able to return both the chosen move
   and its evaluation number. 

   This essentially handles moves for the computer. */

float getmax(int &row, int &col, char board[4][4], int level, char who) {
   char tempboard[4][4];
   int r,c = 0;
   float max = -1;
   float val;
   int tempR, tempC;
   for (r = 0; r < 4; r++)
    for (c = 0; c < 4; c++) {  /* Try each row and column in board */
      if (board[r][c] == ' ') {     /* Make sure square not full */

         /* To avoid changing original board  during tests, make a copy */
         copy(tempboard, board); 

         /* Find out what would happen if we chose this column */
         tempboard[r][c] = who;

         /* If this is the bottom of the search tree (that is, a leaf) we need
            to use the evaluation function to decide how good the move is */
         if (level == MAXLEVEL) {
                val = evaluate(tempboard, who);
             }

         /* Otherwise, this move is only as good as the worst thing our
            opponent can do to us. */
         else
            val = getmin(tempR, tempC, tempboard, level+1, who);

         /* Return the highest evaluation, and set call by ref. parameter
            "move" to the corresponding column */
         if (val > max) {
            max = val;
            if (level==1) {row = r; col = c;}
            }

         }
      }
   return max;
   }

/* This handles any MIN level of a MINMAX tree. Using a pointer to move
   is a hack to deal with not being able to return both the chosen move
   and its evaluation number. 

   This essentially handles moves for the opponent. */

float getmin(int &row, int &col, char board[4][4], int level, char who) {
   char tempboard[4][4];
   int r,c = 0;
   int tempR, tempC;
   float min = 1001;
   float val;

   /* Since this is opponent's move, we need to figure out which they are */
   char other;
   if (who == 'X') other = 'O'; else other = 'X'; 

   for (r = 0; r < 4; r++)
    for (c = 0; c < 4; c++) {  /* Try each row and column in board */
      if (board[r][c] == ' ') {     /* Make sure square not full */

         /* To avoid changing original board  during tests, make a copy */
         copy(tempboard, board);

         /* Find out what would happen if opponent chose this column */
         tempboard[r][c] = other;

         /* If this is the bottom of the search tree (that is, a leaf) we need
            to use the evaluation function to decide how good the move is */
         if (level == MAXLEVEL) 
             val = evaluate(tempboard, who);
             

         /* Otherwise, find the best thing that we can do if opponent
            chooses this move. */
         else
            val = getmax(tempR, tempC, tempboard, level+1, who);

         /* Return the lowest evaluation (which we will assume will be 
            chosen by opponent, and set call by ref. parameter
            "move" to the corresponding column */
         if (val < min) {
            min = val;
            // *move = col;
            }
         }
      }
   return min;
   }


/* This function makes a copy of a given board. This is necessary to be
   able to "try out" the effects of different moves without messing up
   the actual current board. */

void copy(char a[4][4], char b[4][4]) {
  int i, j;
  for (i = 0; i < 4; i++) { 
    for (j = 0; j < 4; j++) {
      a[i][j] = b[i][j];
      }
    }
  }
     

/* Begin the game, asking whether player wants to go first or second. */

int main(int argc, char** argv) {
    char player, computer;
    char line[5];
    int scores[2];
    /* Decide who goes first */
    cout << "Do you want to play X or O: ";
    cin >> line;
    player = line[0];
    if (player == 'X') computer = 'O';
    else computer = 'X';
    int win = 0;
    win = run(scores, computer);
    if (!win)
        cout << "\nFinal score: \nX: " << scores[0] << "\nO: " << scores[1] << "\n";

    return 0;
}
