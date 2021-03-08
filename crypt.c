/* 
 * Filename: crypt.c
 * Author: Aaron Ennis
 * Email: ennisa@oregonstate.edu
 * Last modified: 06 March 2021
 * Description: This is the implementation file that defines a structure
 * to contain a cryptarithm mapping, and some simple functions to operate 
 * on the structure.
 */

#include "crypt.h"
#include <stdlib.h>

/** 
 * This function creates a cryptarithm mapping
 * Parameters: A character and an accompanying digit as a character
 * Return value: A pointer to a structure containing the cryptarithm mapping
 */
struct Crypt* createCrypt(char puzzle, char solution)
{
  struct Crypt* newCrypt = malloc(sizeof(struct Crypt));

  newCrypt->puzzle = puzzle;
  newCrypt->solution = solution;

  return newCrypt;
}

/**
 *  This function takes a Crypt struct as a parameter and free up the memory
 *  allocated to hold the Crypt.
 */
void destroyCrypt(struct Crypt* crypt) 
{
  free(crypt);
}