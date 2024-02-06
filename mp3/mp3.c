#include <stdio.h>
#include <stdlib.h>
/* Name: Daniel Park | NetID: danielp7 | Date: 9/24/19
I wrote this code based on the equation given. I made sure i had the loop to 
iterate through all the numbers needed and then I printed the final variable.

*/

int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  int i;
  int k;
  unsigned long int coef = 1;	//initialize the variabes
  k = row;			//make a variable equal to row number
  printf("1 ");
  for (i = 1; i <= k; i++){	//For loop condition and start
    coef = coef * (k + 1 - i);	//Start the first step of equation
    coef = coef / i;		//Finish second step of equation
    printf("%lu ", coef);	//Print the coefficient.
  }

  return 0;
}
