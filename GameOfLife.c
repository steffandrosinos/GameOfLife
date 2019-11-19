/* Game of Life in C */
#include <stdio.h>
#include <stdlib.h>

/* Functions declaration */
int getIntInput(void);
char * getField(int height, int width);
char * newGame(int width, int height, int steps, char *field);
char * oneGeneration(int width, int height, char *field);
int checkNeighbours(char *field, int width, int height, int y_index, int x_index);
char lifeOrDeath(int neighbours, char cell);
void printField(char *field, int height, int width);

/* Program start */
int main(void)
{
	int height = getIntInput(); /* Get rows */
	int width = getIntInput(); /* Get columns */
	int steps = getIntInput(); /* Get steps */

	/* Get initial configuration */
	char *field = getField(height, width);

	/* new game */
	char *finalField = newGame(width, height, steps, field);

	/* Print results */
	printField(finalField, height, width);
	return 0; /* End of program */
}

/* Function that gets an integer input */
int getIntInput(void)
{
	int value;
	scanf("%d", &value);
	return value;
}

/* Function that returns a 2d char array filled with inputted characters */
char * getField(int height, int width)
{
	/* Allocate memory of size height*width, is filled with characters so times by size of char */
	char *field = malloc(height*width*sizeof(char));
	/* Loop for height and width */
	for(int y=0; y<height; y++)
		for(int x=0; x<width; x++)
		{
			char input = getchar(); /* Get character from STDIN */
			while(input == '\n') /* getchar() also catches keyboard ENTER, so we need to deal with this */
				input = getchar();
			*(field + (y * width) + x) = input; /* Set position (y,x) in array = the input */
		}
	return field; /* Return the complete field */
}

/* Function that loops the generation process based on the user input */
char * newGame(int width, int height, int steps, char *field)
{
	for(int i=0; i<steps; i++)
		field = oneGeneration(width, height, field);
	return field; /* This will returned the finished field */
}

/* Function that advances the field by one generation */
char * oneGeneration(int width, int height, char *field)
{
	char *next_field = malloc(height*width*sizeof(char)); /* Need a temp array as I can't overwrite */
	for(int y=0; y<height; y++)
		for(int x=0; x<width; x++)
		{
			int neighbours = checkNeighbours(field, width, height, y, x); /* Check neighbours of current index */
			char cell = *(field + (y*width) + x); /* Value at current index */
			*(next_field + (y*width) + x) = lifeOrDeath(neighbours, cell); /* Determine if this cell dies or lives */
		}
	/* Freeing memory, getting rid of next_field as it's only temporary */
	for(int y=0; y<height; y++)
		for(int x=0; x<width; x++)
			*(field + (y*width) + x) = *(next_field + (y*width) + x); /* change field to next_field */
	free(next_field); /* Free memory */
	return field; /* Return the next generation */
}

/* Function that checks the value of neighbours at a given x,y index */
int checkNeighbours(char *field, int width, int height, int y_index, int x_index)
{
	int base_index = (y_index*width) + x_index; /* This gives us the position of x,y in our array */
	/* Temp values for all neighbours, some won't get set differently */
	char top_left = '!';
	char top_mid = '!';
	char top_right = '!';
	char mid_left = '!';
	char mid_right = '!';
	char bottom_left = '!';
	char bottom_mid = '!';
	char bottom_right = '!';

	/* Top neighbours */
	if((base_index - width) >= 0)
	{
		top_mid = *(field + base_index - width); /* top mid */
		if(x_index != 0)
			top_left = *(field + base_index - width - 1); /*top left*/
		if((x_index+1) != width)
			top_right = *(field + base_index - width + 1); /* top right */
	}

	/* Middle neighbours */
	if(x_index != 0)
		mid_left = *(field + base_index - 1); /* mid left */
	if((x_index+1) != width)
		mid_right = *(field + base_index + 1); /* mid right */

	/* Bottom neighbours */
	if((base_index)+width <= height*width)
	{
		bottom_mid = *(field + base_index + width); /* Bottom mid */
		if(x_index != 0)
			bottom_left = *(field + base_index + width -1); /* Bottom left */
		if((x_index+1) != width)
			bottom_right = *(field + base_index + width +1); /* Bottom right */
	}

	/* Check all these values, if they = 'X' then add to neighbours */
	int neighbours = 0;
	if(top_left == 'X')
		neighbours++;
	if(top_mid == 'X')
		neighbours++;
	if(top_right == 'X')
		neighbours++;
	if(mid_left == 'X')
		neighbours++;
	if(mid_right == 'X')
		neighbours++;
	if(bottom_left == 'X')
		neighbours++;
	if(bottom_mid == 'X')
		neighbours++;
	if(bottom_right == 'X')
		neighbours++;

	return neighbours; /* Return amount of neighbours */
}

/* Function that determines if a cell dies of lives or if a dead cell comes alive */
char lifeOrDeath(int neighbours, char cell)
{
	char new_cell;
	if(cell == 'X') /* All checks for cells that are alive */
	{
		if(neighbours < 2) /* Under-population */
			new_cell = '.'; /* Cell dies */
		if(neighbours == 2 || neighbours == 3)
			new_cell = 'X'; /* Cell lives */
		if(neighbours > 3) /* over-population */
			new_cell = '.'; /* Cell dies */
	}
	else /* All checks for dead cells */
	{
		if(neighbours == 3)
			new_cell = 'X'; /* Dead cell becomes a live cell */
		else
			new_cell = '.'; /* Stay dead */
	}
	return new_cell; /* Return new cell */
}

/* Function that prints a char array given its height and width */
void printField(char *field, int height, int width)
{
	for(int y=0; y<height; y++)
	{
		for (int x = 0; x < width; x++)
			printf("%c", *(field + (y * width) + x));
		printf("\n");
	}
}
