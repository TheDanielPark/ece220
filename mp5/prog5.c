/*			
 *
Name: Daniel Park | NETID: danielp7 | Date: 10/9/19
Intro: The goal of this program was to created a game that took user input and checked if it matched a string of numbers randomly generated.
I approached by first writing the method to set the seed and create the solution number, then I tracked the input of the user to check
if any of his guesses were correct or if his numbers were just misplaced. The set_seed method checks for an input by user and if it is a 
valid input, it sets a solution. The start_game stores values into an array that creates the solution combination. The make_guess method 
takes user input and compares it to the solution and tells the user if they have any perfect guesses or misplaced ones. 

 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number = 1;
static int solution1;
static int solution2;
static int solution3;
static int solution4;

/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
  int seed;
  char post[2];
  //Check if the seed is just 1 number
    if ((sscanf(seed_str, "%d%1s", &seed, post)) == 1) {
      srand(seed);
      return 1;
    }
    //if not 1 number, invalid
  printf("set_seed: invalid seed\n");
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
  //store a random number between 1-8 into memory locations 1 2 3 and 4. Then set the solution equal to the corresponding number.
    *one = rand() % 8 + 1;
    solution1 = *one;
    *two = rand() % 8 + 1;
    solution2 = *two;
    *three = rand() % 8 + 1;
    solution3 = *three;
    *four = rand() % 8 + 1;
    solution4 = *four;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess 
typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
  int w, x, y, z;
  int correctGuesses = 0;
  int misplacedGuesses = 0;
  int pair1, pair2, pair3, pair4;
  char post[2];
  // check if the input is 4 integers
  if (sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 4) {
    //make sure the 4 integers are between 1-8 each
  if (w < 1 || w > 8 || x < 1 || x > 8 || y < 1 || y > 8 || z < 1 || z > 8 ) {
    printf("make_guess: invalid guess\n");
    return 0;
  }
  // set solution equal to the proper variables.
  *one = w;
  *two = x;
  *three = y;
  *four = z;
  pair1 = 0; 
  pair2 = 0;
  pair3 = 0;
  pair4 = 0;
  //Check if there are perfect matches
  if (w == solution1) {
    pair1 = 1;
    correctGuesses++;
  }
  if (x == solution2) {
    pair2 = 1;
    correctGuesses++;
  }
  if (y == solution3) {
    pair3 = 1;
    correctGuesses++;
  }
  if (z == solution4) {
    pair4 = 1;
    correctGuesses++;
  }
  //Check if there are misplaced matches
  if (pair1 != 1) {
    if (pair2 != 1 && w == solution2) {
      //  pair2 = 1;
      misplacedGuesses++;
    } else if (pair3 != 1 && w == solution3) {
      //     pair3 = 1;
      misplacedGuesses++;
    } else if (pair4 != 1 && w == solution4) {
      //    pair4 = 1;
      misplacedGuesses++;
    }
  }
  if (pair2 != 1) {
    if (pair1 != 1 && x == solution1) {
      //    pair1 = 1; 
      misplacedGuesses++;
    } else if (pair3 != 1 && x == solution3) {
      //    pair3 = 1;
      misplacedGuesses++;
    } else if (pair4 != 1 && x == solution4) {
      //    pair4 = 1; 
      misplacedGuesses++;
    }
  }
  if (pair3 != 1) {
    if (pair1 != 1 && y == solution1) {
      //   pair1 = 1;
      misplacedGuesses++;
    } else if (pair2 != 1 && y == solution2) {
      //    pair2 = 1;
      misplacedGuesses++;
    } else if (pair4 != 1 && y == solution4) {
      //    pair4 = 1;
      misplacedGuesses++;
    }
  }
  if (pair4 != 1) {
    if (pair1 != 1 && z == solution1) {
      //    pair1 = 1;
      misplacedGuesses++;
    } else if (pair2 != 1 && z == solution2) {
      //    pair2 = 1;
      misplacedGuesses++;
    } else if (pair3 != 1 && z == solution3) {
      //    pair3 = 1;
      misplacedGuesses++;
    }
  }
  //print the sentence to show how many guesses, correct guesses, and misplaced guesses.
  printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, correctGuesses, misplacedGuesses);
  /*  if (correctGuesses == 4) {
    printf("You guessed correctly in %d guesses.\n", guess_number);
    return 1;
    } */
  //increment gues counter
  guess_number++;
  return 1;
}
  // print invalid if it is not a valid guess.
printf("make_guess: invalid guess\n");

return 0;
}


