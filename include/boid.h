#ifndef BOID_H
#define BOID_H

#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class boid{
private:
    float boid_x;  //X component of the boid position 
    float boid_y;  //Y component of the boid position 
    float boid_vx; //X component of the boid velocity 
    float boid_vy; //Y component of the boid velocity 

    void checkspeeds(float vx, float vy);
    void checkcoordinates(float x, float y);
public:

    //constructors
    boid(float x, float y, float vx, float vy);
    boid(); 

    float x() const; //return boid_x
    float y() const; //return boid_y
    float vx() const; //return boid_vx
    float vy() const; //return boid_vy
    float v_abs() const; //return the absolute speed of the boid

    void move(); //move the boid throug the screen
    float distance(boid& b); //calclulate the distance from another boid

    void separation(vector<boid>& boidarray);
    void alignment(vector<boid>& boidarray);
    void cohesion(vector<boid>& boidarray);

};

// Operators
std::ostream& operator<<(std::ostream& os, const boid& b);



#endif