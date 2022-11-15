//Quinn Corcoran
//trapezoidShooting

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
    int trapezoids = 0;
    int sets = 0;
    int remain = 0;
    int randomAdd = 0;
    int bottomMin = 0;
    int bottomMax = 0;
    int topMin = 0;
    int topMax = 0;
    int uMin = 0;
    int wMax = 0;
    int ui = 0;
    int vi = 0;
    int wi = 0;
    int zi = 0;

    //initialize random seed
    srand(time(NULL));

    //prompt user for input
    cout<<"Enter name of input file to create: ";
    cin>>infile;
    cout<<"Enter name of answer file to create: ";
    cin>>ansfile;
    cout<<"Enter number of trapezoids to create: ";
    cin>>trapezoids;

    //create and open input file
    ofstream iFile(infile.c_str());

    //write the number of trapezoids to the input file
    iFile << trapezoids << "\n";

    //set a random number of sets of overlapping trapezoids
    //the MIS will be equal to the number of sets
    sets = (rand() % trapezoids) + 1;

    //keep track of the trapezois that need to be added to a set
    remain = trapezoids;
    //array of the number of trapezoids in each set
    int numberPerSet[sets];

    //initialize sets array with one trapezoid per set
    for(int i=0; i < sets; i++){
        numberPerSet[i] = 1;
        remain--;
    }

    //add a random number of trapezoids to each set until there are no more trapezoids left
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

    //create the given number of trapezoids
    for(int i=0; i < sets; i++){
        //set the bounds of the set
        bottomMin = (rand() % RANDMAX/sets) + max(bottomMax, topMax) + 20;
        assert(bottomMin >= 0);
        assert(bottomMin > bottomMax);
        assert(bottomMin > topMax);
        topMin = (rand() % RANDMAX/sets) + max(bottomMax, topMax) + 20;
        assert(topMin >= 0);
        assert(topMin > bottomMax);
        assert(topMin > topMax);
        bottomMax = (rand() % RANDMAX/sets) + bottomMin + 10 + numberPerSet[i];
        assert(bottomMax >= bottomMin);
        topMax = (rand() % RANDMAX/sets) + topMin + 10 + numberPerSet[i];
        assert(topMax >= topMin);
        ui = bottomMin;
        wi = topMax;
        uMin = bottomMin;
        wMax = topMax;
        for(int j=0; j < numberPerSet[i]; j++){
            //by making the bottom start point increase and the top startpoint decrease
            //we ensure that every trapezoid in the set will overlap with eachother
            //so we know that each set is worth exactly one point towards our MIS
            //the endpoints are random but set to remain inside the bounds of the set
            //the asserts ensure that the trapezoids reamin in the bounds of their set
            ui++;
            assert(ui < bottomMax);
            assert(ui > bottomMin);
            assert(ui > uMin);
            vi = (rand() % (bottomMax-ui+1)) + ui;
            assert(vi <= bottomMax);
            assert(vi >= ui);
            wi--;
            assert(wi < topMax);
            assert(wi < wMax);
            assert(wi > topMin);
            zi = (rand() % (topMax-wi+1)) + wi;
            assert(zi <= topMax);
            assert(zi >= wi);
            //these ifs ensure that no trapezoids are only a single line
            if(ui == vi){
                vi++;
            }
            if(wi == zi){
                zi++;
            }
            uMin = ui;
            wMax = wi;
            //write the trapezoids to the input file
            iFile << ui << " " << vi << " " << wi << " " << zi << "\n";
        }
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
