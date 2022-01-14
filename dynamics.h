#ifndef DYNAMICS_H
#define DYNAMICS_H
#pragma once
#include <cmath>

/* Class of formulas in Mechanics (Dynamics)
    Started since 10 December 2021
    Written by group 4 section 6 eece 1313 */

// # The formulas written are resorted according to the kinematics equation in the dynamics part
// # Angle inputs are in degree
// # All the calculations are assumed that there are no friction and aerodynamics forces

/*  LIST OF THE KINEMATICS EQUATIONS

    V = Vi + at 
    S = S0 + V0t + 0.5at^2
    V^2 = V0^2 + 2a(S - S0)

    // a is constant

*/

// fikri
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
    // rime of flight
    void P_timeOfFlight(double angle, double height, double velocity);
    // range of flight
    void P_range(double angle, double height, double velocity);
    // max height of flight
    void P_maxHeight(double angle, double height, double velocity);
    // final velocity of flight
    void P_finalVelocity(double angle, double height, double velocity);

    // free fall
    // find time when given velocity
    void F_Time_Velocity(double iVelocity, double fVelocity);
    // find velocity when given time
    void F_Velocity_Time(double iVelocity, double time);
    // find height when given velocity
    void F_Height_Velocity(double iVelocity, double fVelocity);
    // find time when given height
    void F_Time_Height(double iVelocity, double height);
    // find velocity when given height
    void F_Velocity_Height(double iVelocity, double height);
    // find height when given time
    void F_Height_Time(double iVelocity, double time);

    // horizontal projectile motion
    // find the time of flight
    void H_TimeOfFlight(double iHeight, double velocity);
    // find the range of flight
    void H_Range(double iHeight, double velocity);

    // display the data
    // show time
    double showTime(){
        return Time;
    }
    // show range
    double showRange(){
        return Range;
    }
    // show max height
    double showMaxHeight(){
        return MaxHeight;
    }
    // show velocity
    double showVelocity(){
        return Velocity;
    }
    // show height
    double showHeight(){
        return Height;
    }
    // show final velocity in x component
    double showVfx(){
        return Vfx;
    }
    // show final velocity in y component
    double showVfy(){
        return Vfy;
    }

};

/* ------------- PROJECTILE MOTION ------------- */
// find time
void formula::P_timeOfFlight(double angle, double height, double velocity)
{    
    // t = (Vy + pow(pow(Vy,2) + 2 * G * height),0.5) / G
    // change the angle from degree to radian
    angle = (angle * PI) / 180;
    // get the time of flight
    Time = (velocity * sin(angle) + pow(pow(velocity * sin(angle),2) + 2 * Gravity * height,0.5)) / Gravity;
}
// find range
void formula::P_range(double angle, double height, double velocity)
{
    // Rx = Vx * t
    // change the angle from degree to radian
    angle = (angle * PI) / 180;
    // find the velocity in x component
    double velocity_x = velocity * cos(angle);
    // get the time from the kinematics equations
    double time = (velocity * sin(angle) + pow(pow(velocity * sin(angle),2) + 2 * Gravity * height,0.5)) / Gravity;
    // find the range of flight
    Range = velocity_x * time;
}
// find maximum height
void formula::P_maxHeight(double angle, double height, double velocity)
{
    // Vy = velocity * sin(angle)
    // MaxHeight = initital_height + pow(velocity_y) / (2 * G)
    // change the angle from degree to radian
    angle = (angle * PI) / 180;
    // find velocity in y component
    double velocity_y = velocity * sin(angle);
    // use the formula to get the max height of the flight
    MaxHeight = height + pow(velocity_y,2) / (2 * Gravity);
}

// find final velocity when the object hits the ground
void formula::P_finalVelocity(double angle, double height, double velocity)
{
    // change the angle from degree to radian
    double Angle = (angle * PI) / 180;
    // find initial velocity in y component
    Viy = velocity * sin(Angle);

    // get the time of flight
    P_timeOfFlight(angle, height, velocity);

    // use kinematics equations to find the final velocities of x and y components
    Vfy = Viy + (-Gravity) * Time;
    Vfx = velocity * cos(Angle);

    // get the magnitude of velocity
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
    // determine the time of flight
    double time1 = (-iVelocity + pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);
    double time2 = (-iVelocity - pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);

    // determine whether the time is positive or negative
    // the Time will be chosen if it is in positive form
    if(time1 > 0)
        Time = time1;
    else if(time2 > 0)
        Time = time2;
}
// find velocity given height
void formula::F_Velocity_Height(double iVelocity, double height)
{    
    // determine the time of flight
    double time1 = (-iVelocity + pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);
    double time2 = (-iVelocity - pow(pow(iVelocity,2) - 4 * Gravity * 0.5 * height * -1,0.5)) / (2 * Gravity * 0.5);

    // determine whether the time is positive or negative
    // the Time will be chosen if it is in positive form
    if(time1 > 0)
        Time = time1;
    else if(time2 > 0)
        Time = time2;
    
    // V = Vo + G * t
    // find the velocity
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
    // find time
    Time = pow(2 * iHeight / Gravity,0.5);
}
// range of flight given initial height and velocity
void formula::H_Range(double iHeight, double velocity)
{
    // find time
    double time = pow(2 * iHeight / Gravity,0.5);
    // get range
    Range = velocity * time;
}

#endif
