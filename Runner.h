//////////////////////////////////////////////////////////////
// Runner.h - Runner Class Definition                       //
//                                                          //
// While the body parts and the countdown-driven running    //
// and spinning motions of the character may be retained,   //
// its use of a hard-coded path is inappropriate for a      //
// dynamic program in which the character is moving towards //
// a goal that changes each time the program is executed.   //
//////////////////////////////////////////////////////////////

#ifndef RUNNER_H

#include <gl/freeglut.h>
#include <cmath>
#include <iostream>
#include "PathfinderGlobals.h"
#include "Joint.h"
#include "CrossJoint.h"

class Runner 
{
	public:
		Runner();                             // default constructor
		void draw();                          // draw runner to screen
		void Runner::getImageSpacePosition(float pos[]);
		void update();                        // update joint positions
		void init(int curr[], int goal[], int ctdn, GLfloat ori, GLfloat oriGoal, int oriCtdn, int pIndex);
		void reset();                         // set runner's parameters to default values
		void setColor(const float color[]);

		CrossJoint Shoulders;
		CrossJoint Hips;
		Joint      TorsoAndHead;
		Joint      LeftArm[3];         // 0=Humerus, 1=Forearm, 2=Hand
		Joint      RightArm[3];
		Joint      LeftLeg[4];         // 0=Thigh, 1=Shin, 2=Heel, 3=Toe
		Joint      RightLeg[4];

		int        currGridPos[2];
		int        goalGridPos[2];
		int        countdown;
		float      orient;
		float      orientGoal;
		int        orientCountdown;
		int        pathIndex;          // Index of current leg of hard-coded path.
};

void SetMaterialProperties();

#define RUNNER_H
#endif
