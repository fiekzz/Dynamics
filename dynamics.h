#ifndef DYNAMICS_H
#define DYNAMICS_H
#pragma once
#include <cmath>

/* Class of formulas in Mechanics (Dynamics)
    Started since 10 December 2021
    Written by fikri */

// class of formulas
class formula {

private:
    // variables to be returned
    double Time, Range, MaxHeight, Velocity, Height;
    double Vix, Viy, Vfx, Vfy;
    // gravity constant
    const double Gravity = 9.8;
    const double PI = 3.142;

public:
    // projectile motion when given angle, height, velocity
    void P_timeOfFlight(double angle, double height, double velocity);
    void P_range(double angle, double height, double velocity);
    void P_maxHeight(double angle, double height, double velocity);
    void P_finalVelocity(double angle, double height, double velocity);

    // free fall
    void F_Time_Velocity(double iVelocity, double fVelocity);
    void F_Velocity_Time(double iVelocity, double time);
    void F_Height_Velocity(double iVelocity, double fVelocity);
    void F_Time_Height(double iVelocity, double height);
    void F_Velocity_Height(double iVelocity, double height);
    void F_Height_Time(double iVelocity, double time);

    // horizontal projectile motion
    void H_TimeOfFlight(double iHeight, double velocity);
    void H_Range(double iHeight, double velocity);

    // display the data
    double showTime(){
        return Time;
    }
    double showRange(){
        return Range;
    }
    double showMaxHeight(){
        return MaxHeight;
    }
    double showVelocity(){
        return Velocity;
    }
    double showHeight(){
        return Height;
    }
    double showVfx(){
        return Vfx;
    }
    double showVfy(){
        return Vfy;
    }

};

/* ------------- PROJECTILE MOTION ------------- */
// find time
void formula::P_timeOfFlight(double angle, double height, double velocity)
{    
    // t = (Vy + pow(pow(Vy,2) + 2 * G * height),0.5) / G
    angle = (angle * PI) / 180;
    Time = (velocity * sin(angle) + pow(pow(velocity * sin(angle),2) + 2 * Gravity * height,0.5)) / Gravity;
}
// find range
void formula::P_range(double angle, double height, double velocity)
{
    // Rx = Vx * t
    angle = (angle * PI) / 180;
    double velocity_x = velocity * cos(angle);
    double time = (velocity * sin(angle) + pow(pow(velocity * sin(angle),2) + 2 * Gravity * height,0.5)) / Gravity;
    Range = velocity_x * time;
}
// find maximum height
void formula::P_maxHeight(double angle, double height, double velocity)
{
    // Vy = velocity * sin(angle)
    // MaxHeight = initital_height + pow(velocity_y) / (2 * G)
    angle = (angle * PI) / 180;
    double velocity_y = velocity * sin(angle);
    MaxHeight = height + pow(velocity_y,2) / (2 * Gravity);
}

// find final velocity when the object hits the ground
void formula::P_finalVelocity(double angle, double height, double velocity)
{
    double Angle = (angle * PI) / 180;
    Viy = velocity * sin(Angle);

    P_timeOfFlight(angle, height, velocity);

    Vfy = Viy + (-Gravity) * Time;
    Vfx = velocity * cos(Angle);

    Velocity = pow(pow(Vfx,2) + pow(Vfy,2),0.5);
}

/* ------------- FREE FALL ------------- */
// find time given velocity
void formula::F_Time_Velocity(double iVelocity, double fVelocity)
{
    // fVelocity = iVelocity + G * t
    // t = (fVelocity - iVelocity) / G
    Time = (fVelocity - iVelocity) / Gravity;
}
// find velocity given time
void formula::F_Velocity_Time(double iVelocity, double time)
{
    // V = Vo + G * t
    Velocity = iVelocity + Gravity * time;
}
// find height given velocity
void formula::F_Height_Velocity(double iVelocity, double fVelocity)
{
    // fVelocity = iVelocity + G * t
    // t = (fVelocity - iVelocity) / G
    double time = (fVelocity - iVelocity) / Gravity;
    Height = iVelocity * time + 0.5 * 9.8 * time;
}
// find time given height
void formula::F_Time_Height(double iVelocity, double height)
{
    // height = iVelocity * time + 0.5 * 9.8 * pow(time,2)
    // 0.5 * 9.8 * pow(time,2) + iVelocity * time - height = 0
    // root1 = (-b + pow(pow(b,2) - 4 * a * c,0.5)) / (2 * a);
    // root2 = (-b - pow(pow(b,2) - 4 * a * c,0.5)) / (2 * a);
    double time1 = (-iVelocity + pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);
    double time2 = (-iVelocity - pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);

    if(time1 > 0)
        Time = time1;
    else if(time2 > 0)
        Time = time2;
}
// find velocity given height
void formula::F_Velocity_Height(double iVelocity, double height)
{    
    double time1 = (-iVelocity + pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);
    double time2 = (-iVelocity - pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);

    if(time1 > 0)
        Time = time1;
    else if(time2 > 0)
        Time = time2;
    
    // V = Vo + G * t
    Velocity = iVelocity + Gravity * Time;
}
// find height given time
void formula::F_Height_Time(double iVelocity, double time)
{
    Height = iVelocity * time + 0.5 * Gravity * pow(time,2);
}

/* ------------- HORIZONTAL PROJECTILE MOTION ------------- */
// time of flight given initial height and velocity
void formula::H_TimeOfFlight(double iHeight, double velocity)
{
    Time = pow(2 * iHeight / Gravity,0.5);
}
// range of flight given initial height and velocity
void formula::H_Range(double iHeight, double velocity)
{
    double time = pow(2 * iHeight / Gravity,0.5);
    Range = velocity * time;
}

#endif
