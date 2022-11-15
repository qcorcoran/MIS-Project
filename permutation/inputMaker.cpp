//Quinn Corcoran
//permutation

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <assert.h>
#include <time.h>

#define RANDMAX 32767

using namespace std;

int main(int argc, char** argv){
    //declare local variables
    string ansfile = "answer.txt";
    string infile = "input.txt";
    ifstream myfile;
    int permutations = 0;
    int lis = 0;
    int lisStart = 0;
    int p = 0;
    int prevP = 0;

    //initialize random seed
    srand(time(NULL));

    //prompt user for input
    /*
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter name of answer file to create: ";
    cin>>ansfile;
    cout<<"Enter number of permutations to create: ";
    cin>>permutations;
    */
    permutations = 15;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of permutations to the input file
    iFile << permutations << "\n";

    //set a random number of sets of overlapping permutations
    //the MIS will be equal to the number of sets
    lis = (rand() % permutations) + 1;
    lisStart = (rand() % (permutations-lis)) + 1;

    cout<<lis<<" "<<lisStart<<endl;

    int i = 0;
    prevP = 1000000;
    while(i < permutations){
        if(i == lisStart-1){
            cout<<"if "<<i<<endl;
            p = (rand() % (prevP-1)) + 1;
            cout<<"p "<<p<<" prevp "<<prevP<<endl;
            assert(p < prevP);
            prevP = p;
            iFile << p << "\n";
            i++;
            for(int j=1; j < lis; j++){
                cout<<"for "<<i<<endl;
                p = (rand() % 1000000) + prevP + 1;
                assert(p > prevP);
                cout<<"p "<<p<<" prevp "<<prevP<<endl;
                prevP = p;
                iFile << p << "\n";
                i++;    
            }
        }
        if(i >= permutations){
            break;
        }
        p = (rand() % prevP-1) + 1;
        assert(p < prevP);
        prevP = p;
        iFile << p << "\n";
        i++;
    }
    

    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the solution to the answer file
    aFile << lis << "\n";

    //close the answer file
    aFile.close();

    return 0;
}
