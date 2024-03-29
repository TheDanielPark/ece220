#include "game.h"
/*Name: Daniel Park | netid: danielp7 | date: 11/1/19
Intro: I approached this project by first creating the basic functions of creating the game. I then approached the move methods by
first trying to see if I could slide a number from one position up one. Once I figured out how to move it up one position, I tried to move it more 
and then tried to merge. After, I created a loop to keep sliding and merging until it completed the cycle and moved completely.
This project was very difficult and confusing. I really have no idea why it starts typing after I press s but I know the move_s function works.
*/
game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    int score;
    score = 0;
    int i,j;
    // initialize cols rows and score.
    mygame->cols = cols;
    mygame->rows = rows;
    mygame->score = 0;
    // set all values to -1
    for (i = 0; i < rows; i++) {
      for (j = 0; j < cols; j++) {
	mygame->cells[i*cols + j] = -1;
      }
    }
  

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	int score;
	score = 0;
	int i,j;
	// initlaize cols, rows, and score
         (*_cur_game_ptr)->cols = new_cols;
    (*_cur_game_ptr)->rows = new_rows;
     (*_cur_game_ptr)->score = 0;
     // reset the board
	for (i = 0; i < new_rows; i++) {
	  for (j = 0; j < new_cols; j++) {
	    (*_cur_game_ptr)->cells[i*new_cols + j] = -1;
	  }
	}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
  if (row < cur_game->rows && col < cur_game->cols && row > -1 && col > -1) {
    return &cur_game->cells[row * cur_game->cols + col];
  }
    return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
  int row, col, row1;
  int repeat;
  int doubled;
  int check;
  int checkRow;
  int score;
  //loop to repeat the slide and merge
  for (repeat = 0; repeat < cur_game->rows; repeat++) {
    //loop to iterate through every position
  for (col = 0; col < cur_game->cols; col++) {
    for (row = 0; row < cur_game->rows - 1; row++) {
      //slide if it is -1
      if (cur_game->cells[row*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols + col] = cur_game->cells[(row+1)*cur_game->cols + col];
	cur_game->cells[(row+1)*cur_game->cols+col] = -1;
      }
    }
  }
  }
 for (col = 0; col < cur_game->cols; col++) {
    for (row1 = 0; row1 < cur_game->rows - 1; row1++) {
      //merge if the two values are same
      if (cur_game->cells[row1*cur_game->cols + col] == cur_game->cells[(row1+1)*cur_game->cols + col] && cur_game->cells[row1*cur_game->cols + col] != -1) {
	doubled = cur_game->cells[row1*cur_game->cols + col] + cur_game->cells[(row1+1)*cur_game->cols + col];
	cur_game->cells[row1*cur_game->cols+col] = doubled;
	cur_game->cells[(row1+1)*cur_game->cols+col] = -1;
	cur_game->score += doubled;
	check++;
      }
    }
    for (checkRow = 0; checkRow < cur_game->rows - 1; checkRow++) {
      //slide again
      if (cur_game->cells[checkRow*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[checkRow*cur_game->cols + col] = cur_game->cells[(checkRow+1)*cur_game->cols + col];
	cur_game->cells[(checkRow+1)*cur_game->cols+col] = -1;
      }
    }
 }
  
      /*     if (cur_game->cells[row*cur_game->cols + col] != -1) {
	for (checkRow = 0; checkRow < cur_game->rows; checkRow++) {
	  if (cur_game->cells[checkRow*cur_game->cols + col] == cur_game->cells[row*cur_game->cols + col] && merged == 0) {
	    merged = 1;
	    doubled = cur_game->cells[checkRow*cur_game->cols+col] + cur_game->cells[checkRow*cur_game->cols+col];
	    cur_game->cells[checkRow*cur_game->cols+col] = doubled;
	    cur_game->cells[row*cur_game->cols + col] = -1;
	    check++;
	    score = score + doubled;
	  } else if (cur_game->cells[(checkRow)*cur_game->cols + col] == -1) {
	    cur_game->cells[checkRow*cur_game->cols + col] = cur_game->cells[row*cur_game->cols + col];
	    cur_game->cells[row*cur_game->cols + col] = -1;
	    check++;
	  }
	}
	} 
    }
  } */
 //check to see if there was a move done
  if (check == 0) {
    return 0;
  }
  return 1;
  
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
  int row, col, row1;
  
  int doubled;
  int check ;
  int checkRow;
  check = 0;
  int repeat;
  for (repeat = 0; repeat = cur_game->rows; repeat++) {
  for (col = cur_game->cols - 1; col > -1; col--) {
    for (row = cur_game->rows - 1; row > 0; row--) {
      if (cur_game->cells[row*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols + col] = cur_game->cells[(row-1)*cur_game->cols + col];
	cur_game->cells[(row-1)*cur_game->cols + col] = -1;
      }
    }
  }
  }
 for (col = cur_game->cols - 1; col > -1; col--) {
    for (row1 = cur_game->rows - 1; row1 > 0; row1--) {
      if (cur_game->cells[row1*cur_game->cols + col] == cur_game->cells[(row1-1)*cur_game->cols + col] && cur_game->cells[row1*cur_game->cols + col] != -1) {
	doubled = cur_game->cells[row1*cur_game->cols + col] + cur_game->cells[(row1-1)*cur_game->cols + col];
	cur_game->cells[row1*cur_game->cols+col] = doubled;
	cur_game->cells[(row1-1)*cur_game->cols + col] = -1;
	cur_game->score += doubled;
      }
    }
    for (checkRow = cur_game->rows - 1; checkRow>0; checkRow--) {
      if (cur_game->cells[checkRow*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[checkRow*cur_game->cols + col] = cur_game->cells[(checkRow-1)*cur_game->cols + col];
	cur_game->cells[(checkRow-1)*cur_game->cols + col] = -1;
      }
    }
 }

  /*
  for (col = 0; col < cur_game->cols; col++) {
    merged = 0;
    for (row = cur_game->rows - 2; row > -1; row--) {
      if (cur_game->cells[row*cur_game->cols + col] != -1) {
	for (checkRow = row + 1; checkRow > row; checkRow--) {
	  if (cur_game->cells[checkRow*cur_game->cols + col] == cur_game->cells[row*cur_game->cols + col] && merged == 0) {
	    merged = 1;
	    doubled = cur_game->cells[checkRow*cur_game->cols+col] + cur_game->cells[checkRow*cur_game->cols+col];
	    cur_game->cells[checkRow*cur_game->cols+col] = doubled;
	    cur_game->cells[row*cur_game->cols + col] = -1;
	    check++;
	    score = score + doubled;
	  } else if (cur_game->cells[(checkRow)*cur_game->cols + col] == -1) {
	    cur_game->cells[checkRow*cur_game->cols + col] = cur_game->cells[row*cur_game->cols + col];
	    cur_game->cells[row*cur_game->cols + col] = -1;
	    check++;
	  }
	}
      }
    }
    } */
  if (check == 0) {
    return 0;
  }
    return 1;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE

  int row, col, row1;
 
  int doubled;
  int check;
  int checkRow;
  int repeat;
  check = 0;
  //repeat the loop until it is complete
  for (repeat = 0; repeat < cur_game->rows; repeat++) {
    //iterate through every space
for (row = 0; row < cur_game->rows ; row++) {
  for (col = 0; col < cur_game->cols - 1; col++) {
    //slide if blank
      if (cur_game->cells[row*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols + col] = cur_game->cells[(row)*cur_game->cols + col + 1];
	cur_game->cells[(row)*cur_game->cols+col + 1] = -1;
      }
  }
 }
  }
for (row = 0; row < cur_game->rows ; row++) {
    for (row1 = 0; row1 < cur_game->cols - 1; row1++) {
      //merge if same
      if (cur_game->cells[row*cur_game->cols + row1] == cur_game->cells[row*cur_game->cols + row1 + 1] && cur_game->cells[row*cur_game->cols + row1] != -1) {
	doubled = cur_game->cells[row*cur_game->cols + row1] + cur_game->cells[row*cur_game->cols + row1 + 1];
	cur_game->cells[row*cur_game->cols+row1] = doubled;
	cur_game->cells[row*cur_game->cols+row1 + 1] = -1;
	cur_game->score += doubled;
	check++;
      }
    }
    for (checkRow = 0; checkRow < cur_game->cols - 1; checkRow++) {
      //slide one more time
      if (cur_game->cells[row*cur_game->cols + checkRow] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols + checkRow] = cur_game->cells[row*cur_game->cols + checkRow + 1];
	cur_game->cells[row*cur_game->cols+checkRow + 1] = -1;
      }
    }
 }
  /*
 int row, col, row1;
 
  int doubled;
  int check = 0;
  int checkRow;
  int score;
  for (col = cur_game->cols -2; col > -1; col--) {
    for (row = cur_game->rows - 1; row > -1; row--) {
      if (cur_game->cells[row*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols + col] = cur_game->cells[(row)*cur_game->cols + col + 1];
	cur_game->cells[(row)*cur_game->cols + col + 1] = -1;
      }
    }
    for (row1 = cur_game->rows - 1; row1 > -1; row1--) {
      if (cur_game->cells[row1*cur_game->cols + col] == cur_game->cells[(row1)*cur_game->cols + col+1]) {
	doubled = cur_game->cells[row1*cur_game->cols + col] + cur_game->cells[(row1)*cur_game->cols + col + 1];
	cur_game->cells[row1*cur_game->cols+col] = doubled;
	score += doubled;
	cur_game->cells[(row1)*cur_game->cols + col + 1] = -1;
      }
    }
    for (checkRow = cur_game->rows - 1; checkRow > -1; checkRow--) {
      if (cur_game->cells[checkRow*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[checkRow*cur_game->cols + col] = cur_game->cells[(checkRow)*cur_game->cols + col + 1];
	cur_game->cells[(checkRow)*cur_game->cols + col + 1] = -1;
      }
    }
  } */


  /*
  for (row = 0; row < cur_game->rows; row++) {
    merged = 0;
    for (col = cur_game->cols - 1; col > 0; col--) {
      if (cur_game->cells[row*cur_game->cols + col] != -1) {
	for (checkCol = col - 1; checkCol < col; checkCol++) {
	  if (cur_game->cells[checkCol*cur_game->cols + col] == cur_game->cells[row*cur_game->cols + col] && merged == 0) {
	    merged = 1;
	    doubled = cur_game->cells[checkCol*cur_game->cols+col] + cur_game->cells[checkCol*cur_game->cols+col];
	    cur_game->cells[checkCol*cur_game->cols+col] = doubled;
	    cur_game->cells[col*cur_game->cols + col] = -1;
	    check++;
	    score = score + doubled;
	  } else if (cur_game->cells[(checkCol)*cur_game->cols + col] == -1) {
	    cur_game->cells[checkCol*cur_game->cols + col] = cur_game->cells[col*cur_game->cols + col];
	    cur_game->cells[col*cur_game->cols + col] = -1;
	    check++;
	  }
	}
      }
    }
    } */
// check if move was done
  if (check == 0) {
    return 0;
  }
  return 1;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
   int row, col, row1;
  
  int doubled;
  int check ;
  int checkRow;

  check = 0;
  int repeat;
  // repeat the loop till finished
  for (repeat = 0; repeat < cur_game->cols; repeat++){
 for (row = cur_game->rows - 1; row > -1; row--) {
  for (col = cur_game->cols - 1; col > 0; col--) {
    //slide if blank
      if (cur_game->cells[row*cur_game->cols + col] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols + col] = cur_game->cells[(row)*cur_game->cols + col -1];
	cur_game->cells[(row)*cur_game->cols + col - 1] = -1;
      }
    }
 }
  }
 for (row = cur_game->rows - 1; row > -1; row--) {
   // check if merge is possible and merge
    for (row1 = cur_game->cols - 1; row1 > 0; row1--) {
      if (cur_game->cells[row*cur_game->cols +row1] == cur_game->cells[(row)*cur_game->cols + row1 - 1] && cur_game->cells[row*cur_game->cols+row1] != -1) {
	doubled = cur_game->cells[row*cur_game->cols + row1] + cur_game->cells[(row)*cur_game->cols + row1 - 1];
	cur_game->cells[row*cur_game->cols+row1] = doubled;
	cur_game->cells[(row)*cur_game->cols +row1 - 1] = -1;
	cur_game->score += doubled;
	check++;
      }
    }
    //slide one more time
    for (checkRow = cur_game->cols - 1; checkRow > 0; checkRow--) {
      if (cur_game->cells[row*cur_game->cols + checkRow] == -1) {
	check++;
	cur_game->cells[row*cur_game->cols +checkRow] = cur_game->cells[(row)*cur_game->cols + checkRow - 1];
	cur_game->cells[(row)*cur_game->cols + checkRow -1] = -1;
      }
    }
 }
  
  


  /*
  for (row = 0; row < cur_game->rows; row++) {
    merged = 0;
    for (col = 1; col < cur_game->cols; col++) {
      if (cur_game->cells[row*cur_game->cols + col] != -1) {
	for (checkCol = col - 1; checkCol < col; checkCol++) {
	  if (cur_game->cells[checkCol*cur_game->cols + col] == cur_game->cells[row*cur_game->cols + col] && merged == 0) {
	    merged = 1;
	    doubled = cur_game->cells[checkCol*cur_game->cols+col] + cur_game->cells[checkCol*cur_game->cols+col];
	    cur_game->cells[col*cur_game->cols+col] = doubled;
	    cur_game->cells[checkCol*cur_game->cols + col] = -1;
	    check++;
	    score = score + doubled;
	  } else if (cur_game->cells[(col)*cur_game->cols + col] == -1) {
	    cur_game->cells[col*cur_game->cols + col] = cur_game->cells[checkCol*cur_game->cols + col];
	    cur_game->cells[checkCol*cur_game->cols + col] = -1;
	    check++;
	  }
	}
      }
    }
    } */
  if (check == 0) {
    return 0;
  }
  return 1;
  
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
  int row,col;
  //iterate through each space and see if a move is possible
  for (row = 0; row < cur_game->rows; row++) {
    for (col = 0; col < cur_game->cols; col++) {
      if (cur_game->cells[row*cur_game->cols + col] == -1) {
	return 1;
      }
      if (row <= 0 && cur_game->cells[row*cur_game->cols + col] == cur_game->cells[(row+1)*cur_game->cols + col]) {
	return 1;
      }
      if (col <= 0 && cur_game->cells[row*cur_game->cols + col] == cur_game->cells[(row)*cur_game->cols + col+1]) {
	return 1;
      }
    }
  }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
