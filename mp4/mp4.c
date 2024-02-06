#include <stdlib.h>
#include <stdio.h>
/* Name: Daniel Park | NETID: danielp7 | Date: 10/2/19
Description: I made a method is prime in order to check if a number is prime. Then I created a method called semiprime in order to check if it is semi prime and if it is, print the number. 
Partners: jayhp2
*/

int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   return print_semiprimes(a, b);    // Call method
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
  int i;
  for (i = 2; i < number; i = i + 1) {    //Check if the input is a prime by                                                dividing by i
    if (number % i == 0) {
      return 0;
    }
  }
  return 1;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
  int i; //Variable to store a through b
  int counter = 0; // Variable to be a counter.
  int k; 
  int check; // Variable to store i/k
  
  for (i = a; i <= b; i = i + 1) {
    //  printf("i = %d ", i);
    for (k = 2; k <= (i - 1) ; k = k + 1) {
      //  printf("k =  %d ", k);
      if ((i%k)!= 0) {           //Just continue the loop if i/k is not prime
	continue;
      }
      check = i / k;
      // Check if k is prime,i/k is prime, and to see if it repeats.
      if (is_prime(k) == 1 && is_prime(check)== 1 && k <= (i/k)) { 
	printf("%d ", i);
	counter = counter + 1;
	//	printf("2nd loop");
      }
    }
  }
  if (counter == 0) {
    //  printf("Counter is zero");
    return 0;
  }
  return 1;
}



