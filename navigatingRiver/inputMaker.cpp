//Quinn Corcoran
//navigatingRiver

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <time.h>
#include <math.h>

#define RANDMAX 32767

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    string ansfile = "answer.txt";
    string infile = "input.txt";
    ifstream myfile;
    int numPoints = 0;
    int pointsRem = 0;
    int leftRight = 0;
    int minX = -1;
    int maxX = 50;
    int minY = 0;
    int maxY = 100;
    int diameter = 3;
    int point[2];
    int leftOpen[2];
    int rightOpen[2];
    int startPoint[2];
    int endPoint[2];
    int prevPoint[2];

    //initialize random seed
    srand(time(NULL));

    //prompt user for input
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter name of answer file to create: ";
    cin>>ansfile;
    cout<<"Enter number of points to create: ";
    cin>>numPoints;
    cout<<"Enter the maximum diameter: ";
    cin>>diameter;
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

    //create the largest gap based on the diameter entered
    leftOpen[0] = (rand() % ((maxX-1) - (minX + 1) + 1)) + minX+1;
    leftOpen[1] = (rand() % ((maxY-1) - (minX + 1) + 1)) + minY+1;
    pointsRem--;
    rightOpen[0] = leftOpen[0] + diameter;
    rightOpen[1] = leftOpen[1];
    pointsRem--;
    //ensure that the gap is the right size
    assert((pow((pow((rightOpen[0] - leftOpen[0]), 2) + pow((rightOpen[1] - leftOpen[1]), 2)), 0.5)) == diameter);
    //write the gap points to the file
    iFile << leftOpen[0] << " " << leftOpen[1] << "\n";
    iFile << rightOpen[0] << " " << rightOpen[1] << "\n";

    //now make a wall of points on either side of the gap that has no gaps larger than the diameter//

    //create start and end points for our wall
    startPoint[0] = minX + diameter - 1;
    startPoint[1] = leftOpen[1];
    pointsRem--;
    endPoint[0] = maxX - diameter + 1;
    endPoint[1] = leftOpen[1];
    pointsRem--;
    //write the start and end points to the file
    iFile << startPoint[0] << " " << startPoint[1] << "\n";
    iFile << endPoint[0] << " " << endPoint[1] << "\n";

    //create our leftside wall
    point[0] = startPoint[0];
    point[1] = startPoint[1];
    while(point[0] < (leftOpen[0] - diameter)){
        //keep track of previous point for the assert
        prevPoint[0] = point[0];
        prevPoint[1] = point[1];
        //place the new point at 1 less than the diameter ahead of the previous point on the x-axis
        point[0] = point[0] + diameter - 1;
        //do not let any points for our wall go inside of the gap but ensure that the wall has no gaps
        while(point[0] >= leftOpen[0]){
            point[0]--;
        }
        //all points in our wall are at the height on the y-axis
        point[1] = point[1];
        pointsRem--;
        //ensure the wall has no gaps
        assert((pow((pow((point[0] - prevPoint[0]), 2) + pow((point[1] - prevPoint[1]), 2)), 0.5)) <= diameter);
        //write the new point to the file
        iFile << point[0] << " " << point[1] << "\n";   
    }

    //create our rightside wall
    point[0] = rightOpen[0];
    point[1] = rightOpen[1];
    while(point[0] < (endPoint[0] - diameter)){
        //keep track of previous point for the assert
        prevPoint[0] = point[0];
        prevPoint[1] = point[1];
        //place the new point at 1 less than the diameter ahead of the previous point on the x-axis
        point[0] = point[0] + diameter - 1;
        //do not let any points for our wall go past the endpoint but ensure that the wall has no gaps
        while(point[0] >= endPoint[0]){
            point[0]--;
        }
        //all points in our wall are at the height on the y-axis
        point[1] = point[1];
        pointsRem--;
        //ensure the wall has no gaps
        assert((pow((pow((point[0] - prevPoint[0]), 2) + pow((point[1] - prevPoint[1]), 2)), 0.5)) <= diameter);
        //write the new point to the file
        iFile << point[0] << " " << point[1] << "\n";
    }

    //if more points than we were told to make were required to build the wall throw an error
    if(pointsRem < 0){
        cerr<<"Not enough points to create the wall"<<endl;
    }

    //create remaining points
    while(pointsRem > 0){
        if(leftRight == 0){
            //place a point randomly inside the section to the left of the gap
            point[0] = (rand() % ((leftOpen[0] - 1) - (minX + 1) + 1)) + minX + 1;
            point[1] = (rand() % ((maxY - 1) - (minY + 1) + 1)) + minY + 1;
            leftRight++;
            //ensure that the point is within the left section
            assert(point[0] < leftOpen[0]);
            assert(point[0] > minX);
            assert(point[1] < maxY);
            assert(point[1] > minY);
        }
        else if(leftRight == 1){
            //place a point randomly inside the section to the right of the gap
            point[0] = (rand() % ((maxX - 1) - (rightOpen[0] + 1) + 1)) + rightOpen[0] + 1;
            point[1] = (rand() % ((maxY - 1) - (minY + 1) + 1)) + minY + 1;
            leftRight--;
            //ensure that the point is within the right section
            assert(point[0] > rightOpen[0]);
            assert(point[0] < maxX);
            assert(point[1] > minY);
            assert(point[1] < maxY);
        }
        pointsRem--;
        //write the new point to the file
        iFile << point[0] << " " << point[1] << "\n";
    }

    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the solution to the answer file
    aFile << diameter << "\n";

    //close the answer file
    aFile.close();

    return 0;
}
