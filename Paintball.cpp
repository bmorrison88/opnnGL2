////////////////////////////////////////////////////
// Paintball.cpp - Paintball Class Implementation //
////////////////////////////////////////////////////

//#include <cstdlib>
#include <gl/freeglut.h>
#include <cmath>
#include "PathfinderGlobals.h"
#include "Paintball.h"

using namespace std;

//Assignment operator
Paintball& Paintball::operator = (const Paintball &p)
{
	for (int i = 0; i < NBR_DROPLETS; i++)
	{
		droplets[i].dSpin[0] = p.droplets[i].dSpin[0];
		droplets[i].dSpin[1] = p.droplets[i].dSpin[1];
		droplets[i].dSpin[2] = p.droplets[i].dSpin[2];
		droplets[i].color[0] = p.droplets[i].color[0];
		droplets[i].color[1] = p.droplets[i].color[1];
		droplets[i].color[2] = p.droplets[i].color[2];
		droplets[i].distFromCent = p.droplets[i].distFromCent;
		droplets[i].radius = p.droplets[i].radius;
	}
	exploded = p.exploded;
	pCurSpin[0] = p.pCurSpin[0];
	pCurSpin[1] = p.pCurSpin[1];
	pCurSpin[2] = p.pCurSpin[2];
	pSpin[0] = p.pSpin[0];
	pSpin[1] = p.pSpin[1];
	pSpin[2] = p.pSpin[2];
	pos = p.pos;
	return*this;
}

Paintball::Paintball()
{}

//Overloaded constructor 
Paintball::Paintball(bool exploded)
{
	for (int i = 0; i < NBR_DROPLETS; i++)
	{
		droplets[i].dSpin[0] = rand() % (90 - DROPLET_LIMIT_ROT) + DROPLET_LIMIT_ROT + 180;
		droplets[i].dSpin[1] = rand() % DROPLET_ROT_MOD;
		droplets[i].distFromCent = (rand() % PAINTBALL_RAD_MOD) / 100.0;
		droplets[i].radius = DROPLET_RAD;
	}
	pos.x = GOAL_POS[0];
	pos.y = GOAL_POS[1];
	pos.z = GOAL_POS[2];
	pSpin[0] = (rand() % PAINTBALL_ROT_MOD);
	pSpin[1] = (rand() % PAINTBALL_ROT_MOD);
	pSpin[2] = (rand() % PAINTBALL_ROT_MOD);
	pCurSpin[0] = 0.0;
	pCurSpin[1] = 0.0;
	pCurSpin[2] = 0.0;
	pColor[0] = 1.0;
	pColor[1] = 0.0;
	pColor[2] = 0.0;
	Paintball::exploded = exploded;
}

// Position mutator
void Paintball::setPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

// Draws the paintball
void Paintball::draw(GLUquadricObj *qObj)
{
	gluQuadricDrawStyle(qObj, GLU_SMOOTH);
	if (pos.z > FAR_CLIP)
	{
		for (int i = 0; i < NBR_DROPLETS; i++)
		{
			glPushMatrix();
			glTranslatef(pos.x, pos.y, pos.z);
			glPushMatrix();
			glRotatef(droplets[i].dSpin[2], 0.0, 0.0, 1.0);
			glRotatef(droplets[i].dSpin[1], 0.0, 1.0, 0.0);
			glRotatef(droplets[i].dSpin[0], 1.0, 0.0, 0.0);
			glTranslatef(0.0, 0.0, droplets[i].distFromCent);
			glColor3f(pColor[0], pColor[1], pColor[2]);
			gluSphere(qObj, droplets[i].radius, 16, 16);
			glPopMatrix();
			glPopMatrix();
		}
	}
}

// Moves the droplets outward in the explosion and updates their color.
bool Paintball::incrementExplosion()
{
	bool ret = true;

	for (int i = 0; i < NBR_DROPLETS; i++)
	{

		droplets[i].distFromCent += .005f / droplets[i].distFromCent + .1f;
		explodeColor(0, i);
		explodeColor(1, i);
		explodeColor(2, i);
		if (droplets[i].distFromCent > 5 && droplets[i].distFromCent < 10)
			ret = false;
	}
	fallRate += .005f;
	pos.y -= fallRate;
	return ret;

}

// Changes the color in an explosion
void Paintball::explodeColor(int color, int dropletIndex)
{
	if (color < 2)
	{
		if (droplets[dropletIndex].color[color] + EXPLOSION_CONST > 1)
			droplets[dropletIndex].color[color] = 1;
		else
			droplets[dropletIndex].color[color] += EXPLOSION_CONST;
	}
	else
	{
		if (droplets[dropletIndex].color[color] - EXPLOSION_CONST < 0)
			droplets[dropletIndex].color[color] = 0;
		else
			droplets[dropletIndex].color[color] -= EXPLOSION_CONST;
	}

}

// Returns the exploded boolean
bool Paintball::getExploded()
{
	return exploded;
}

// Returns the position of the molecule
void Paintball::getPosition(float pos[])
{
	pos[0] = Paintball::pos.x;
	pos[1] = Paintball::pos.y;
	pos[2] = Paintball::pos.z;
}

// Sets the exploded boolean to true
void Paintball::explode()
{
	exploded = true;
}

// moves and rotates the Paintball slightly for animation purposes
void Paintball::increment()
{
	if (pos.z < 1.0)
	{
		pCurSpin[0] += pSpin[0];
		pCurSpin[1] += pSpin[1];
	}
	else
		reset();
}

// Resets the Paintball
void Paintball::reset()
{
	for (int i = 0; i < NBR_DROPLETS; i++)
	{
		droplets[i].dSpin[0] = rand() % (90 - DROPLET_LIMIT_ROT) + DROPLET_LIMIT_ROT + 180;
		droplets[i].dSpin[1] = rand() % DROPLET_ROT_MOD;
		droplets[i].distFromCent = (rand() % PAINTBALL_RAD_MOD) / 100.0;
		droplets[i].radius = DROPLET_RAD;
		droplets[i].color[0] = (rand() % COLOR_RANGE + COLOR_INTENSITY) / 100.0;
		droplets[i].color[1] = (rand() % COLOR_RANGE + COLOR_INTENSITY) / 100.0;
		droplets[i].color[2] = (rand() % COLOR_RANGE + COLOR_INTENSITY) / 100.0;
	}
	fallRate = 0;
	pos.x = GOAL_POS[0];
	pos.y = GOAL_POS[1];
	pos.z = GOAL_POS[2];
	pSpin[0] = (rand() % PAINTBALL_ROT_MOD);
	pSpin[1] = (rand() % PAINTBALL_ROT_MOD);
	pSpin[2] = (rand() % PAINTBALL_ROT_MOD);
	pCurSpin[0] = 0.0;
	pCurSpin[1] = 0.0;
	pCurSpin[2] = 0.0;
	exploded = false;
}

void Paintball::setColor(float r, float g, float b)
{
	pColor[0] = r;
	pColor[1] = g;
	pColor[2] = b;
}