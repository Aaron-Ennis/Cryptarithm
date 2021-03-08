/* 
 * Filename: cryptarithm.c
 * Author: Aaron Ennis
 * Email: ennisa@oregonstate.edu
 * Last modified: 06 March 2021
 * Description: This is the main implementation file for a simple cryptarithm
 * puzzle that presents a user with a cryptarithm to solve. It then takes the
 * user's solution and verifies whether the solution is correct. The main
 * purpose of this program is to test the algorithm that verifies the
 * correctness of a cryptarithm solution, so we are using hard-coded well-known
 * cryptarithm in a standard format of two rows added together to produce
 * an "answer". Specifically:
 *  
 *    send
 *  + more
 *  ------
 *   money
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "linkedList.h"
#include "crypt.h"

#define MAX_INPUT 50

// We're building only a single puzzle for this program to test the
// verification algorithm, so these string lengths will be preset.
struct Puzzle {
  char first[5];
  char second[5];
  char answer[6];
};


void displayRules();
void displayPuzzle(struct Puzzle* cryptarithm);
void getInput(char* input, char* inputRow, char* puzzleRow);
int isSolved(struct Puzzle* cryptarithm, struct Puzzle* solution);

int main(int argc, char const *argv[])
{
  struct Puzzle* cryptarithm = malloc(sizeof(struct Puzzle));
  struct Puzzle* solution = malloc(sizeof(struct Puzzle));
  int solved;

  // Initialize a static cryptarithm. We are stubbing one out as the purpose
  // of this program is really just to test the verification algorithm.
  strcpy(cryptarithm->first, "send");
  strcpy(cryptarithm->second, "more");
  strcpy(cryptarithm->answer, "money");

  displayPuzzle(cryptarithm);


  // Get the solution attempt from the user
  getInput(solution->first, "first", cryptarithm->first);
  getInput(solution->second, "second", cryptarithm->second);
  getInput(solution->answer, "answer", cryptarithm->answer);

  solved = isSolved(cryptarithm, solution);

  return 0;
}

void displayPuzzle(struct Puzzle* cryptarithm)
{
  printf("  %s\n+ %s\n------\n %s\n\n", cryptarithm->first, cryptarithm->second,
                                  cryptarithm->answer);
}

/**
 *  This function takes a struct representing a cryparithm puzzle, and a struct
 *  representing a user-entered attempt at solving the cryptarithm. It then
 *  verifies whether or not the solution provided is correct. It returns 1 if
 *  solved and 0 if not solved.
 *  A correct solution must satisfy two criteria:
 *    1)  There must be a one-to-one mapping of letters to digits. That is,
 *        each letter must be represented by only one digit [0,9] (e.g., if
 *        there are two instances of 'n' in the puzzle, they must both be
 *        represented by the same digit. Likewise, a digit cannot map to
 *        more than one letter).
 *    2)  The resulting mapping of letters to digits must result in the 
 *        equation being correct.
 */

int isSolved(struct Puzzle* cryptarithm, struct Puzzle* solution)
{

  // Checking for a valid equation is trivial. If the first and second
  // row added together does not equal the answer row, we can return
  // that it's not solved. Otherwise, we need to continue by checking the
  // first criteria (one-to-one mapping).
  if ((atoi(solution->first) + atoi(solution->second)) != atoi(solution->answer)) {
    return 0;
  }

}


/**
 *  This function takes input from the user and does some basic input
 *  validation before copying the buffer into the input param.
 *  Params: char* input - a string pointer to store the validated input
 *          char* inputRow - a string literal to indicate the current row
 *                           for which we are getting a solution
 *          char* puzzleRow - the text from the current puzzle row  
 */
void getInput(char* input, char* inputRow, char* puzzleRow)
{
  char buffer[MAX_INPUT];
  // a valid entry will have the same number of digits as the length of
  // the puzzle clue for the row
  int minValid = pow(10, strlen(puzzleRow) - 1);
  do {
    printf("Enter solution for the %s row (\"%s\"): ", inputRow, puzzleRow);
    fgets(buffer, MAX_INPUT, stdin);
    if (strlen(buffer) != strlen(puzzleRow) + 1 || atoi(buffer) < minValid) {
      printf("Invalid entry! Row solution must have %ld digits.\n", strlen(puzzleRow));
    }
  } while (strlen(buffer) != strlen(puzzleRow) + 1 || atoi(buffer) < minValid);
  buffer[strlen(buffer) - 1] = '\0';
  strcpy(input, buffer);
}

