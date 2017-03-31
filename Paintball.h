//////////////////////////////////////////////
// Paintball.h - Paintball Class Definition //
//////////////////////////////////////////////

using namespace std;

#ifndef PAINTBALL_H

class Paintball
{
private:
	struct point
	{
		float x;
		float y;
		float z;
	};
	struct droplet
	{
		float dSpin[3];
		float distFromCent;
		float color[3];
		float radius;
	};
	float fallRate;
	float pColor[3];
	point pos;
	float pSpin[3];
	float pCurSpin[3];
	droplet droplets[NBR_DROPLETS];
	void explodeColor(int color, int dropletIndex);
	bool exploded;

public:
	Paintball();
	Paintball(bool exploded);
	Paintball& operator = (const Paintball &p);
	void draw(GLUquadricObj *qObj);
	void increment();
	void getPosition(float pos[]);
	void explode();
	bool getExploded();
	bool incrementExplosion();
	void reset();
	void setPosition(float x, float y, float z);
	void setColor(float r, float g, float b);
};


#define PAINTBALL_H
#endif
