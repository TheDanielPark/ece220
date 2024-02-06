#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
/*Name: Daniel Park | Date: 11/14/19 | NETID: danielp7
Intro: I approached this problem using my knowledge on linked lists. I made sure to load the tuples based on the given text file. I created set 
tuples and used it in load in order to set the certain tuples to certain values based on what the text file input was. After going through
the whole file, I set up a matrix in load tuples. I really had a tough time with this MP so the multiplication and addition I just tried to use
the code given on the MP site. I also am unsure if this all works in a little way. I did try but I am just very confused with this MP.

*/




sp_tuples * load_tuples(char* input_file)
{
  long int row, col;
  long double value;
  //Check and make sure the file can be read
  FILE* file;
  file = fopen(input_file, "r");
  if (file == NULL) {
    printf("Could not read file\n");
    fclose(file);
    return NULL;
  }
  //allocate memory for spTuples
  sp_tuples * spTuples = (sp_tuples*)malloc(sizeof(sp_tuples));
  spTuples->tuples_head = NULL;
  //scan the row and col of the array
  fscanf(file, "%d %d\n", &(spTuples->m), &(spTuples->n));
 
  //scan the line for the values needed to store into the array
  while (fscanf(file, "%ld %ld %Lf\n", &row, &col, &value) == 3) {
    set_tuples(spTuples, row, col, value);
  }
  //set a variable current to the head of the tuples node created
  sp_tuples_node * current = spTuples->tuples_head;
  //set the number of non zero values to zero
  spTuples->nz = 0;
  //count the amount of non zeros there are and store in nz
  while ( current != NULL) {
    spTuples->nz += 1;
    current = current->next;
  }

  fclose(file);
  
  
  return spTuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  //set a variable current to the head
  sp_tuples_node * current = mat_t->tuples_head;
  // as long as current is not null, return the value if the row and col match the ones asked for. If not, go to the next node
  while (NULL != current) {
    if (current->row == row && current->col == col) {
      return current->value;
    } else {
      current = current->next;
    }
  }
    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  sp_tuples_node ** temp;
  sp_tuples_node * temp2;
    sp_tuples_node * temp3;
  //if the head is null but there is a value, create a node and put the value inside where the row and col should be
 
  /*  if (mat_t->tuples_head == NULL && value != 0) {
    mat_t->tuples_head = malloc(sizeof(sp_tuples_node));
    mat_t->tuples_head->row = row;
    mat_t->tuples_head->col = col;
    mat_t->tuples_head->value = value;
    mat_t->tuples_head->next = NULL;
    mat_t->nz += 1;
    return;
    }  */
  //make a temp node with null
  temp = &(mat_t->tuples_head);
  temp2 = NULL;
  temp3 = NULL;
  //As long as temp isn't null, go through until you reach either a null node or the correct row/col
  
  while (*temp != NULL && row > (*temp)->row) {
    temp = &(*temp)->next;
  }
  while (*temp != NULL && row == (*temp)->row && col > (*temp)->col) {
    temp = &(*temp)->next;
    }
  

   // check to see if anything repeats
  if (*temp != NULL && row == (*temp)->row && col == (*temp)->col) {
    if (value == 0) {
      //make sure temp isn't at head
      if (*temp != NULL) {
	temp2 = *temp;
	*temp = (*temp)->next;
	free(temp2);
      }
      mat_t->nz += -1;
    }
  } else if (value != 0) { //if value is not zero and we have not written in this row and column before, create new node
    //if it is at head of node
    if(temp2 == NULL) {
  
      temp3 = malloc(sizeof(sp_tuples_node));
      temp3->row = row;
      temp3->col = col;
      temp3->value = value;
      temp3->next = *temp;
      *temp = temp3;
      mat_t->nz += 1;
     }
      
  }
    
      

    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  //Save the final array/linked list into a file.
  FILE * file = fopen(file_name, "w");
  fprintf(file, "%d %d\n", mat_t->m, mat_t->n);
  sp_tuples_node * temp = mat_t->tuples_head;
  while (temp != NULL) {
    fprintf(file, "%d %d %f\n", temp->row, temp->col, temp->value);
    temp = temp->next;
  }
  fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
 
  sp_tuples * matC = (sp_tuples*)malloc(sizeof(sp_tuples));
  matC->m = matA->m;
  matC->n = matA->n;
  matC->tuples_head = NULL;
    sp_tuples_node * tempA = matA->tuples_head;
  sp_tuples_node * tempB = matB->tuples_head;
  if(matA->m == matB->m && matA->n == matB->n) {

    while (tempA != NULL) {
      set_tuples(matC, tempA->row, tempA->col, tempA->value + tempB->value); 
      tempB = tempB->next;
      tempA = tempA->next;
    }
    
  


    sp_tuples_node * current = matC->tuples_head;
    //set the number of non zero values to zero
    matC->nz = 0;
    //count the amount of non zeros there are and store in nz
    while ( current != NULL) {
      matC->nz += 1;
      current = current->next;
    }
    
    return matC;
  }
  return NULL; 
  //	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 

  
  return NULL;
  // return retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
  // while mainNode isn't nuull, free very single node until you get to the end. Then clear out the head node.
  sp_tuples_node * mainNode = mat_t->tuples_head;
  sp_tuples_node * temp;
  while (NULL != mainNode) {
    temp = mainNode;
    mainNode = mainNode->next;
    free(temp);
  }
  mat_t->tuples_head = NULL;
  free(mat_t);

  return;
}  






