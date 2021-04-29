#include <stdio.h>
#include <stdlib.h>
#define IMAGE_SIZE 10

/*--------------------GLOBAL VARIABLES--------------------*/

/**
 * Parallel array, for each of the direction vectors
 * 
 * (0, -1)  - West
 * (-1, -1) - North West
 * (-1, 0)  - North
 * (-1, 1)  - North East
 * (0, 1)   - East
 * (1, 1)   - South East
 * (1, 0)   - South
 * (1, -1)  - South West
 **/
int xDir[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int yDir[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

/*------------------------FUNCTIONS------------------------*/

/**
 * This function prints the input array
 * 
 * int array[][] - array to be printed
 **/
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{
    printf("---------------------------------------\n");
    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++)
    {
        for (j = 0; j < IMAGE_SIZE; j++)
            printf("%02d, ", array[i][j]);
        printf("\n");
    }
    printf("---------------------------------------\n");
}

/**
 * 
 * A 'boolean' helper method that calculates if the 
 * neighbouring coordinate we want to check is in 
 * the array
 * 
 * int x - the neighbouring x coordinate
 * int y - the neighbouring y coordinate
 * 
 * Return 1 if x and y can be located in the grid,
 * else, return 0 
 */
int validCoor(int x, int y)
{
    return (x >= 0 && x < IMAGE_SIZE && y >= 0 && y < IMAGE_SIZE);
}

/**
 * A helper method that marks all the connected components of a label
 * If a non zero number in the input array is found, it will recursively 
 * mark all the neighbours of the component in the visited array. This will
 * tell us not to increment the count because its component was already 
 * accounted for
 * 
 * int image[][] - the input array
 * int i - the x coordinate we are checking
 * int j - the y coordinate we are checking
 * int visited[][] - the array keeping track of the coordinates that have
 *                   already been seen/ don't need to check
 */
void dfsCellCount(int image[IMAGE_SIZE][IMAGE_SIZE], int i, int j, int visited[IMAGE_SIZE][IMAGE_SIZE])
{
    if (!validCoor(i, j)) // return this is not a valid coordinate
        return;

    if (visited[i][j]) // return if we already checked this coordinates connectivity
        return;

    visited[i][j] = 1; // let this coordinate be marked as seen

    int aroundX; // neighbouring X
    int aroundY; // neighbouring Y

    // recursively check the surrounding coordinate in all directions
    int d;
    for (d = 0; d < 8; ++d)
    {
        // since the direction arrays are parallel, this is possible
        aroundX = i + xDir[d];
        aroundY = j + yDir[d];

        // if the neighbouring coordinate is valid and that coordinated is labelled in the input array
        // but not the visited array, mark it in the label array and check that point's neighbours
        if (validCoor(aroundX, aroundY) && (image[aroundX][aroundY] && !visited[aroundX][aroundY]))
            dfsCellCount(image, aroundX, aroundY, visited);
    }
}

/**
 * Returns the number of distinct cells 
 * in the given matrix
 * 
 * int image[][] - the matrix
 * 
 * Assuming, image[][] is already labelled
 **/
int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    int count = 0; // the number of distinct cells

    // an array that will hold non zero vales, to ensure we don't increment our count
    // on an already visited coordinate
    int visited[IMAGE_SIZE][IMAGE_SIZE] = {0};

    int i, j;
    for (i = 0; i < IMAGE_SIZE; ++i)
    {
        for (j = 0; j < IMAGE_SIZE; ++j)
        {
            if (image[i][j] && !visited[i][j])
            {
                dfsCellCount(image, i, j, visited);
                ++count;
            }
        }
    }
    return count;
}

/**
 * A recursive helper method that checks the current coordinate's
 * neighbours, and than decides the connected component value 
 * based off the neighbours
 * 
 * int x - x coordinate
 * int y - y coordinate
 * int componentLabel - current label
 * int image[][] - input array
 * int connectedR[][] - image equivalent but with labels
 */
void dfs(int x, int y, int componentLabel, int image[IMAGE_SIZE][IMAGE_SIZE], int connected[IMAGE_SIZE][IMAGE_SIZE])
{
    int aroundX, aroundY;
    
    /**
     *  Checks if the surround coordinates of the current index 
     *  is out of bounds. For example, will not compute the North,
     *  West, North West, and North East coordinates of the first 
     *  index of the array because they do not exist
     */
    if (!validCoor(x, y))
        return;

    // mark the current index in the copy array
    connected[x][y] = componentLabel;

    // recursively check the surrounding coordinates
    int d;
    for (d = 0; d < 8; ++d)
    {
        aroundX = x + xDir[d];
        aroundY = y + yDir[d];

        // if the respective neighbour in the original array is labelled
        // the same neighbour is not labelled in the copy array
        if (image[aroundX][aroundY] && !connected[aroundX][aroundY])
            dfs(aroundX, aroundY, componentLabel, image, connected);
    }
}

/**
 * This function colors each cell with a unique color
 * (i.e., unique number).
 * 
 * int image[][] - input matrix
 **/
int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    int connectedR[IMAGE_SIZE][IMAGE_SIZE] = {0};

    int componentLabel = 0; // component labelling

    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++)
    {
        for (j = 0; j < IMAGE_SIZE; j++)
        {
            /**
	         * Check ever value in the original array,
	         * if the original array has a non-zero, and the copy array
	         * at the same position has a 0, turn that position in 
	         * the array to the value in the original array
	         */
            if (image[i][j] && !connectedR[i][j])
                dfs(i, j, ++componentLabel, image, connectedR);
        }
    }

    // make the original array, into the labelled array
    int m, n;
    for (m = 0; m < IMAGE_SIZE; m++)
    {
        for (n = 0; n < IMAGE_SIZE; n++)
            image[m][n] = connectedR[m][n];
    }

    return 0;
}

// TESTING  //
#ifndef __testing
int main()
{

    // DO not change anything in main(), it will confuse the
    // auto-checker.
    puts("\nTest 1:");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                           {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    puts("---------------------------------------\nInitial Grid: ");
    printImgArray(cellImg);
    colorRecursively(cellImg);
    puts("Connected Components: ");
    printImgArray(cellImg);
    count = cellCount(cellImg);
    printf("Total number of cells in the image: %d\n", count);

    puts("\nTest 2:");
    int cellImg_[IMAGE_SIZE][IMAGE_SIZE] = {{0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
                                            {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
                                            {1, 0, 0, 1, 1, 0, 1, 1, 0, 1},
                                            {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                            {1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
                                            {0, 0, 0, 0, 1, 0, 0, 1, 1, 0},
                                            {0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
                                            {0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
                                            {0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
                                            {0, 1, 1, 0, 0, 0, 1, 1, 1, 1}};
    puts("---------------------------------------\nInitial Grid: ");
    printImgArray(cellImg_);
    colorRecursively(cellImg_);
    puts("Connected Components: ");
    printImgArray(cellImg_);
    count = cellCount(cellImg_);
    printf("Total number of cells in the image: %d\n", count);

    puts("\nTest 3:");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE] = {{0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		                                     {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		                                     {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		                                     {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		                                     {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		                                     {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		                                     {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		                                     {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		                                     {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
		                                     {1, 1, 1, 1, 1, 0, 0, 0, 0, 0}};
    puts("---------------------------------------\nInitial Grid: ");
    printImgArray(cellImg__);
    colorRecursively(cellImg__);
    puts("Connected Components: ");
    printImgArray(cellImg__);
    count = cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n\n", count);
    return 0;
}
#endif