#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
/* Name: Daniel Park | NETID: danielp7 | date: 11/9/19
intro: I approached this project by first knowing I needed to create a double array. I did this
in order to format the maze I needed to create. I set up the properties of the array given by
the maze.h file and made sure everything was checked. Then I went through to solve the array
by reading each space around and just going through the array until E was found.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
  int i= 0, j, x, y;
  size_t length= 0;
  ssize_t test;
  char * charArray;
  //open file and check if it is null
  FILE * mainFile = fopen(fileName, "r");
  if (mainFile == NULL) {
    printf("File does not exist");
    fclose (mainFile);
    return NULL;
  }
  //scan the dimensions and store it
  fscanf(mainFile, "%d %d\n", &x, &y);
  // allocate memory for the maze
  maze_t * mainMaze;
  mainMaze = (maze_t*)malloc(sizeof(maze_t));
  // make sure maze is not null
   if (mainMaze != NULL) {
     // set values for the maze
    mainMaze->width = x;
    mainMaze->height = y;
    mainMaze->cells = (char **)malloc(y*sizeof(char*));
    //loop 
     for (i = 0; i < y; i++) {
       //make sure it reads a line
          test = getline(&charArray, &length, mainFile);
       	 if (test != -1) {
	   //allocate memory
	   mainMaze->cells[i] = (char*)malloc(mainMaze->width * sizeof(char));
	   // store the values of where E and S are
	   for (j = 0; j < x; j++) {
	     mainMaze->cells[i][j] = charArray[j];
	     if (mainMaze->cells[i][j] == 'E') {
	       mainMaze->endRow = i;
	       mainMaze->endColumn = j;
	     } else if (mainMaze->cells[i][j] == 'S') {
	       mainMaze->startRow = i;
	       mainMaze->startColumn = j;
	     }
	   }
	 }
     }
   }
   //free the array memory, close the file, and return the maze
  free(charArray);
  fclose(mainFile);
  return mainMaze;
  

}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
  int i;
  //free memory of the inner array, then the main array, then the maze itself
  for (i = 0; i < maze->height; i++) {
    free(maze->cells[i]);
  }
  free(maze->cells);
  free(maze);
  return;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
  int i,j;
  // print each value
  for (i = 0; i < maze->height; i++) {
    for (j = 0; j < maze->width; j++) {
      printf("%c", maze->cells[i][j]);
    }
    printf("\n");
  }
  return ;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently being visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
  // base case to make sure it stays in bounds and it is not in a wall/previous checked space
  if (row < 0 || col < 0 || col>=maze->width || row>= maze->height || 
      maze->cells[row][col] == '%' || maze->cells[row][col] == '*'){
    return 0;
  }
  //return true if you find e
  if (maze->cells[row][col] == 'E'){
    return 1;
  }
  //mark space as solution
  maze->cells[row][col] = '*';
  //check the left, up, right, down spaces
  if (solveMazeDFS(maze, col-1,row) == 1) {
    return 1;
  }
  if (solveMazeDFS(maze, col, row-1) == 1) {
    return 1;
  }
  if (solveMazeDFS(maze, col+1, row) == 1) {
    return 1;
  }
  if (solveMazeDFS(maze, col, row+1) == 1) {
    return 1;
  }
  //set S as the starting space to not overwrite it
  maze->cells[maze->startRow][maze->startColumn] = 'S';
  //mark as checked
  maze->cells[row][col] = '~';

    return 0;
}
