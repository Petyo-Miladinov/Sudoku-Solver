#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<stdbool.h> 

#define EMPTY 0 

char** sdm_to_sudoku(char line_sudoku[81]) {
    char** grid = (char**)malloc(9*sizeof(char*));
    int k = 0; 
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j <= 9; j++) {
            grid[i][j] = line_sudoku[k]; 
            k++; 
        }
    }
    return grid; 
}

int* old_ss_to_sudoku(int grid[9][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(grid[i][j] == 'X') 
                grid[i][j] = '0'; 
        }
    }
    int* ptr = &grid[0][0]; 
    return ptr; 
}

int* ss_to_sudoku(char ss_sudoku[11][11]) {
    int grid[9][9], temp[11][11];  
    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            temp[i][j] = ss_sudoku[i][j]; 
        }
    } 

    for(int i = 0; i < 11; i++) {
        for(int j = 0; j < 11; j++) {
            if(temp[i][j] == '.') 
                temp[i][j] = '0'; 
            if(temp[i][j] == '|') {
                temp[i][j] = temp[i][j+1];
                j++; 
            }
        }
    } 

    int row = 11, col = 11; 
    for(int i = 0; i < row; i++) { 
        if(temp[i][0] == '-') {
            for(int k = i; i < row - 1; k++) {
                for(int j = 0; j < col; j++) {
                    temp[k][j] = temp[k + 1][j];
                    k++; 
                }
            } 
            i--; 
            row--; 
        }
    } 

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            grid[i][j] = temp[i][j]; 
        }
    }
    int* ptr = &grid[0][0]; 
    return ptr; 
}

bool find_empty_location(int grid[9][9], int row, int col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == EMPTY)
                return true;
        }
    }
    return false;
}
bool is_safe(int grid[9][9], int row, int col, int num);
 
bool sudoku_solver(int grid[9][9], int row, int col) {
 
    if (!find_empty_location(grid, row, col))
        return true; 
 
    for (int num = 1; num <= 9; num++) {
         
        if (is_safe(grid, row, col, num)) {
            
            grid[row][col] = num;
 
            if (sudoku_solver(grid, row, col))
                return true;
 
            grid[row][col] = EMPTY;
        }
    }
   
    return false;
}
 


bool used_in_row(int grid[9][9], int row, int num) {
    for (int col = 0; col < 9; col++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

bool used_in_col(int grid[9][9], int col, int num) {
    for (int row = 0; row < 9; row++) {
        if (grid[row][col] == num)
            return true;
    }
    return false;
}

// small sudoku --> 3x3 box 
bool used_in_small_sudoku(int grid[9][9], int start_row_in_small_sudoku, int start_col_in_small_sudoku, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + start_row_in_small_sudoku][col + start_col_in_small_sudoku] == num)
                return true;
    return false;
}

bool is_safe(int grid[9][9], int row, int col, int num) {
    
    return !used_in_row(grid, row, num)
           && !used_in_col(grid, col, num)
           && !used_in_small_sudoku(grid, row - row % 3, col - col % 3, num)
           && grid[row][col] == EMPTY; 
}

void print_sudoku(int grid[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}

int main() {


    // FILE *fp; 
    // char* file_name;  
    // char buffer[256]; 
    // printf("Enter file path: "); 
    // scanf("%s", file_name); 
    // fp = fopen(file_name, "r"); 


    // fclose(fp); 

    
    FILE *fp; 
    char file_name[20];  
    char buffer[256]; 
    char key[5]; 
    printf("Enter file path: "); 
    scanf("%s", file_name); 
    printf("\nEnter the type of your file /.sdm/.ss/: "); 
    scanf("%s", key); 
    fp = fopen(file_name, "rb");  
    fread(buffer, strlen(buffer)*sizeof(char), 1, fp); 

    if(strcmp(key, ".sdm")) {
        sdm_to_sudoku(buffer); 
    }
    

    return 0; 
}