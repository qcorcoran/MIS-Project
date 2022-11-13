//Quinn Corcoran

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
    int sets = 0;
    int remain = 0;
    int randomAdd = 0;
    int pMin = 1;
    int pMax = 0;
    int p = 0;

    //initialize random seed
    srand(time(NULL));

    //prompt user for input
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter name of answer file to create: ";
    cin>>ansfile;
    cout<<"Enter number of permutations to create: ";
    cin>>permutations;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of permutations to the input file
    iFile << permutations << "\n";

    //set a random number of sets of overlapping permutations
    //the MIS will be equal to the number of sets
    sets = (rand() % permutations) + 1;

    //keep track of the permutations that need to be added to a set
    remain = permutations;
    //array of the number of permutations in each set
    int numberPerSet[sets];

    //initialize sets array with one permutation per set
    for(int i=0; i < sets; i++){
        numberPerSet[i] = 1;
        remain--;
    }

    //add a random number of permutations to each set until there are no more permutations left
    while(remain > 0){
        for(int i=0; i < sets; i++){
            //dividing by the number of sets makes it more likely that each set will be added to
            randomAdd = (rand() % remain/sets);
            if(randomAdd == 0){
                randomAdd++;
            }
            numberPerSet[i] += randomAdd;
            remain -= randomAdd;
            if(remain == 0){
                break;
            }
        }
    } 

    //create the given number of permutations
    for(int i=0; i < sets; i++){
        //set the bounds of the set
        pMax = numberPerSet[i] + pMin - 1;
        for(int j=0; j < numberPerSet[i]; j++){
            p = pMax;
            assert(p >= pMin);
            assert(p <= pMax);
            pMax = p-1;
            //write the permutations to the input file
            iFile << p << "\n";
        }
        pMin = pMax + 1;
    }

    //close the input file
    iFile.close();

    //create and open answer file
    ofstream aFile(ansfile.c_str());

    //write the solution to the answer file
    aFile << sets << "\n";

    //close the answer file
    aFile.close();

    return 0;
}
