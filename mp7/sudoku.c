#include "sudoku.h"
/* Name: Daniel Park | NETID: danielp7 | date: 10/24/19
intro: I did this MP by first creating programs to check if if a number was valid based on each 
row, column, and 3x3 matrix. After that, I created the is valid method to make it easier to check if the
number was valid. I used this in my solve_sudoku method to make sure the sudoku was able to be solved. I approached
this MP by first iterating through the array to make sure there were zeros. If zeros were found, I would then place 
a value into that position in order to make that spot filled in order to solve the sudoku. Then, I used recursion
and recalled the method in order to check each spot until it was completed.
*/

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int k;
  //Go through row i and make sure val doesn't appear anywhere in it
  for (k = 0; k < 9; k++) {
    if (val == sudoku[i][k]) {
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int k;
  //Go through column j and make sure val doesn't appear anywhere in it
  for (k = 0; k < 9; k++) {
    if (val == sudoku[k][j]) {
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int k;
  int l;
  //Go through the 3x3 box and make sure val doesn't appear anywhere in it
  for (k = 0; k < 3; k++) {
    for (l = 0; l < 3; l++) {
      //i-(i%3) makes it so the first row of the 3x3 is 0 and so on to make sure the code works for each 3x3 box.
      if (val == sudoku[i-(i%3)+k][j-(j%3)+l]) {
	return 1;
      }
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  //call the other functions and make sure they are all valid to see if val is valid.
  if (is_val_in_row(val, i, sudoku) == 0 && is_val_in_col(val,j,sudoku) == 0 && 
      is_val_in_3x3_zone(val,i,j,sudoku) == 0) {
    return 1;
  }

  return 0;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j,k,l,val;
  int count = 0;
  // Loop to check if each space in the array is filled. If it is filled increment count
  for (k = 0; k < 9; k++) {
    for (l = 0; l < 9; l++) {
      if (sudoku[k][l] != 0) {
	count++;
      }
    }
  }
  // If each space in the array is not a 0 then it is solved.
  // if count is 81 then each space is filled
  if (count == 81) {
    return 1;
  }
  // set k and j equal to the i and j values
    for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
	if (sudoku[i][j] == 0) {
	  k = i; 
	  l = j;
	}
      }
    } 
    // Go through the array and fill in numbers where there are zeros
  for (val = 1; val < 10; val++) {
    if (is_val_valid(val,k,l,sudoku) == 1) {
      sudoku[k][l] = val;
      if (solve_sudoku(sudoku)) {
	return 1;
      }
      sudoku[k][l] = 0;
    }
    } 
  //IDK why this did not work (nvm I found out in office hours)
  /*	 for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (sudoku[i][j] == 0) {
	for (val = 1; val < 10; val++) {
	  if (is_val_valid(val,i,j,sudoku) == 1) {
	    sudoku[i][j] = val;
	    if (solve_sudoku(sudoku)) {
	      return 1;
	    }
	    //  sudoku[i][j] = 0;
	  }
	}
      }
    }
  } */
  
    
  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





