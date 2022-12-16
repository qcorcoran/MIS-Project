//Quinn Corcoran
//circularArc

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

//header function declaration
double* createLine(double angle1, double angle2, int r, double* slopeYint);

int main(int argc, char** argv){
    //declare local variables
    string infile = "input.txt";
    string ansfile = "answer.txt";
    ifstream myfile;
    int arcs = 0;
    int arcsRem = 0;
    int radius = 0;
    int arcPoints = 0;
    int startIndex = 0;
    int endIndex = 0;
    double* ac;
    int mis = 0;

    //initialize random seed
    //srand(time(NULL));
    srand(0);

    //prompt user for input
    /*
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter name of answer file to create: ";
    cin>>ansfile;
    */
    cout<<"Enter number of arcs to create: ";
    cin>>arcs;
    cout<<"Enter the radius of the circle: ";
    cin>>radius;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of arcs and the center position and radius of the circle to the input file
    iFile << arcs << " " << 0 << " " << 0 << " " << radius << "\n";

    //initialize arcsRem
    arcsRem = arcs;

    //allocate ac
    ac = new double[2];

    //set the number of points to create around the circle for MIS arcs
    arcPoints = 2*arcs;

    //set the points around the circle for MIS arcs
    double angles[arcPoints];
    int index = 0;
    for(double i=0; i < 2*M_PI; i+=((2*M_PI)/arcPoints)){
        angles[index] = i;
        assert(angles[index] >= 0);
        assert(angles[index] <= 2*M_PI);
        index++;
    }

    //set an MIS
    mis = (rand() % arcs) + 1;

    //create arcs in MIS
    for(int i=0; i < mis*2; i+=2){
        ac = createLine(angles[i], angles[i+1], radius, ac);
        iFile << ac[0] << " " << -1 << " " << ac[1] << "\n";
    }

    //create points around the circle for overlapping arcs
    double alphaAngles[mis];
    index = 0;
    for(int i=0; i < mis*2; i+=2){
        alphaAngles[index] = (angles[i+1] + angles[i]) / 2;
        assert(alphaAngles[index] <= angles[i+1]);
        assert(alphaAngles[index] >= angles[i]);
        index++;
    }

    arcsRem -= mis;
    //create remaining arcs
    for(int i=0; i < arcsRem; i++){
        //the start and endpoints will be between the start and enpoint of MIS arcs
        //this ensures that all of these arcs overlap with at least one MIS arc
        do{
            startIndex = (rand() % mis);
            assert(startIndex < mis);
            endIndex = (rand() % mis);
            assert(endIndex < mis);
        }while(startIndex == endIndex);
        ac = createLine(alphaAngles[startIndex], alphaAngles[endIndex], radius, ac);
        iFile << ac[0] << " " << -1 << " " << ac[1] << "\n";
    }

    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the solution to the answer file
    aFile << mis << "\n";

    //close the answer file
    aFile.close();

    //deallocate ac
    delete[] ac;

    return 0;
}

double* createLine(double angle1, double angle2, int r, double* slopeC){
    //get intersection coordinates
    double x1 = r * cos(angle1);
    double y1 = r * sin(angle1);
    double x2 = r * cos(angle2);
    double y2 = r * sin(angle2);

    //create the line by assigning slope and C
    slopeC[0] = (y2 - y1) / (x2 - x1);
    slopeC[1] = -1 * (slopeC[0] * x1 - y1);
    
    return slopeC;
}
