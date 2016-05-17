#include "Robot.h"
#include <sstream>

#define M_PI 3.14159265358979323846
using std::cout;

Double* Robot::CalcCrossingPoints(){
    typedef Point<Double> PointRD;
    typedef std::vector<PointRD> ArrayPoint;
    PointR p1 = position;
    PointR p2;
    ArrayPoint crossingPointsInEachAngle[int(360/angleStep)+1]; //формула n = (b-a)/delta + 1
    Double* minDistances = new Double[int(360/angleStep)+1];
    int i = 0;
    for(Double fi = 0; fi <= 360; fi+=angleStep){
        p2.x = 1000*cos(fi/360*M_PI)+p1.x;
        p2.y = 1000*sin(fi/360*M_PI)+p1.y;
        LineR ray(p1,p2);
        cout << "ray ";
        if(ray.isVertical())
            cout << "x = " << ray.p1.x;
        else
            cout << "y = " << ray.GetK() << "*x"<< (ray.GetB()<0? " ": " +") << ray.GetB() << " crosses:\n"; 
        for(auto wall: area.getWalls()){
            Point<Double> crossPoint;
            if(abs(wall.GetK() - 1) < 0.0001 && abs(wall.GetB() + 4) < 0.0001){
                int b = 4;
                b+=5;
            }
            if(ray.RayCrossLineSegment(wall,crossPoint)){
                cout << "segment" << wall << " with line ";
                if(wall.isVertical())
                    cout << "x = " << wall.p1.x;
                else
                    cout << "y = " << wall.GetK() << "*x"<< (wall.GetB()<0? " ": " +") << wall.GetB() << " in point (" << crossPoint.x << ";" << crossPoint.y << ")\n"; 
                crossingPointsInEachAngle[i].push_back(crossPoint);
            }
        }
        cout << "and nothing more\n";
        if(!crossingPointsInEachAngle[i].empty()){
            PointRD positionInDouble(position.x,position.y);
            minDistances[i] = distancePoints(crossingPointsInEachAngle[i].front(),positionInDouble);
            for(auto j = 0; j < crossingPointsInEachAngle[i].size(); j++){
                minDistances[i] = MIN(minDistances[i], distancePoints(crossingPointsInEachAngle[i].at(j),positionInDouble));
            }
        }
        i++;
    }
    return minDistances;
}
