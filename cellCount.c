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

// TASK 1.2  //
/**
 * NON-POINTER VERSION
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
 * NON-POINTER VERSION
 * 
 * A helper method that marks all the connected components of a label
 * If a non zero number in the input array is found, it will recursively 
 * mark all the neighbours of the component in the visited array. This will
 * tell us not to increment the count because its component was already 
 * accounted for
 * 
 * int image[][] - the input array
 * int i - the x coordinate we are checking
 * int y - the y coordiante we are checking
 * int visited[][] - the array keeping track of the coordinates that have
 *                   already been seen/ don't need to check
 */
void markNeighbours(int image[IMAGE_SIZE][IMAGE_SIZE], int i, int j, int visited[IMAGE_SIZE][IMAGE_SIZE])
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
            markNeighbours(image, aroundX, aroundY, visited);
    }
}

/**
 * NON-POINTER VERSION
 * 
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
                markNeighbours(image, i, j, visited);
                ++count;
            }
        }
    }
    return count;
}

// TASK 1.1  //
/**
 * NON-POINTER VERSION
 * 
 * This function colors each blood cell with a unique color
 * (i.e. unique number)
 * 
 * int image[][] - input matrix
 **/
void color(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    /**
     * This is an array equivalent to the input image
     * but will have the label connected components
     */
    int connected[IMAGE_SIZE][IMAGE_SIZE] = {0};

    int componentLabel = 0; // component labelling

    /**********FIRST PASS************
     * This pass will find and label all the connected components 
    */
    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++)
    {
        for (j = 0; j < IMAGE_SIZE; j++)
        {
            if (image[i][j] && !connected[i][j])
            {
                connected[i][j] = componentLabel;

                // boolean statement to check if surrounding
                // coordinates have already been labelled
                int notSurrounded = 0;

                // check every direction surrounding to current coordinate
                int d;
                for (d = 0; d < 8; ++d)
                {
                    int aroundX = i + xDir[d];
                    int aroundY = j + yDir[d];

                    // if neighbour is a valid coordinate
                    if (validCoor(aroundX, aroundY))
                    {
                        // if this coordinate is in the grid and has a non zero value
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

                    if (validCoor(aroundX, aroundY))
                    {
                        // if neighbours are different, change the neighbours to be the same
                        if (connected[aroundX][aroundY] && (connected[y][z] != connected[aroundX][aroundY]))
                            connected[aroundX][aroundY] = connected[y][z];
                    }
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
// TASK 2.1  //
/**
 * POINTER VERSION
 * 
 * This function colors each blood cell with a unique color
 * (i.e. unique number)
 * 
 * int image[][] - input matrix
 **/
void colorPtr(int *image)
{
    /**
     * This is an array equivalent to the input image
     * but will have the label connected components
     */
    int connected[IMAGE_SIZE][IMAGE_SIZE] = {0};
    int *connectedPtr = connected; // pointer to connected array

    int componentLabel = 0; // component labelling

    int currImageCoor; // current image coordinate
    int currConnectedCoor; // current connected coordinate
    int surroundConnectedCoor; // the neighbouring coordinate of connected
    
    int *xDirPtr = xDir; // pointer to xDir values
    int *yDirPtr = yDir; // pointer to yDir values

    /**********FIRST PASS************
     * This pass will find and label all the connected components 
    */
    int i, j;
    for (i = 0; i < IMAGE_SIZE; i++)
    {
        for (j = 0; j < IMAGE_SIZE; j++)
        {
            currImageCoor = *((image + i * IMAGE_SIZE) + j);
            currConnectedCoor = *((connectedPtr + i * IMAGE_SIZE) + j);
            
            if (*((image + i * IMAGE_SIZE) + j) && !*((connectedPtr + i * IMAGE_SIZE) + j))
            {
                *((connectedPtr + i * IMAGE_SIZE) + j) = componentLabel;

                // boolean statement to check if surrounding
                // coordinates have already been labelled
                int notSurrounded = 0;

                // check every direction surrounding to current coordinate
                int d;
                for (d = 0; d < 8; ++d)
                {
                    int aroundX = i + *(xDirPtr + d);
                    int aroundY = j + *(yDirPtr + d);

                    // if neighbour is a valid coordinate
                    if (validCoor(i + *(xDirPtr + d), j + *(yDirPtr + d)))
                    {
                        surroundConnectedCoor = *((connectedPtr + aroundX * IMAGE_SIZE) + aroundY);
                        
                        // if this coordinate is in the grid and has a non zero value
                        // this means this is a labelled component
                        notSurrounded = notSurrounded || *((connectedPtr + aroundX * IMAGE_SIZE) + aroundY);

                        // if the respective neighbour in the labelled array is
                        // already labelled, let them share the same label
                        // else if all the neighbours are 0 and the equivalent coordinate
                        // is labelled, let this component in the labelled array signify
                        // a new connected component
                        if (*((connectedPtr + aroundX * IMAGE_SIZE) + aroundY))
                        {
                            *((connectedPtr + i * IMAGE_SIZE) + j) = *((connectedPtr + aroundX * IMAGE_SIZE) + aroundY);
                            d = 7; // get out of loop
                        }
                        else if (!*((connectedPtr + aroundX * IMAGE_SIZE) + aroundY) && d == 6)
                        {
                            //componentLabel += 1;
                            *((connectedPtr + i * IMAGE_SIZE) + j) = ++componentLabel;
                        }
                            
                    }
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
            currConnectedCoor = *((connectedPtr + y * IMAGE_SIZE) + z);
            
            // if this is a non zero component
            if (*((connectedPtr + y * IMAGE_SIZE) + z))
            {
                // check all surrounding neighbours
                int d;
                for (d = 0; d < 8; ++d)
                {
                    int aroundX = y + *(xDirPtr + d);
                    int aroundY = z + *(yDirPtr + d);

                    surroundConnectedCoor = *((connectedPtr + aroundX * IMAGE_SIZE) + aroundY);

                    if (validCoor(y + *(xDirPtr + d), z + *(yDirPtr + d)))
                    {
                        // if neighbours are different, change the neighbours to be the same
                        if (*((connectedPtr + aroundX * IMAGE_SIZE) + aroundY) && (*((connectedPtr + y * IMAGE_SIZE) + z) != *((connectedPtr + aroundX * IMAGE_SIZE) + aroundY)))
                            *((connectedPtr + aroundX * IMAGE_SIZE) + aroundY) = *((connectedPtr + y * IMAGE_SIZE) + z);
                    }
                }
            }
        }
    }

    // make the original array, into the labelled array
    int m, p;
    for (m = 0; m < IMAGE_SIZE; m++)
    {
        for (p = 0; p < IMAGE_SIZE; p++)
            *((image + m * IMAGE_SIZE) + p) = *((connectedPtr + m * IMAGE_SIZE) + p);
    }
}

// TASK 2.2  //
/**
 * POINTER VERSION
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
int validCoorPtr(int *x, int *y)
{
    return (*x >= 0 && *x < IMAGE_SIZE && *y >= 0 && *y < IMAGE_SIZE);
}

/**
 * POINTER VERSION
 * 
 * A helper method that marks all the connected components of a label
 * If a non zero number in the input array is found, it will recursively 
 * mark all the neighbours of the component in the visited array. This will
 * tell us not to increment the count because its component was already 
 * accounted for
 * 
 * int image[][] - the input array
 * int i - the x coordinate we are checking
 * int y - the y coordiante we are checking
 * int visited[][] - the array keeping track of the coordinates that have
 *                   already been seen/ don't need to check
 */
void markNeighboursPtr(int *image, int *i, int *j, int *visited)
{
    int iVal = *i;
    int jVal = *j;

    //int currVisitedCoor = *((visited + iVal * IMAGE_SIZE) + jVal);

    if (!validCoorPtr(&iVal, &jVal)) // return this is not a valid coordinate
        return;

    if (*((visited + iVal * IMAGE_SIZE) + jVal)) // return if we already checked this coordinates connectivity
        return;

    *((visited + iVal * IMAGE_SIZE) + jVal) = 1; // let this coordinate be marked as seen

    int aroundX; // neighbouring X
    int aroundY; // neighbouring Y

    // recursively check the surrounding coordinate in all directions
    int d;
    for (d = 0; d < 8; ++d)
    {
        // since the direction arrays are parallel, this is possible
        aroundX = iVal + xDir[d];
        aroundY = jVal + yDir[d];

        int imageCoorisLabelled = *((image + aroundX * IMAGE_SIZE) + aroundY);
        int visitedCoorisLabelled = *((visited + aroundX * IMAGE_SIZE) + aroundY);

        // if the neighbouring coordinate is valid and that coordinated is labelled in the input array
        // but not the visited array, mark it in the label array and check that point's neighbours
        if (validCoorPtr(&aroundX, &aroundY) && (imageCoorisLabelled && !visitedCoorisLabelled))
            markNeighboursPtr(image, &aroundX, &aroundY, visited);
    }
}

/**
 * POINTER VERSION
 * 
 * Returns the number of distinct cells 
 * in the given matrix
 * 
 * int *image - the matrix
 * 
 * Assuming, *image is already labelled
 **/
int cellCountPtr(int *image)
{
    int count = 0; // the number of distinct cells

    // an array that will hold non zero vales, to ensure we don't increment our count
    // on an already visited coordinate
    int visited[IMAGE_SIZE][IMAGE_SIZE] = {0};
    int *visitedPtr = visited;

    int i, j;
    int currImageCoor, currVisitedCoor;
    for (i = 0; i < IMAGE_SIZE; ++i)
    {
        for (j = 0; j < IMAGE_SIZE; ++j)
        {
            currImageCoor = *((image + i * IMAGE_SIZE) + j);
            currVisitedCoor = *((visitedPtr + i * IMAGE_SIZE) + j);

            if (currImageCoor && !currVisitedCoor)
            {
                markNeighboursPtr(image, &i, &j, visitedPtr);
                ++count;
            }
        }
    }
    return count;
}

/********************************************************************************/

// BONUS  //
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
void connect(int x, int y, int componentLabel, int image[IMAGE_SIZE][IMAGE_SIZE], int connectedR[IMAGE_SIZE][IMAGE_SIZE])
{

    /**
     *  Checks if the surround coordinates of the current index 
     *  is out of bounds. For example, will not compute the North,
     *  West, North West, and North East coordinates of the first 
     *  index of the array because they do not exist
     */
    if (!validCoor(x, y))
        return;

    // mark the current index in the copy array
    connectedR[x][y] = componentLabel;

    // recursively check the surrounding coordinates
    int d;
    for (d = 0; d < 8; ++d)
    {
        int aroundX = x + xDir[d];
        int aroundY = y + yDir[d];

        // if the respective neighbour in the original array is labelled
        // the same neighbour is not labelled in the copy array
        if (image[aroundX][aroundY] && !connectedR[aroundX][aroundY])
            connect(aroundX, aroundY, componentLabel, image, connectedR);
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
                connect(i, j, ++componentLabel, image, connectedR);
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