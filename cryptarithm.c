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
  char again;

  // Initialize a static cryptarithm. We are stubbing one out as the purpose
  // of this program is really just to test the verification algorithm.
  strcpy(cryptarithm->first, "send");
  strcpy(cryptarithm->second, "more");
  strcpy(cryptarithm->answer, "money");

  displayRules();

  do {

    displayPuzzle(cryptarithm);
    printf("Enter your solution one line at a time.\n\n");
    // Get the solution attempt from the user
    getInput(solution->first, "first", cryptarithm->first);
    getInput(solution->second, "second", cryptarithm->second);
    getInput(solution->answer, "answer", cryptarithm->answer);

    solved = isSolved(cryptarithm, solution);

    if (solved) {
      printf("Solved!\n");
      again = 'n';
    } else {
      printf("Not solved. Try again? (y = again; other = quit): ");
      again = getchar();
      getchar();  // Throw out newline
    }
 } while (again == 'y');

  return 0;
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
  // List to hold the puzzle to solution mappings
  struct LinkedList* puzzleMap = linkedListCreate();
  // To hold the map that is currently being processed
  struct Crypt* currentCrypt = NULL;
  // To hold the map that is being compared to current
  struct Crypt* compareCrypt = NULL;
  struct Iterator* iterator = NULL;

  // Checking for a valid equation is trivial. If the first and second
  // row added together does not equal the answer row, we can return
  // that it's not solved. Otherwise, we need to continue by checking the
  // first criteria (one-to-one mapping).
  if ((atoi(solution->first) + atoi(solution->second)) != atoi(solution->answer)) {
    return 0;
  }

  // Map the puzzle letters to the solution digits in a list of structs
  // one line at a time.
  for (int i = 0; i < strlen(solution->first); i++) {
    currentCrypt = createCrypt(cryptarithm->first[i], solution->first[i]);
    linkedListAddFront(puzzleMap, currentCrypt);
  }
  for (int i = 0; i < strlen(solution->second); i++) {
    currentCrypt = createCrypt(cryptarithm->second[i], solution->second[i]);
    linkedListAddFront(puzzleMap, currentCrypt);
  }
  for (int i = 0; i < strlen(solution->answer); i++) {
    currentCrypt = createCrypt(cryptarithm->answer[i], solution->answer[i]);
    linkedListAddFront(puzzleMap, currentCrypt);
  }

  // Now we are going to go through the list to make sure there is a one-to-one
  // mapping of puzzle letters to solution digits. We'll remove them one at
  // a time to check against the remaining mappings until the list is empty
  // or until we find an instance where a digit in the current mapping
  // is being used to represent a different letter. In this case, we can
  // immediately return 0 to indicate not solved.
  while (!linkedListIsEmpty(puzzleMap)) {
    // Get the first mapping and remove it from the list
    currentCrypt = linkedListFront(puzzleMap);
    linkedListRemoveFront(puzzleMap);
    // Create the list iterator and loop through the remaining mappings
    iterator = createIterator(puzzleMap);
    while (iteratorHasNext(iterator)) {
      compareCrypt = iteratorNext(iterator);
      // If the letters match but the digits don't, or if the digits match
      // but the letters don't; we don't have a 1:1 mapping and can return 0
      if ((currentCrypt->puzzle == compareCrypt->puzzle && 
           currentCrypt->solution != compareCrypt->solution) || 
           (currentCrypt->puzzle != compareCrypt->puzzle && 
           currentCrypt->solution == compareCrypt->solution)) {
        // Clean up memory before returning
        iteratorDestroy(iterator);
        linkedListDestroy(puzzleMap);
        return 0;
      }
      // If our current map does match our compare map, we can remove the
      // compare map we are currently looking at. This isn't strictly
      // necessary, but can speed things up on large data sets.
      if (currentCrypt->puzzle == compareCrypt->puzzle && 
           currentCrypt->solution == compareCrypt->solution) {
        iteratorRemove(iterator);
      }
    }
    // Destroy the iterator before we loop again as we will need a new
    // iterator instance for each loop.
    iteratorDestroy(iterator);
  }

  // Clean up memory allocation before returning
  linkedListDestroy(puzzleMap);
  // List is now empty, so we have confirmed 1:1 mapping
  return 1;

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
  int isValid;  // Flag for input validation
  do {
    isValid = 1;
    printf("Enter solution for the %s row (\"%s\"): ", inputRow, puzzleRow);
    fgets(buffer, MAX_INPUT, stdin);
    // Entries starting with a 0 are not valid.
    if (buffer[0] == '0') {
      isValid = 0;
      printf("Invalid entry! Leading digit cannot be zero (0)\n");
      // Entries that are not the same length as the puzzle row are not valid
      // and we can also catch some entries that can't convert to an int
    } else if (strlen(buffer) != strlen(puzzleRow) + 1 || atoi(buffer) < minValid) {
      isValid = 0;
      printf("Invalid entry! Row solution must have %ld digits.\n", strlen(puzzleRow));
    }
  } while (!isValid);
  // Hack off the newline character before storing the input
  buffer[strlen(buffer) - 1] = '\0';
  strcpy(input, buffer);
}

/**
 *  Simple function to display the puzzle.
 */
void displayPuzzle(struct Puzzle* cryptarithm)
{
  printf("  %s\n+ %s\n------\n %s\n\n", cryptarithm->first, 
          cryptarithm->second, cryptarithm->answer);
}

/**
 *  Simple function to display the rules of the game.
 */
void displayRules()
{
  printf("To solve the following cryptarithm, you will need to replace\n");
  printf("each letter with a digit 0-9 such that the resulting mathematical\n");
  printf("formula is correctly satisfied. In addition, the digits you choose\n");
  printf("must form a one-to-one mapping with the letters. That is, each\n");
  printf("letter is represented by one digit, and each digit can only\n");
  printf("represent one letter (e.g., 'n' will always be represented\n");
  printf("by the same number, and that number will not represent any other\n");
  printf("letter. Finally, your numbers cannot start with 0.\n\n");
}