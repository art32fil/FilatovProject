#ifndef ROBOT_H
#define	ROBOT_H
#include "Line.h"
#include "Environment.h"

class Robot{
public:
    typedef Point<Environment::PointValuesType> PointR;
    typedef Line<Environment::PointValuesType> LineR;
    typedef Line<Double> LineRD;
private:
    PointR position;
    Environment area;
    Double angleStep;
public:
    
    Robot(const Environment& area, const PointR& position = 0, const Double& angleStep = 1):area(area),position(position),angleStep(angleStep){}
    Robot(const Robot& orig){
        position = orig.position;
        area = orig.area;
        angleStep = orig.angleStep;
    }
    Double* CalcCrossingPoints();
};


#endif	/* ROBOT_H */

