/* The Game of Life: Luke Hooker */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines max dimensions of the game board according to the spec */

#define MAX_WIDTH 80
#define MAX_HEIGHT 52

/* Game Board Structure */

struct
{
    char cell[MAX_WIDTH][MAX_HEIGHT + 2];       /* 2D array created to store the game-board */
    int width, height, round, max_rounds, no_cells;        /* Variables to define the width, height, max rounds and no. cells in the file. */
} typedef game;        /* Structure defined as "game" */

/* Function declarations */

game prep_game(game game_board);
game read_game(char *cells, game game_board);
game run_game(game game_board);
game print_game(game game_board, int flag);
static int read_line (FILE *fp, char *line, int max_length);

int main(int argc, char *argv[])
{
    game game_board;        /* Creates set of data called "game_board" following the game structure type */
    
    sscanf(argv[2], "%i", &game_board.width);    /* Sets second command line argument to the game-board width variable */
    sscanf(argv[3], "%i", &game_board.height);        /* Sets third command line argument to the game-board height variable */
    sscanf(argv[4], "%i", &game_board.max_rounds);       /* Sets fourth command line argument to the game-board max_rounds variable */
    
    game_board = prep_game(game_board);     /* Sends game_board into the function prep_game, and sends the result into game_board (edits game_board) */
    game_board = read_game(argv[1], game_board);        /* Runs function to read in the game file. Sends first command line argument into it */
    game_board = run_game(game_board);      /* Runs the game, carrying out the set number of time steps, and prints the game board for each generation, starting from 0 (initial set-up) */
    return 0;
}

/* Populates board with spaces and borders to match size defined at run-time */

game prep_game (game game_board)
{
    int i, j;
    
    for(j = 0; j < (game_board.height +2); j++)     /* Fills array full of spaces */
    {
        for(i = 0; i < (game_board.width+2); i++)
        {
            game_board.cell[i][j] = ' ';
        }
    }
    
    game_board.cell[0][0] = game_board.cell[game_board.width + 1][0] = '*';
    game_board.cell[0][game_board.height + 1] = game_board.cell[game_board.width + 1][game_board.height + 1] = '*';     /* Puts '*' in the four corners */
    
    for(i = 1; i < (game_board.width + 1); i++)     /* Creates the border along the x-axis */
    {
        game_board.cell[i][0] = '-';
        game_board.cell[i][game_board.height + 1] = '-';
    }
    
    for(i = 1; i < (game_board.height + 1); i++)    /* Creates the border along the y-axis */
    {
        game_board.cell[0][i] = '|';
        game_board.cell[game_board.width + 1][i] = '|';
    }
    
    return game_board;      /* Returns game_board back to main (saves changes to game_board) */
}

/* Reads in game file at run-time and places the cells (X) in the game board */

game read_game (char *cells, game game_board)
{
    FILE *fp;       /* Creates a file pointer so program can track the file being accessed */
    fp = fopen(cells, "r");     /* Allows the program to read the file sent into the function */
    
    if(fp == NULL)
    {
        fprintf(stderr,"Error opening game file\n");        /* Returns error message if game file invalid or empty */
        exit(EXIT_FAILURE);     /* Exits progam showing failure case */
    }
    
    char temp_no_cells[5], temp[7];
    read_line(fp, temp_no_cells, 4);    /* Reads first line of file, stating the number of cells */
    sscanf(temp_no_cells, "%i", &game_board.no_cells);      /* Converts the character to an integer data type */
    int i, x, y;
    
    for(i = 0; i < game_board.no_cells; i++)    /* For each cell... */
    {
        read_line(fp, temp, 6);     /* Read in co-ordinates to temp */
        sscanf(temp, "%i %i", &y,&x);       /* Convert temp characters to integers y and x */
        x++, y++;       /* Account for border */
        game_board.cell[x][y] = 'X';        /* Place X in co-ordinates given by x and y */
    }
    
    fclose(fp);     /* Closes stream (access to file) and clears the buffer */
    return game_board;
}

/* Runs algorithm to determine what cells live, die, or are born for each time step */

