//Quinn Corcoran
//navigatingRiver

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <math.h>

#define RANDMAX 32767

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    string infile = "input.txt";
    ifstream myfile;
    int numPoints = 10;
    int pointsRem = 0;
    int leftRight = 0;
    int minX = 0;
    int maxX = 20;
    int minY = 0;
    int maxY = 20;
    int point[2];
    
    //initialize random seed
    //srand(time(NULL));
    srand(0);

    //prompt user for input
    /*
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    */
    cout<<"Enter number of points to create: ";
    cin>>numPoints;
    cout<<"Enter the minimum x value: ";
    cin>>minX;
    cout<<"Enter the maximum x value: ";
    cin>>maxX;
    cout<<"Enter the minimum y value: ";
    cin>>minY;
    cout<<"Enter the maximum y value: ";
    cin>>maxY;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the first line of the input file
    iFile << minX << " " << maxX << " " << minY << " " << maxY << " " << numPoints << "\n";

    //initialize the points that still need to be added
    pointsRem = numPoints;

    //create the points
    while(pointsRem > 0){
        //place a point randomly inside the river
        point[0] = (rand() % ((maxX - 1) - (minX + 1) + 1)) + minX + 1;
        point[1] = (rand() % ((maxY - 1) - (minY + 1) + 1)) + minY + 1;
        leftRight++;
        //ensure that the point is within the river
        assert(point[0] > minX);
        assert(point[1] < maxY);
        assert(point[1] > minY);
        
        pointsRem--;
        //write the new point to the file
        iFile << point[0] << " " << point[1] << "\n";
    }

    //close the input file
    iFile.close();

    return 0;
}
