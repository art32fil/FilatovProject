#include <iostream>
#include <sstream>
#include <fstream>
#include "Environment.h"
#include "Robot.h"
using namespace std;



int main(int argc, char** argv) {
    typedef Point<Integer> Point;
    typedef Line<Integer> Line;
    
    ifstream inputFile("environment.txt");
    Environment env;
    inputFile >> env;
    
    cout << env << "\n\n\n";
    
    Robot r(env,Point(5,5),1);
    int amount = 361;
    Double* res = r.CalcCrossingPoints();
    for(int i = 0; i < amount; i++){
        cout << "fi = " << i << ", d = " << res[i] << endl;
    }
    
    return 0;
}

