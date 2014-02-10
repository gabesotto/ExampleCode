Game of Life
http://en.wikipedia.org/wiki/Conway's_Game_of_Life
=====================
The input will be a game board of cells, either alive (1) or dead (0).

The code should take this board and create a new board for the
next generation based on the following rules:
1) Any live cell with fewer than two live neighbours dies 
(under-population)

2) Any live cell with two or three live neighbours lives on to
the next generation (survival)

3) Any live cell with more than three live neighbours dies
(overcrowding)

4) Any dead cell with exactly three live neighbours becomes a
live cell (reproduction)
As an example, this game board as input:

0 1 0 0 0 
1 0 0 1 1 
1 1 0 0 1 
0 1 0 0 0 
1 0 0 0 1

Will have a subsequent generation of:

0 0 0 0 0 
1 0 1 1 1 
1 1 1 1 1 
0 1 0 0 0 
0 0 0 0 0 


============
Usage:

The game of life java code is a simple java class that can be 
instantiated with a 2-d array of 1's and 0's and can step through
generations of life following the rules of the game.

Public Class Life:

Constructor:
Life(int[][] input)
	Constructs a Game of life board, input must be a 'square' 2d array
	of 1's and 0's. 
	
	Throws - IllegalArgumentException if board isn't square or contains
				values other than 0 or 1.
	
Method Summary:
Void step()
	Updates the game state one generation according to the rules.
	
Void printArray()
	Prints the game board to stdout
	


