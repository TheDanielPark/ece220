/*
  Name: Daniel Park | NETID: danielp7 | Date: 10/17/19
  Intro: I wrote this code based on the instructions given. My goal was to create a method that counted the amount of live neighbors around a single point.
  Then I made sure to create a copy of a board and create an update board method to create an updated board, but I made sure to update the copy and not the original to not alter the board. Then I created a method to check if the board did not update anymore and that meant it was stable. I have extra comments for things I used to test and other methods I used throughout my thought process.

 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int liveNeighbor = 0;
  int currRow;
  int currCol;
  // loop through each column per row to check each cell around the chosen cell.
  // if the board has a 1 in the position that is not the original spot, increment liveNeighbor.
  for (currRow = row - 1; currRow <= row + 1; currRow++) {
    if (currRow < boardRowSize && currRow >= 0) {
      for (currCol = col - 1; currCol <= col + 1; currCol++) {
	if (currCol < boardColSize && currCol >= 0) {
	  if (currRow != row || currCol != col) {
           if (board[(currRow*boardColSize) + currCol] == 1) {
	      liveNeighbor++;
	   }
	  }
	}
      }
    }
  }
  return liveNeighbor;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int row, col;
  int i;
  int boardCopy[boardRowSize*boardColSize];
  // int count;
  //  int status;
  // Create a copy of the board
  for (i = 0; i < (boardRowSize * boardColSize); i++) {
    boardCopy[i] = board[i];
    }
  //Loop through the original array and update it into the copy of the array
  for (row = 0; row < boardRowSize; row++) {
    for (col = 0; col < boardColSize; col++) {
        if (countLiveNeighbor(board, boardRowSize, boardColSize, row, col) == 3) {
	boardCopy[(row*boardColSize) + col] = 1;
      } else if (countLiveNeighbor(board, boardRowSize, boardColSize, row, col) != 2) {
        boardCopy[(row*boardColSize) + col] = 0;
      } 
      //  count = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);
      //  status = board[row*boardColSize + col];
      /* if (status == 1 && count == 3) {
	boardCopy[row*boardColSize + col] = 1;
      } else if (status == 0 && count == 3) {
	boardCopy[row*boardColSize + col] = 1;
      } else if (status == 1 && count == 2) {
	boardCopy[row*boardColSize + col] = 1;
      } else {
	boardCopy[row*boardColSize + col] = 0;
	} */
      /*  if (status == 1) {
	if (count == 2 || count == 3) {
	  boardCopy[row*boardColSize + col] = 1;
	} else {
	  boardCopy[row*boardColSize + col] = 0;
	}
      } else {
	if (count == 3) {
	  boardCopy[row*boardColSize + col] = 1;
	} else {
	  boardCopy[row*boardColSize + col] = 0;
	}
	} */
	  
      
      
    }
  }
  //Copy the new array into the original array
  for (i = 0; i < (boardRowSize * boardColSize); i++ ){
    board[i] = boardCopy[i];
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int counter;
  int i;
  int boardCopy[boardRowSize*boardColSize];
  for (i = 0; i < (boardRowSize * boardColSize); i++) {
    boardCopy[i] = board[i];
  }
  updateBoard(boardCopy, boardRowSize, boardColSize);
  for (counter = 0; counter < (boardRowSize * boardColSize); counter++) {
    if (boardCopy[counter] != board[counter]) {
      return 0;
    }
  }
  return 1;
}

				
				
			

