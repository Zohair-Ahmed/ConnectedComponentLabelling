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

/**
 * Parallel array, for each of the direction vectors
 * 
 * (-1, 1) - North East ; (0, 1) - East ; (1, 1) - South East
 * (1, 0) - South ; (1, -1) - South West; (0, -1) - West
 * (-1, -1) - North West - (-1, 0) - North
 * 
 */
int xDir[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int yDir[8] = {1, 1, 1, 0, -1, -1, -1, 0};

/**
 * This array is currently all 0's.
 * When colour is called, the 0's will change into the respecitve label,
 * depending on the number of connected components. Then the original array,
 * will copy this array.
 */
int connected[IMAGE_SIZE][IMAGE_SIZE] = {0};

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
    // insert your code for task1.2 here
    // you may want to change the return value.
    return 0;
}

void connect(int x, int y, int componentLabel, int image[IMAGE_SIZE][IMAGE_SIZE])
{

    /**
     *  Checks if the surround coordinates of the current index 
     *  is out of bounds. For example, will not compute the North,
     *  West, North West, and North East coordinates of the first 
     *  index of the array because they do not exist
     */
    if (x < 0 || x == IMAGE_SIZE)
        return;
    if (y < 0 || y == IMAGE_SIZE)
        return;

    // mark the current index in the copy array
    connected[x][y] = componentLabel;

    // recursively check the surrounding coordinates
    int d;
    for (d = 0; d < 8; ++d)
    {

        // since the direction arrays are parallel, this is possible
        int aroundX = x + xDir[d];
        int aroundY = y + yDir[d];

        // if the respective neighbour in the original array is labelled
        // the same neighbour is not labelled in the copy array
        if (image[aroundX][aroundY] && !connected[aroundX][aroundY])
            connect(aroundX, aroundY, componentLabel, image);
    }
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
    int componentLabel = 0; // component labelling

    // insert your code for task 1.1 here
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
            if (image[i][j] && !connected[i][j])
                connect(i, j, ++componentLabel, image);
        }
    }

    // make the original array, into the labelled array
    int m, n;
    for (m = 0; m < IMAGE_SIZE; m++)
    {
        for (n = 0; n < IMAGE_SIZE; n++)
            image[m][n] = connected[m][n];
    }
}

/********************************************************************************/
//the function and all the helper functions (if any) should use pointer notation,
// instead of array index notation []. It is okey to use [] only when declaring extra arrays
void colorPtr(int *image)
{
    // insert your code for task 2.1 here
}

//the function and all the helper functions (if any) should use pointer notation,
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

    return 0;
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
