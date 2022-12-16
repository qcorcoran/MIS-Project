//Quinn Corcoran
//building

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>

#define RANDMAX 2000

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    string infile = "input.txt";
    string ansfile = "answer.txt";
    ifstream myfile;
    int numBuildings = 20;
    int paths = 5;
    int buildingsRem = 0;
    int l = 0;
    int r = 0;
    int b = 0;
    int t = 0;
    int cl = 0;
    int cr = 0;
    int cb = 0;
    int ct = 0;

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
    cout<<"Enter number of buildings to create: ";
    cin>>numBuildings;
    cout<<"Enter number of paths to create: ";
    cin>>paths;

    assert(paths < numBuildings);

    buildingsRem = numBuildings;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the first line of the input file
    iFile << numBuildings << "\n";

    //make first path pair
    //leftmost box
    l = (rand() % RANDMAX) + r;
    r = (rand() % RANDMAX) + l + 1;
    b = rand() % RANDMAX;
    t = (rand() % RANDMAX) + b + 1;
    iFile << l << " " << r << " " << b << " " << t << "\n";
    buildingsRem--;
    //rightmost box
    l = r;
    r = (rand() % RANDMAX) + l  + 1;
    iFile << l << " " << r << " " << b << " " << t << "\n";
    buildingsRem--;

    for(int i=0; i < paths-1; i++){
        //make connectors
        //top connector
        cl = r;
        cr = (rand() % RANDMAX) + cl + 1;
        cb = t;
        ct = (rand() % RANDMAX) + cb + 1;
        iFile << cl << " " << cr << " " << cb << " " << ct << "\n";
        buildingsRem--;
        //bottom connector
        cl = r;
        ct = b;
        cb = (rand() % (ct-1));
        iFile << cl << " " << cr << " " << cb << " " << ct << "\n";
        buildingsRem--;

        //make path pair
        //leftmost box
        l = cr;
        r = (rand() % RANDMAX) + l + 1;
        iFile << l << " " << r << " " << b << " " << t << "\n";
        buildingsRem--;
        //rightmost box
        l = r;
        r = (rand() % RANDMAX) + l + 1;
        iFile << l << " " << r << " " << b << " " << t << "\n";
        buildingsRem--;
    }
    assert(buildingsRem >= 0);

    //make remaining buildings
    //if an even number are left to make
    if(buildingsRem % 2 == 0){
        cb = t;
        t = (rand() % RANDMAX) + cb + 1;
        while(buildingsRem > 0){
            l = r;
            r = (rand() % RANDMAX) + l + 1;
            //top box
            iFile << l << " " << r << " " << cb << " " << t << "\n";
            buildingsRem--;
            //bottom box
            iFile << l << " " << r << " " << b << " " << cb << "\n";
            buildingsRem--;
        }
    }
    //if an odd number are left to make
    else{
        //top connector bottom
        cb = t;
        //bottom connector top
        ct = b;
        while(buildingsRem > 1){
            l = r;
            r = (rand() % RANDMAX) + l + 1;
            t = (rand() % RANDMAX) + cb + 1;
            b = (rand() % (ct-1));
            //top connector
            iFile << l << " " << r << " " << cb << " " << t << "\n";
            buildingsRem--;
            //bottom connector
            iFile << l << " " << r << " " << b << " " << ct << "\n";
            buildingsRem--;
        }
        l = r;
        r = (rand() % RANDMAX) + l + 1;
        iFile << l << " " << r << " " << b << " " << t << "\n";
        buildingsRem--;
    }

    assert(buildingsRem == 0);


    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the solution to the answer file
    aFile << paths << "\n";

    //close the answer file
    aFile.close();

    return 0;
}
