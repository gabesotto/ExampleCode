import java.util.Arrays;

public class Life{
	private int[][] board;
	
	//Constructor
	public Life(int[][] board){
		
		//Input check
		for(int i = 0; i < board.length; i++){
			
			//check that input is 'square'
			if(board[i].length != board.length){
				throw new IllegalArgumentException("Input 2d Array is not 'square'.");
			}
			
			for(int j = 0; j < board[0].length; j++){
				
				//check that input has only 1's and zero's
				if(board[i][j] != 1 && board[i][j] != 0){
					throw new IllegalArgumentException("Input 2d Array contains values other than 1's and 0's");
				}
			}
		}
		
		this.board = board;
	}
	
	//Advances the game board one step
	public void step(){
		
		//Make a deep copy of our board for next step
		int[][] succesors = new int[board.length][];
		for (int i = 0; i < board.length; i++) {
			succesors[i] = Arrays.copyOf(board[i], board[i].length);
		}
		
		//loop through each cell
		for(int i = 0; i < board.length; i++){
			for(int j = 0; j < board[i].length; j++){
				
				//count neighbors
				int neighbors = countNeighbors(i, j);
				
				//live cell
				if(board[i][j] == 1){
						
					//under pop
					if(neighbors < 2)
						succesors[i][j] = 0;
					
					//survival
					if(neighbors == 2 || neighbors == 3) 
						succesors[i][j] = 1;
					
					//over-crowding
					if(neighbors > 3)
						succesors[i][j] = 0;
				
				//Dead Cell
				}else{
					//reproduction
					if(neighbors == 3)
						succesors[i][j] = 1;
				}
				
			}
		}
		
		//update board state.
		board = succesors;
	}
	
	//Returns numbers of neighbors at board cell i, j.
	private int countNeighbors(int i, int j){
		int count = 0;
		boolean up, down, left, right;
		up = down = left = right = true;
		
		//check out of bounds indices  
		//left
		if(i == 0) 
			left = false;
		
		//right 
		if(i == board.length - 1) 
			right = false;
		
		//up 
		if(j == 0) 
			up = false;
		
		//down
		if(j == board[0].length - 1) 
			down = false;
		
		//Begin counting
		//up
		if(up && board[i][j-1] == 1)
			count++;
			
		//up-right
		if(up && right && board[i+1][j-1] == 1) 
			count++;
		
		//up-left
		if(up && left && board[i-1][j-1] == 1) 
			count++;
		
		//down
		if(down && board[i][j+1] == 1) 
			count++;
			 
		//down-right
		if(down && right && board[i+1][j+1] == 1) 
			count++;
		
		//down-left
		if(down && left && board[i-1][j+1] == 1) 
			count++;
		
		//left
		if(left && board[i-1][j] == 1) 
			count++;
		
		//right
		if(right && board[i+1][j] == 1) 
			count++; 
		
		return count;
	}
	
	//prints the board to stdout
	public void printBoard(){
		System.out.print("\n");	
		for(int i = 0; i < board.length; i++){
			for(int j = 0; j < board[i].length; j++){
				System.out.print(board[i][j] + " ");
			}
			System.out.print("\n");
		}
	}
	
	
	//Test driver
	public static void main(String[] argv){
		//input board
		int[][] input = new int[][]{
			{ 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 1, 1 },
			{ 1, 1, 0, 0, 1 },
			{ 0, 1, 0, 0, 0 },
			{ 1, 0, 0, 0, 1 }
		};
		
		Life test = new Life(input);
		
		test.printBoard();
		test.step();
		test.printBoard();
		
	}
}
