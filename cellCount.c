/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name: Zohair Ahmed
Student Number: 215867633
Course Section: N
eecs user id: zohair99
*/

#include <stdio.h>
#include <stdlib.h>
#define IMAGE_SIZE 10

/*----------GLOBAL VARIABLES----------*/

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
 * 
 */
int xDir[8] = { 0, -1, -1, -1, 0, 1, 1,  1};
int yDir[8] = {-1, -1,  0,  1, 1, 1, 0, -1};

/**
 * This array is the equivalent to the input array but with connected 
 * components. This array is currently all 0's.
 * When color function is called, the 0's will change into the respecitve 
 * label, depending on the number of connected components. Then the 
 * original array, will copy this array.
 * 
 * This is global because colorRecursively and its helper method share this array
 */
int connectedR[IMAGE_SIZE][IMAGE_SIZE] = {0};

/**
 * The label that holds the number of connected components
 */
//int componentLabel;

/*--------------FUNCTIONS--------------*/

/*--DECLARATIONS--*/
void connect(int x, int y, int componentLabel, int image[IMAGE_SIZE][IMAGE_SIZE]);

// this function prints the array
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{

    printf("------ Image Contents -------\n");
    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++)
    {
        for (j = 0; j < IMAGE_SIZE; j++)
            printf("%02d, ", array[i][j]);
        printf("\n");
    }
    printf("-----------------------------\n");
}

/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 *
 * feel free to add auxiliary data structures and helper functions
 **/
int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    // insert your code for task 1.2 here
    // you may want to change the return value.
    return 0;
}

/**
 * This function colors each blood cell with a unique color
 * (i.e. unique number)
 * Hint: scan the array element by element, and explore each element as much as possible, 
 * when come to an already labelled one, relabell the array to form larger cell
 * 
 * feel free to add auxiliary data structures and helper functions
 **/
void color(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    // insert your code for task 1.1 here

    /**
     * This is an array equivalent to the input image
     * but will have the label connected components
     */
    int connected[IMAGE_SIZE][IMAGE_SIZE] = {0};

    int componentLabel = 0; // component labelling

    /*******FIRST PASS**********/

    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++)
    {
        for (j = 0; j < IMAGE_SIZE; j++)
        {
            if (image[i][j] && !connected[i][j])
            {
                /*boolean statement to check if surrounding 
                coordinates have already been labelled*/
                int notSurrounded = 0;

                /*check every direction surrounding to current coordinate*/
                int d;
                for (d = 0; d < 8; ++d)
                {
                    // since the direction arrays are parallel, this is possible
                    int aroundX = i + xDir[d];
                    int aroundY = j + yDir[d];

                    // if the surrounding coordinate is out of bounds, go to next
                    // surrounding coordinate
                    if (aroundX < 0 || aroundX > IMAGE_SIZE - 1)
                        continue;
                    if (aroundY < 0 || aroundY > IMAGE_SIZE - 1)
                        continue;

                    // if this is coordinate is in the grid and has a non zero value
                    // this means this is a labelled component
                    notSurrounded = notSurrounded || connected[aroundX][aroundY];

                    // if the respective neighbour in the labelled array is
                    // already labelled, let them share the same label
                    // else if all the neighbours are 0 and the equivalent coordinate
                    // is labelled, let this component in the labelled array signify
                    // a new connected component
                    if (connected[aroundX][aroundY])
                    {
                        connected[i][j] = connected[aroundX][aroundY];
                        d = 7; // get out of loop
                    }
                    else if (notSurrounded == 0 && d == 6)
                        connected[i][j] = ++componentLabel;
                }
            }
        }
    }

    /*******SECOND PASS*********
     * A second pass is done ensure none of the connected components were missed
     * Since the input array is read from top right to bottom left, there could
     * be connected components that do not seem connected in the beginning, but connect
     * later on in the array
    */
    int y, z;
    for (y = IMAGE_SIZE - 1; y >= 0; y--)
    {
        for (z = 0; z < IMAGE_SIZE; z++)
        {
            // if this is a non zero component
            if (connected[y][z])
            {
                // check all surrounding neighbours
                int d;
                for (d = 0; d < 8; ++d)
                {
                    int aroundX = y + xDir[d];
                    int aroundY = z + yDir[d];

                    if (aroundX < 0 || aroundX > IMAGE_SIZE - 1)
                        continue;
                    if (aroundY < 0 || aroundY > IMAGE_SIZE - 1)
                        continue;

                    // if neighbours are different, change the neighbours to be the same
                    if (connected[aroundX][aroundY] && (connected[y][z] != connected[aroundX][aroundY]))
                        connected[aroundX][aroundY] = connected[y][z];
                }
            }
        }
    }

    // make the original array, into the labelled array
    int m, p;
    for (m = 0; m < IMAGE_SIZE; m++)
    {
        for (p = 0; p < IMAGE_SIZE; p++)
            image[m][p] = connected[m][p];
    }
}

