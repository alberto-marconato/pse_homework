#include "boid.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using std::cerr;
using namespace std;

#define LEFTMARGIN 0
#define RIGHTMARGIN 1920
#define BOTTOMARGIN 0
#define TOPMARGIN 1080
#define MAXSPEED 10
#define MINSPEED 2
#define D_SEP 5
#define D_CA 3
#define AVOIDFACTOR 0.7
#define ALIGNFACTOR 0.2
#define CENTERINGFACTOR 0.5

boid::boid(float x, float y, float vx, float vy)
    :boid_x{x}, boid_y{y}, boid_vx{vx}, boid_vy{vy}
{

    if (boid_x < LEFTMARGIN || boid_x > RIGHTMARGIN || boid_y < BOTTOMARGIN || boid_y > TOPMARGIN )
    {
        cerr << "invalid boid positions\n";
		exit(1);
    }

    if (sqrt(boid_vx*boid_vx + boid_vy*boid_vy) > MAXSPEED || sqrt(boid_vx*boid_vx + boid_vy*boid_vy) < MINSPEED)
    {
        cerr << "invalid boid speed\n";
		exit(1);
    }  

}

const boid& default_boid(){
    float random_x = LEFTMARGIN + static_cast <float> (rand()) /( static_cast <float> (RIGHTMARGIN/(RIGHTMARGIN-LEFTMARGIN)));
    float random_y = BOTTOMARGIN + static_cast <float> (rand()) /( static_cast <float> (TOPMARGIN/(TOPMARGIN-BOTTOMARGIN)));
    static boid b{ random_x , random_y , MINSPEED, MINSPEED};
    return b;
}

boid::boid()
    :boid_x{default_boid().x()}, boid_y{default_boid().y()}, boid_vx{default_boid().vx()}, boid_vy{default_boid().vy()}
{
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

void boid::move(){ //change position of boid object
    boid_x += boid_vx;

    if(boid_x > RIGHTMARGIN){
        boid_x -= RIGHTMARGIN;
    }
    if(boid_x < LEFTMARGIN){
        boid_y += RIGHTMARGIN;
    }

    boid_y += boid_vy;

    if(boid_y > TOPMARGIN){
        boid_y-= TOPMARGIN;
    }   
    if(boid_y < BOTTOMARGIN){
        boid_y += TOPMARGIN;
    }
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
        if(distance(*itr) <= D_SEP){
            close_dx += boid_x - itr->x();
            close_dy += boid_y - itr->y();   
        }
    }

    boid_vx += close_dx * AVOIDFACTOR;
    boid_vy += close_dy * AVOIDFACTOR;

}

void boid::alignment(vector<boid>& boidarray){
    
    float xvel_avg{0};
    float yvel_avg{0};
    int close_boids{0}; //number of boids with a distance under D_CA

    for (auto itr = boidarray.begin(); itr != boidarray.end(); ++itr){ 
        if(distance(*itr) <= D_CA){
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

}

void boid::cohesion(vector<boid>& boidarray){

    float xpos_avg{0};
    float ypos_avg{0};
    int close_boids{0};

    for (auto itr = boidarray.begin(); itr != boidarray.end(); ++itr){ 
        if(distance(*itr) <= D_CA){
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
}