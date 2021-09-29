
# Cryptarithm

This is my portfolio assignment for **CS 325: Analysis of Algorithms**

This README file contains simple instructions for compiling and running the
programs contained in this directory.

## Compiling Instructions

To compile, simply run 'make' in the project directory. This will create an
executable called 'cryptarithm'.

## Gameplay Instructions

This is a simple command line version of a cryptarithm puzzle. For this
implementation, I am using a single well-known cryptarithm stubbed as a
driver to test a general algorithm for verifying the correctness of a solution
to a cryptarithm.

To play, simply run the 'cryptarithm' executable and follow the instructions
in the terminal. You will be presented with the well-known cryptarithm:
```
   send
 + more
 ------
  money
```
You will then be prompted to enter your solution one line/row at a time. A valid
solution will meet the following criteria:

	1) Each letter will be represented by a digit 0-9.
	2) Any instance of a letter will be represented by the same digit.
	3) No digits will represent more than one letter.
	4) Solution rows cannot start with a 0.
	5) The resulting mathematical formula must be correctly satisfied.

For testing purposes, the solution to the above cryptarithm is as follows:
```
   9567
 + 1085
 ------
  10652
  ```