game run_game (game game_board)
{
    int i, x, y, neighbours, flag = 0;
    char new_cell[MAX_WIDTH][MAX_HEIGHT];       /* Creates a 2D array to store any changes caused in each time-step */
    game_board = print_game(game_board, flag);  /* Prints initial game board with cells given from the file */
    
    for(y = 1; y < (game_board.height + 1); y++)        /* Fills the new_cell array with the initial game_board */
    {
        for(x = 1; x < (game_board.width + 1); x++)
        {
            new_cell[x][y] = game_board.cell[x][y];
        }
    }
    
    for(i = 0; i < game_board.max_rounds; i++)  /* For each time-step... */
    {
        for(y = 1; y < (game_board.height + 1); y++)
        {
            for(x = 1, neighbours = 0; x < (game_board.width + 1); x++)     /* For each cell... */
            {
                neighbours = 0;     /* Sets neighbours count to zero */
                if( y == 1)      /* Top Row */
                {
                    if(x == 1)   /* Top Left Corner */
                    {
                        if(game_board.cell[x][y+1] == 'X')      /* Increments neighbours count if there is an adjcacent live cell */
                            neighbours++;
                        if(game_board.cell[x+1][y] == 'X')
                            neighbours++;
                        if(game_board.cell[x+1][y+1] == 'X')
                            neighbours++;
                    }
                    else if(x != (game_board.width + 1))     /* Top Edge */
                        {
                            if(game_board.cell[x-1][y] == 'X')
                                neighbours++;
                            if(game_board.cell[x-1][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y] == 'X')
                                neighbours++;
                        }
                    else        /* Top Right Corner */
                    {
                        if(game_board.cell[x-1][y] == 'X')
                            neighbours++;
                        if(game_board.cell[x-1][y+1] == 'X')
                            neighbours++;
                        if(game_board.cell[x][y+1] == 'X')
                            neighbours++;
                    }
                }
                else if(y != (game_board.height + 1))      /* Middle Rows */
                    {
                        if(x == 1)      /* Left Edge */
                        {
                            if(game_board.cell[x][y-1] == 'X')
                               neighbours++;
                            if(game_board.cell[x+1][y-1] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x][y+1] == 'X')
                                neighbours++;
                        }
                        else if(x != (game_board.width + 1))       /* Middle */
                        {
                            if(game_board.cell[x-1][y-1] == 'X')
                                neighbours++;
                            if(game_board.cell[x][y-1] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y-1] == 'X')
                                neighbours++;
                            if(game_board.cell[x-1][y] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y] == 'X')
                                neighbours++;
                            if(game_board.cell[x-1][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x+1][y+1] == 'X')
                                neighbours++;
                        }
                        else        /* Right Edge */
                        {
                            if(game_board.cell[x][y-1] == 'X')
                                neighbours++;
                            if(game_board.cell[x-1][y-1] == 'X')
                                neighbours++;
                            if(game_board.cell[x-1][y] == 'X')
                                neighbours++;
                            if(game_board.cell[x-1][y+1] == 'X')
                                neighbours++;
                            if(game_board.cell[x][y+1] == 'X')
                                neighbours++;
                        }
                    }
                else        /* Bottom Row */
                {
                    if(x == 1)      /* Bottom Left Corner */
                    {
                        if(game_board.cell[x][y-1] == 'X')
                            neighbours++;
                        if(game_board.cell[x+1][y-1] == 'X')
                            neighbours++;
                        if(game_board.cell[x+1][y] == 'X')
                            neighbours++;
                    }
                    else if(x != (game_board.width + 1))   /* Bottom Edge */
                    {
                        if(game_board.cell[x-1][y] == 'X')
                            neighbours++;
                        if(game_board.cell[x-1][y-1] == 'X')
                            neighbours++;
                        if(game_board.cell[x][y-1] == 'X')
                            neighbours++;
                        if(game_board.cell[x+1][y-1] == 'X')
                            neighbours++;
                        if(game_board.cell[x+1][y] == 'X')
                            neighbours++;
                    }
                    else        /* Bottom Right Corner */
                    {
                        if(game_board.cell[x-1][y] == 'X')
                            neighbours++;
                        if(game_board.cell[x-1][y-1] == 'X')
                            neighbours++;
                        if(game_board.cell[x][y-1] == 'X')
                            neighbours++;
                    }
                }
            
                if(neighbours < 2)      /* If there are less than two live neighbours, the cell dies */
                {
                    new_cell[x][y] = ' ';   /* Updates any board changes to the new_cell array so it doesn't cause a 'domino effect' with the original game board for the current time-step */
                }
                if(neighbours == 3)  /* If there are two or three live neigbours, a cell stays alive or is born */
                {
                    new_cell[x][y] = 'X';       /* Live cell born/kept for current cell being tested */
                }
                if(neighbours > 3)     /* If there are more then 3 live neighbours, the cell dies */
                {
                    new_cell[x][y] = ' ';
                }
            }
        }
        
        for(y = 1; y < (game_board.height + 1); y++)        /* Updates the game board with any changes made during the time-step by copying the new cell array characters into it */
        {
            for(x = 1; x < (game_board.width + 1); x++)
            {
                game_board.cell[x][y] = new_cell[x][y];
            }
        }
        
        if(i == (game_board.max_rounds - 1))        /* Sets flag to 1 if the final time-step has been completed */
        {
            flag = 1;
        }
        
        game_board = print_game(game_board, flag);      /* Sends the current game board to the print_game function to be printed. Sends the flag variable so the function knows exactly what to print */
    }
    
    return game_board;
}

/* Prints the entire game board to stdout and changes the output, depending on the current time-step */
        
game print_game(game game_board, int flag)
{
    int i, j;
    
    /* Print Game Board */
    for(j = 0; j < (game_board.height +2); j++)     /* For each row of the array... */
    {
        for(i = 0; i < (game_board.width+2); i++)   /* For each column of the array... */
        {
            printf("%c", game_board.cell[i][j]);    /* Print the character */
        }
        puts("");     /* Creates a space between each row */
    }
    
    if(flag == 0)       /* If there are more time-steps to go... */
    {
        printf("\n\n");     /* Print two blank lines after the game board is printed */
    }
    else if(flag == 1)      /* If the last time-step has been completed... */
    {
        printf("\nFinished\n");     /* Print a blank line and tell user the game has finished */
    }
    
    return game_board;
}

/* Read a line of characters from the file pointer "fp", copying the characters into the "line" string, up to a max of "max_length" characters */

static int read_line (FILE *fp, char *line, int max_length)
{
    int i;
    char ch;
    
    /* Creates index-to-string character and sets it to zero */
    i = 0;
    
    /* Read to the end of line, filling in characters in string up to its
     maximum length, and ignoring the rest */
    for(;;)
    {
        /* Read next character */
        ch = fgetc(fp);
        
        /* Check for end of file error */
        if ( ch == EOF )
            return -1;
        
        /* Check for end of line */
        if ( ch == '\n' )
        {
            /* Terminate string and return */
            line[i] = '\0';
            return 0;       /* Return 0 if successful */
        }
        
        /* Fill character in string if it is not already full*/
        if ( i < max_length )
            line[i++] = ch;
    }
    
    /* The program should not reach here */
    return -1;
}
