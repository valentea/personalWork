/* 
maze.cpp

Author:Alex Valente

Short description of this file: FIND SHORTEST PATH FROM START TO FINISH IN A MAZE A DEFINED BY '.in' FILE
                                THAT STARTS WITH NUMBERS THAT REPRESENT NUMBER OF ROWS AND COLLUMS.
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);


// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result = 0;
    char **myMaze;
    cin >> rows;
    cin >> cols;


    myMaze = read_maze(&rows, &cols);

    if (myMaze == NULL) {
        cout << "Error, input format incorrect" << endl;
        return 1;
    }

    // when working on Checkpoint 3, you will call maze_search here.
    // here. but for Checkpoint 1, just assume we found the path.
    result = maze_search(myMaze, rows, cols);

    if (result == 1) { // path found!
        cout << rows << " " << cols << endl;
        print_maze(myMaze, rows, cols);
    }
    else if (result == 0) { // no path :(
        cout << "No path could be found!" << endl;
    }
    else { // result == -1
        cout << "Invalid maze." << endl;
    }

    // ADD CODE HERE to delete all memory
    // that read_maze allocated

    for (int i = 0; i < rows; i++) { //DELETE ALL ALLOCATED MEM
        delete[] myMaze[i];
    }
    delete[] myMaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze(not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
//return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.

int maze_search(char** maze, int rows, int cols) {
    int maxObjects = rows * cols;
    Queue exploredPoints(maxObjects);
    Location startPoint;
    bool startReal = false;
    Location finishPoint;
    bool finishReal = false;


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (maze[i][j] == 'S') {  //DOUBLE 'FOR' LOOP TO FIND THE STARTING POINT
                startPoint.row = i;
                startPoint.col = j;
                startReal = true;
            }
            if (maze[i][j] == 'F') {  //DOUBLE 'FOR' LOOP TO FIND THE END POINT
                finishPoint.row = i;
                finishPoint.col = j;
                finishReal = true;
            }
        }
    }

    if (startReal != true || finishReal != true) { //CHECK FOR ONE START AND END POINTS
        return -1;
    }

    Location **previousPoint = new Location *[rows];  //ALLOCATE MEM
    bool **lookedAt = new bool *[rows];
    for (int i = 0; i < rows; i++) {
        previousPoint[i] = new Location[cols];
        lookedAt[i] = new bool[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            lookedAt[i][j] = 0;
            previousPoint[i][j].row = -1;
            previousPoint[i][j].col = -1;
        }
    }

    lookedAt[startPoint.row][startPoint.col] = 1; //WE HAVE LOOKED AT THE START POINT AS SOON AS WE FIND THE START
    previousPoint[startPoint.row][startPoint.col].row = -1; //SET 'startPoint' PREVIOUS POINT OFF THE MAP
    previousPoint[startPoint.row][startPoint.col].col = -1;
    exploredPoints.add_to_back(startPoint); //WE HAVE LOOKED AT THE START POINT AS SOON AS WE FIND THE START

    while (!exploredPoints.is_empty()) { //RUN LOOP WHILE WE HAVE NOT EXPLORED ALL POINTS
        Location currentPoint = exploredPoints.remove_from_front();

        if (currentPoint.row == finishPoint.row && currentPoint.col == finishPoint.col) {

            //WHEN END IS FOUND GO BACK USING 'previousPoint' ARRAY UNTIL WE ARE BACK AT THE START POINT
            while (maze[previousPoint[currentPoint.row][currentPoint.col].row][previousPoint[currentPoint.row][currentPoint.col].col] != 'S') {
                maze[previousPoint[currentPoint.row][currentPoint.col].row][previousPoint[currentPoint.row][currentPoint.col].col] = '*';
                currentPoint = previousPoint[currentPoint.row][currentPoint.col];
            }
            for (int i = 0; i < rows; i++) { //DELETE ALL ALLOCATED MEM
                delete[] previousPoint[i];
                delete[] lookedAt[i];
            }
            delete[] previousPoint;
            delete[] lookedAt;
            return 1;
        }

        //LOOK NORTH
        if (currentPoint.row - 1 >= 0) {
            if (maze[currentPoint.row - 1][currentPoint.col] == '.' ||
                    maze[currentPoint.row - 1][currentPoint.col] == 'F') {
                if (!lookedAt[currentPoint.row - 1][currentPoint.col]) {
                    Location northPoint;
                    northPoint.row = currentPoint.row - 1;
                    northPoint.col = currentPoint.col;
                    exploredPoints.add_to_back(northPoint);
                    previousPoint[currentPoint.row - 1][currentPoint.col] = currentPoint;
                    lookedAt[currentPoint.row - 1][currentPoint.col] = true;
                }
            }
        }

        //LOOK WEST
        if (currentPoint.col - 1 >= 0) {
            if (maze[currentPoint.row][currentPoint.col - 1] == '.' ||
                    maze[currentPoint.row][currentPoint.col - 1] == 'F') {
                if (!lookedAt[currentPoint.row][currentPoint.col - 1]) {
                    Location westPoint;
                    westPoint.row = currentPoint.row;
                    westPoint.col = currentPoint.col - 1;
                    exploredPoints.add_to_back(westPoint);
                    previousPoint[currentPoint.row][currentPoint.col - 1] = currentPoint;
                    lookedAt[currentPoint.row][currentPoint.col - 1] = true;
                }
            }
        }

        //LOOK SOUTH
        if (currentPoint.row + 1 < rows) {
            if (maze[currentPoint.row + 1][currentPoint.col] == '.' ||
                    maze[currentPoint.row + 1][currentPoint.col] == 'F') {
                if (!lookedAt[currentPoint.row + 1][currentPoint.col]) {
                    Location southPoint;
                    southPoint.row = currentPoint.row + 1;
                    southPoint.col = currentPoint.col;
                    exploredPoints.add_to_back(southPoint);
                    previousPoint[currentPoint.row + 1][currentPoint.col] = currentPoint;
                    lookedAt[currentPoint.row + 1][currentPoint.col] = true;
                }
            }

        }

        //LOOK EAST
        if (currentPoint.col + 1 < cols) {
            if (maze[currentPoint.row][currentPoint.col + 1] == '.' ||
                    maze[currentPoint.row][currentPoint.col + 1] == 'F') {
                if (!lookedAt[currentPoint.row][currentPoint.col + 1]) {
                    Location eastPoint;
                    eastPoint.row = currentPoint.row;
                    eastPoint.col = currentPoint.col + 1;
                    exploredPoints.add_to_back(eastPoint);
                    previousPoint[currentPoint.row][currentPoint.col + 1] = currentPoint;
                    lookedAt[currentPoint.row][currentPoint.col + 1] = true;
                }
            }
        }
    } //END OF WHILE LOOP

    //IF NO PATH IS FOUND THEN DELETE MEM, AND RETURN 0
    for (int i = 0; i < rows; i++) {
        delete[] previousPoint[i];
        delete[] lookedAt[i];
    }
    delete[] previousPoint;
    delete[] lookedAt;

    return 0;
}