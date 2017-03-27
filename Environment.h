#ifndef ENVIRONMENT_H
#define	ENVIRONMENT_H
#include "Line.h"
#include <iostream>
#include <vector>


class Environment {
public:
    typedef Integer PointValuesType;
    typedef Point<PointValuesType> PointE;
    typedef Line<PointValuesType> LineE;
    typedef std::vector<LineE> Walls;
    typedef std::istream istream;
    typedef std::ostream ostream;
private:
    Walls env;
public:
    Environment();
    Environment(const Environment& orig);
    
    Walls getWalls() const {return env;}
    Walls& getWalls() {return env;}
    friend istream& operator >> (istream& input, Environment& env);
    friend ostream& operator << (ostream& output, Environment& env);
    
    virtual ~Environment();
private:

};

#endif	/* ENVIRONMENT_H */

