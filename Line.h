#ifndef LINE_H
#define	LINE_H
#include <cmath>
#include <math.h>
#include <iostream>

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define SCOLAR_VECTORS(a,b) (((a).x)*((b).x)+((a).y)*((b).y))
#define SCOLAR_POINTS(p1x,p1y,p2x,p2y,p3x,p3y,p4x,p4y) (((p1x)-(p2x))*((p3x)-(p4x)) + ((p1y)-(p2y))*((p3y)-(p4y)))

typedef int Integer;
typedef double Double;
typedef char Char;
typedef std::istream istream;
typedef std::ostream ostream;

template <typename T>
struct Point{
    typedef T Type;
    Integer x;
    Integer y;
public:    
    Point(const T& x = 0, const T& y = 0):x(x),y(y){}
    Point(const Point<T>& orig):x(orig.x),y(orig.y){}
    Point<T> operator = (const Point<T>& orig){
        x = orig.x;
        y = orig.y;
        return *this;
    }
    friend Point<T> operator +(const Point<T>& p1, const Point<T>& p2){
        Point<Type> res(p1.x+p2.x, p1.y+p2.y);
        return res;
    }
    friend Point<T> operator +(const Point<T>& p, const T& val){
        Point<Type> res(p.x+val, p.y+val);
        return res;
    }
    friend Point<T> operator +(const T& val,const Point<T>& p){
        Point<Type> res(p.x+val, p.y+val);
        return res;
    }
    friend Point<T> operator -(const Point<T>& p1, const Point<T>& p2){
        Point<Type> res(p1.x-p2.x,p1.y-p2.y);
        return res;
    }
    friend Point<T> operator -(const Point<T>& p, const T& val){
        Point<Type> res(p.x-val,p.y-val);
        return res;
    }
    friend Point<T> operator -(const T& val, const Point<T>& p){
        Point<Type> res(val-p.x,val-p.y);
        return res;
    }
    friend T operator *(const Point<T>& p1, const Point<T>& p2){
        return p1.x*p2.x+p1.y*p2.y;
    }
    friend Point<T> operator*(const Point<T>& p, const T& val){
        Point<Type> res(p.x*val,p.y*val);
        return res;
    }
    friend Point<T> operator*(const T& val,const Point<T>& p){
        Point<Type> res(p.x*val,p.y*val);
        return res;
    }
    friend Double distancePoints(const Point<T>& p1, const Point<T>& p2){
        return pow(pow(p1.x-p2.x,2.0)+pow(p1.y-p2.y,2.0),0.5);
    }
    
    friend istream& operator >> (istream& input, Point<T>& pt){
        input >> pt.x >> pt.y;
        return input;
    }
    
    friend bool operator == (const Point<T>& p1, const Point<T>& p2){
        return p1.x==p2.x && p1.y==p2.y;
    }
    friend bool operator != (const Point<T>& p1, const Point<T>& p2){
        return !(p1 == p2);
    }
    friend ostream& operator << (ostream& output, Point<T>& p){
        output << "(" << p.x << ";" << p.y << ")";
        return output;
    }
};

template <typename T>
struct Line{
    typedef Point<T> Pt;
    Pt p1;
    Pt p2;
private:
    bool verticalLine;
    Double k;
    Double b;
public:
    Line(const Point<T>& p1 = 0,const Point<T>& p2 = 0):p1(p1),p2(p2),verticalLine(p1.x == p2.x){
        k = b = 0.0;
        if(!verticalLine){
            k = Double(p2.y-p1.y)/Double(p2.x-p1.x);
            b = p1.y - k*p1.x;
        }
    }
    Line(const Line<T>& orig):p1(orig.p1),p2(orig.p2),verticalLine(orig.verticalLine),k(orig.k),b(orig.b){}
    Line<T> operator =(const Line<T>& l){
        p1 = l.p1;
        p2 = l.p2;
        verticalLine = l.verticalLine;
        k = l.k;
        b = l.b;
    }
    
    
    
    void RecalcKoef(){
        k = b = 0;
        if(p1.x == p2.x){
            verticalLine = true;
            return;
        }
        verticalLine = false;
        k = Double(p2.y-p1.y)/Double(p2.x-p1.x);
        b = p1.y - k*p1.x;
    }
    
    bool isVertical(){
        RecalcKoef();
        return verticalLine;
    }
    
    friend Double DistanceToLineSegment(const Point<T>& p, const Line<T>& segment){
        auto d = abs(segment.k*p.x-p.y+segment.b)/sqrt(pow(segment.k,2.0)+1);
        Pt v1 = p - segment.p1;
        Pt v2 = segment.p2 - segment.p1;
        
        Pt u1 = p - segment.p2;
        Pt u2 = segment.p1 - segment.p2;
        
        if((v1*v2)*(u1*u2) > 0)
            return d;
        return MIN(distancePoints(p,segment.p1),distancePoints(p,segment.p2));
    }
    friend bool LineCros(Line<T> l1, Line<T> l2, Point<Double>& cross){
        if(l1.isVertical() && l2.isVertical()){
            if(l1.p1.x == l2.p1.x)
                return true;
            return false;
        }
        if(l1.isVertical()){
            cross.x = l1.p1.x;
            cross.y = l2.k*cross.x+l2.b;
            return true;
        }
        if(l2.isVertical()){
            cross.x = l2.p1.x;
            cross.y = l1.k*cross.x+l1.b;
        }
        if(l1.k == l2.k){
            if(l1.b == l2.b)
                return true;
            return false;
        }
        auto x = Double(l2.b-l1.b)/Double(l1.k-l2.k);
        auto y = l1.k*x+l1.b;
        cross.x = x;
        cross.y = y;
        return true;
    }
    bool Contains(const Point<T>& p){
        return (p-p1)*(p-p2) <= 0;
        //return SCOLAR_POINTS(p.x,p.y,p1.x,p1.y,p.x,p.y,p2.x,p2.y) <=0;
    }
    bool RayCrossLineSegment(Line<T> segment, Point<Double>& cross){
        Point<Double> crossWithAllLine;
        if(!LineCros(*this,segment,crossWithAllLine)) //если луч с прямой не пересекается
            return false;
        if(segment.isVertical() && this->isVertical() || segment.k == this->k){  //если прямые совпадают друг с другом
            if(distancePoints(p1, segment.p1) < distancePoints(p1,segment.p2)){
                cross.x = segment.p1.x;
                cross.y = segment.p1.y;
            }
            else{
                cross.x = segment.p2.x;
                cross.y = segment.p2.y;
            }
            return true;
        }
        Point<Double> p1D(p1.x,p1.y);
        Point<Double> p2D(p2.x,p2.y);
        //if(SCOLAR_POINTS(crossWithAllLine.x,crossWithAllLine.y,p1.x,p1.y,p2.x,p2.y,p1.x,p1.y) < 0)
        if((crossWithAllLine-p1D)*(p2D-p1D) < 0) // если точка в обратной стороне луча
            return false;
        Line<Double> segmentD(Point<Double>(segment.p1.x,segment.p1.y),Point<Double>(segment.p2.x,segment.p2.y));
        if(!segmentD.Contains(crossWithAllLine)) // если точка не принадлежит отрезку
            return false;
        cross = crossWithAllLine;
        return true;
    }
    Double& GetK(){
        RecalcKoef();
        return k;
    }
    Double& GetB(){
        RecalcKoef();
        return b;
    }
    friend ostream& operator << (ostream& output, Line<T>& l){
        output << l.p1 << "--" << l.p2;
        return output;
    }
};

#endif	/* LINE_H */

