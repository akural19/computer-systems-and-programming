#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct container {        // defining a struct to return multiple values from a function 

	int countDeath; 
	int countBorn; 
	char **lastState; 

} container; 


// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
char **read_from_file(const char *filename) {

	FILE* file = fopen(filename, "r");        // to open the file to read the input 
	
	char *pointer;                       
	char str[100]; 
	
	char** nums = malloc(sizeof(char*)*3);    // dynamically allocating memory for number of interation, number of row, and number of column lines 

	for (int ii = 0; ii < 3; ii++) {          // looping to obtain the lines for number of iteration, number of row, and number of column

		pointer = fgets(str, 100, file);

		if (pointer != NULL) {
			nums[ii] = strdup(pointer);  
		}
	}

	char **matArr = malloc(sizeof(char *)*(atoi(nums[1]) + 3));  // dynamically allocating memory for 2 dimensional array consisting of number of iteration, number of row and number of column info 
	int index = 3; 						     // and the game grid 

	while (pointer != NULL) {
		
		pointer = fgets(str, 100, file); 

		if (pointer != NULL) {
			matArr[index] = strdup(pointer);
			index++;
		} 
	}

	for (int ii = 0; ii < 3; ii++) {
		
		matArr[ii] = nums[ii];
	}
	
	fclose(file);
	return matArr;    
}

// given a game step return the next step applying game rules
container next_state(char **state) {

	int countDeath = 0;          // to accumulate number of death cell during transition from current state to the next state 
	int countBorn = 0;	     // to accumulate number of born cells during transition from current state to the next state 

	int numRow = atoi(state[1]);        
	int numCol = atoi(state[2]);

	char **lastState = malloc(sizeof(char*)*(numRow + 3));      // dynamically allocating new 2 dimensional array for the next state 
       	
	for (int ii = 0; ii < 3; ii++) {

		lastState[ii] = strdup(state[ii]);
	}

	state += 3;
       	lastState += 3; 	

	for (int ii = 0; ii < numRow; ii++) {      		    // iterating through the current state game grid's row 

		lastState[ii] = malloc(sizeof(char)*(numCol));      // dynamically allocating each row of next state grid 
		lastState[ii][numCol] = '\0';
	
		for (int jj = 0; jj < numCol; jj++) {               // iterating thorugh the current state game grid's column 
			
			int liveNeig = 0; 			    // accumulating number of neigbours for each cell of the grid 

			for (int kk = -1; kk < 2; kk++) {           // to check for the neighbours of the cell 

				for (int ll = -1; ll < 2; ll++) {
					
					if (kk == 0 && ll == 0) {
						continue; 
					}

					int tempRow = ii + kk; 
					int tempCol = jj + ll; 

					if (tempCol >= 0 && tempCol < numCol && tempRow >= 0 && tempRow < numRow) {   // to check the boundary conditions of the game grid 
						
						if (state[tempRow][tempCol] == 'X') {				
						
							liveNeig++;	       
						}
					}
				}
			}

			if (state[ii][jj] == '-') {        			 // if a cell is dead 
						
				if (liveNeig == 3) {     			 // and the cell has 3 living neighbours 
					lastState[ii][jj] = 'X';                 // then, the cell comes back to life 
					countBorn++;                        
				}
				else {			    			// if the cell has not 3 living neighbours 
					lastState[ii][jj] = '-';                // then, the cell remains dead 
				}
			}
			else if (state[ii][jj] == 'X') {   			// if the cell is alive 
		       		
				if (liveNeig < 2 || liveNeig > 3) {             // but, number of living neighbours are bigger than 3 or small than 2 

					lastState[ii][jj] = '-'; 		// then, the cell dies 
					countDeath++;
				}
				else {						// if the number of living neighbours are 2 or 3 
					lastState[ii][jj] = 'X'; 		// then, the cell reamins alive
				}
			}	
		}	
	} 

	state -= 3; 
	free(state);                               // to free the dynamically allocated memory for the current state since new current state is the previous state 
	lastState -= 3; 

	container contain; 
	contain.countDeath = countDeath; 
	contain.countBorn = countBorn; 
	contain.lastState = lastState;

	return contain; 
}

// bonus task
// return true if the given pattern is an oscillator
bool is_oscillator(char **pattern, int max_steps)
{

}

// print the game state
// after each step you can call this function, add some delay and then clear screen to create a simple game simulation in terminal
void print_state(char **state, int rows, int cols)
{
    int i, j;
    printf("\nNext State:\n");
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%c", state[i][j]);
        }
        printf("\n");
    }
    sleep(0.001);             // suspends execution for given input of seconds 
    system("clear");	      // clears the console 
}

int main(int argc, char **argv) {
	
	char **state = read_from_file(argv[1]);
	
	int numIteration = atoi(state[0]);
	int numRow = atoi(state[1]);
	int numCol = atoi(state[2]);
	
	state += 3; 
	print_state(state, numRow, numCol);
	int counter = 0; 
	
	while (counter < numIteration) {       // executing the number of states given as input 

		state -= 3; 
		container contain = next_state(state); 
		state = contain.lastState;
		counter++;
		
		state += 3;
		print_state(state, numRow, numCol);	

		char filename[40]; 
		sprintf(filename, "%sout_iteration_%d.txt", argv[2], counter);

		FILE *file = fopen(filename, "w");         // opening output files to write the count of death, count of born between transition of states and the current state of the game grid  
			
		fprintf(file, "%d\n", contain.countDeath); 
		fprintf(file, "%d\n", contain.countBorn);
		
		for (int ii = 0; ii < numRow; ii++) {

			fprintf(file, "%s\n", state[ii]);
		}
	       	fclose(file);      // to closing the file 
	}
	return 0;
}               
