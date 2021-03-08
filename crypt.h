/* 
 * Filename: crypt.h
 * Author: Aaron Ennis
 * Email: ennisa@oregonstate.edu
 * Last modified: 06 March 2021
 * Description: This is the declaration/interface file that defines a structure
 * to contain information about a cryptarithm mapping, and some simple 
 * functions to operate on the structure.
 */

#ifndef CRYPT_H
#define CRYPT_H

/* Define the Crypt struct */
struct Crypt
{
  char puzzle;
  char solution;
};

struct Crypt* createCrypt(char puzzle, char solution);
void destroyCrypt(struct Crypt* crypt);

#endif