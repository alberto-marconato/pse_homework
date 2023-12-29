#include "boid.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using std::cerr;
using namespace std;

//definitions of parameters used in this library

#define LEFTMARGIN 0 // left margin of the visualizer
#define RIGHTMARGIN 50 // right margin of the visualizer
#define BOTTOMARGIN 0 // boottom margin of the visualizer
#define TOPMARGIN 30 // top margin of the visualizer

#define MAXSPEED 10 // maximum absolute speed of a boid
#define MINSPEED 1 // minimum absolute speed of a boid

#define D_SEP 5
#define D_CA 3

#define AVOIDFACTOR 0.6
#define ALIGNFACTOR 0.6
#define CENTERINGFACTOR 0.7

boid::boid(float x, float y, float vx, float vy)
    :boid_x{x}, boid_y{y}, boid_vx{vx}, boid_vy{vy}
{

    if (boid_x < LEFTMARGIN || boid_x > RIGHTMARGIN || boid_y < BOTTOMARGIN || boid_y > TOPMARGIN )
    {
        cerr << "Error during boid creation: invalid boid positions\n";
		exit(1);
    }

}

const boid& default_boid(){
    static boid b{ LEFTMARGIN, BOTTOMARGIN, 0 , 0 };
    return b;
}

boid::boid()
    :boid_x{default_boid().x()}, boid_y{default_boid().y()}, boid_vx{default_boid().vx()}, boid_vy{default_boid().vy()}
{
    boid_x += static_cast <float> (rand()) / (RAND_MAX/(RIGHTMARGIN-LEFTMARGIN));
    boid_y += static_cast<float> (rand()) / (RAND_MAX/(TOPMARGIN-BOTTOMARGIN));
    float boid_v_abs = MINSPEED +  static_cast <float> ((rand())) / (RAND_MAX / (MAXSPEED - MINSPEED));
    boid_vx += static_cast<float> (2 * rand() - RAND_MAX) / (RAND_MAX / (boid_v_abs));
    float vy_abs = sqrt(boid_v_abs*boid_v_abs - (boid_vx*boid_vx));
    boid_vy += static_cast<float> (2 * vy_abs * signbit(rand() - RAND_MAX) - vy_abs);

    if (sqrt(boid_vx*boid_vx + boid_vy*boid_vy) > MAXSPEED || sqrt(boid_vx*boid_vx + boid_vy*boid_vy) < MINSPEED)
    {
        cerr << "Error during boid creation: invalid boid speed\n";
		exit(1);
    } 
} 

float boid::x() const
{
    return boid_x;
}

float boid::y() const
{
    return boid_y;
}

float boid::vx() const
{
    return boid_vx;
}

float boid::vy() const
{
    return boid_vy;
}

float boid::v_abs() const{
    return sqrt(boid_vx*boid_vx + boid_vy*boid_vy);
}

void boid::move(){ //change position of boid object

    boid_x += boid_vx;
    boid_y += boid_vy;

    checkcoordinates(boid_x , boid_y);
}

float boid::distance(boid& b){ //calculate distance between two boid objects

    float d_x{boid_x - b.x()};
    float d_y{boid_y - b.y()};
    return sqrt(d_x*d_x + d_y*d_y);
}

void boid::separation(vector<boid>& boidarray){ 

    float close_dx{0};   
    float close_dy{0};

     for (auto itr = boidarray.begin(); itr != boidarray.end(); ++itr){ 
        if(distance(*itr) <= D_SEP && distance(*itr) != 0){
            close_dx += boid_x - itr->x();
            close_dy += boid_y - itr->y();   
        }
    }

    boid_vx += close_dx * AVOIDFACTOR;
    boid_vy += close_dy * AVOIDFACTOR;

    checkspeeds(boid_vx, boid_vy);

}

void boid::alignment(vector<boid>& boidarray){
    
    float xvel_avg{0};
    float yvel_avg{0};
    int close_boids{0}; //number of boids with a distance under D_CA

    for (auto itr = boidarray.begin(); itr != boidarray.end(); ++itr){ 
        if(distance(*itr) <= D_CA && distance(*itr) != 0){
             xvel_avg += itr->vx();
             yvel_avg += itr->vy();
             close_boids++;
        }
    }

    if(close_boids > 0){
        xvel_avg = xvel_avg / close_boids;
        yvel_avg = yvel_avg / close_boids;
    }
    

    boid_vx += (xvel_avg - boid_vx)*ALIGNFACTOR;
    boid_vy += (yvel_avg - boid_vy)*ALIGNFACTOR;

    checkspeeds(boid_vx, boid_vy); 

}

void boid::cohesion(vector<boid>& boidarray){

    float xpos_avg{0};
    float ypos_avg{0};
    int close_boids{0};

    for (auto itr = boidarray.begin(); itr != boidarray.end(); ++itr){ 
        if(distance(*itr) <= D_CA && distance(*itr) != 0){
            xpos_avg += itr->x();
            ypos_avg += itr->y();
            close_boids++;
        }
    }

    if(close_boids > 0){
        xpos_avg = xpos_avg / close_boids;
        xpos_avg = xpos_avg / close_boids;
    }
    

    boid_vx += (xpos_avg - boid_x)*CENTERINGFACTOR;
    boid_vy += (ypos_avg - boid_y)*CENTERINGFACTOR; 

    checkspeeds(boid_vx, boid_vy);

}

void boid::checkspeeds(float vx, float vy){
    float abs = v_abs();

    if(v_abs() > MAXSPEED){
        boid_vx = (boid_vx / abs) * MAXSPEED;
        boid_vy = (boid_vy / abs) * MAXSPEED;
    }   
    if(v_abs() < MINSPEED){
        boid_vx = (boid_vx / abs) * MINSPEED;
        boid_vy = (boid_vy / abs) * MINSPEED;
    }
}

void boid::checkcoordinates(float x, float y){

    if(boid_x > RIGHTMARGIN){
        boid_x -= RIGHTMARGIN;
    }
    if(boid_x < LEFTMARGIN){
        boid_x += RIGHTMARGIN;
    }

    if(boid_y > TOPMARGIN){
        boid_y-= TOPMARGIN;
    }   
    if(boid_y < BOTTOMARGIN){
        boid_y += TOPMARGIN;
    }
}

// Operators

ostream& operator<<(ostream& os, const boid& b)
{
	return os << '(' << b.x()
		<< ',' << b.y()
		<< ',' << b.vx() 
        << ',' << b.vy()
        << ',' << b.v_abs() << ')' << endl;
}