/********************************************************************************/
// the function and all the helper functions (if any) should use pointer notation,
// instead of array index notation []. It is okey to use [] only when declaring extra arrays
void colorPtr(int *image)
{
    // insert your code for task 2.1 here
}

// the function and all the helper functions (if any) should use pointer notation,
// instead of array index notation []. It is okey to use [] only when declaring extra arrays
int cellCountPtr(int *image)
{
    // insert your code for task 2.2 here
    return 0;
}

/********************************************************************************/

/**
 * This function colors each cell with a unique color
 * (i.e., unique number).
 **/
int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE])
{
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
                connect(i, j, ++componentLabel, image);
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

/**
 * A recursive helper method that checks the current coordinate's
 * neighbours, and than decides the connected component value 
 * based off the neighbours
 */
void connect(int x, int y, int componentLabel, int image[IMAGE_SIZE][IMAGE_SIZE])
{

    /**
     *  Checks if the surround coordinates of the current index 
     *  is out of bounds. For example, will not compute the North,
     *  West, North West, and North East coordinates of the first 
     *  index of the array because they do not exist
     */
    if (x < 0 || x > IMAGE_SIZE - 1)
        return;
    if (y < 0 || y > IMAGE_SIZE - 1)
        return;

    // mark the current index in the copy array
    connectedR[x][y] = componentLabel;

    // recursively check the surrounding coordinates
    int d;
    for (d = 0; d < 8; ++d)
    {

        // since the direction arrays are parallel, this is possible
        int aroundX = x + xDir[d];
        int aroundY = y + yDir[d];

        // if the respective neighbour in the original array is labelled
        // the same neighbour is not labelled in the copy array
        if (image[aroundX][aroundY] && !connectedR[aroundX][aroundY])
            connect(aroundX, aroundY, componentLabel, image);
    }
}

#ifndef __testing
int main()
{

    // DO not change anything in main(), it will confuse the
    // auto-checker.
    puts("testing the code with color() function");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE] = {{0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
                                           {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
                                           {1, 0, 0, 1, 1, 0, 1, 1, 0, 1},
                                           {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                           {1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
                                           {0, 0, 0, 0, 1, 0, 0, 1, 1, 0},
                                           {0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
                                           {0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
                                           {0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
                                           {0, 1, 1, 0, 0, 0, 1, 1, 1, 1}};

    printImgArray(cellImg);
    color(cellImg);
    printImgArray(cellImg);
    count = cellCount(cellImg);
    printf("Total number of cells in the image: %d\n", count);

    puts("Testing the code with colorPtr");
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

    int *ptr = cellImg_;
    printImgArray(ptr);
    colorPtr(ptr);
    printImgArray(ptr);
    count = cellCountPtr(ptr);
    printf("Total number of cells in the image: %d\n", count);

    puts("Testing the code with colorRecursively");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE] = {{0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
                                             {1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
                                             {1, 0, 0, 1, 1, 0, 1, 1, 0, 1},
                                             {1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                             {1, 0, 0, 1, 1, 1, 0, 0, 1, 0},
                                             {0, 0, 0, 0, 1, 0, 0, 1, 1, 0},
                                             {0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
                                             {0, 0, 1, 1, 0, 0, 1, 0, 0, 0},
                                             {0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
                                             {0, 1, 1, 0, 0, 0, 1, 1, 1, 1}};
    printImgArray(cellImg__);
    colorRecursively(cellImg__);
    printImgArray(cellImg__);
    count = cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n", count);
    return 0;
}
#endif
