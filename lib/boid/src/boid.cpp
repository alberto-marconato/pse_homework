#include "boid.h"

#include <iostream>
#include <math.h>

using std::cerr;

#define LEFTMARGIN 0
#define RIGHTMARGIN 1920
#define BOTTOMARGIN 0
#define TOPMARGIN 1080
#define MAXSPEED 10
#define MINSPEED 2

boid::boid(int x, int y, int vx, int vy)
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
    static boid b{0, 0 , MINSPEED, MINSPEED};
    return b;
}

boid::boid()
    :boid_x{default_boid().x()}, boid_y{default_boid().y()}, boid_vx{default_boid().vx()}, boid_vy{default_boid().vy()}
{
}

int boid::x() const
{
    return boid_x;
}

int boid::y() const
{
    return boid_y;
}

int boid::vx() const
{
    return boid_vx;
}

int boid::vy() const
{
    return boid_vy;
}