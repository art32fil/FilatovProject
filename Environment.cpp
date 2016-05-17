/* 
 * File:   Environment.cpp
 * Author: Артём
 * 
 * Created on 14 Май 2016 г., 16:39
 */

#include "Environment.h"


Environment::Environment() {}

Environment::istream& operator >> (Environment::istream& input, Environment& env){
    typedef Environment::PointE PointE;
    typedef Environment::LineE LineE;
    PointE firstPt;
    bool firstPointRead = false;;
    while(!input.eof()){
        PointE p1;
        PointE p2;
        input >> p1;
        if(!firstPointRead)
            firstPt = p1;
        firstPointRead = true;
        if(!input.eof())
            input >> p2;
        else
            p2 = firstPt;
        if(!(p1 == p2))
            env.getWalls().push_back(LineE(p1,p2));
    }
    return input;
}

Environment::ostream& operator <<(Environment::ostream& output, Environment& env){
    for(auto line: env.getWalls()){
        output << line << " with equation ";
        if(line.isVertical())
            output << "x = " << line.p1.x << "\n";
        else
            output << "y = " << line.GetK() << "*x" << (line.GetB() < 0 ? " " : " +") << line.GetB() << "\n"; 
    }
    return output;
}

Environment::Environment(const Environment& orig) {
    env = orig.getWalls();
}

Environment::~Environment() {
}

