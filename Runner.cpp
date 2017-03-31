//////////////////////////////////////////////
// Runner.cpp - Runner Class Implementation //
//////////////////////////////////////////////

#include "Runner.h"

// Default Constructor
Runner::Runner()
{
	reset();
}

// Initialize the Runner's data members to the parameterized values.
void Runner::init(int curr[], int goal[], int ctdn, float ori, float oriGoal, int oriCtdn, int pIndex)
{
	reset();
	for (int i = 0; i < 2; i++)
	{
		currGridPos[i] = curr[i];
		goalGridPos[i] = goal[i];
	}
	countdown = ctdn;
	orient = ori;
	orientGoal = oriGoal;
	orientCountdown = oriCtdn;
	pathIndex = pIndex;
	setColor(COLORS[0]);
}

// Reset Runner to default values
void Runner::reset()
{
	// Initialize Torso and Head "joint"
	TorsoAndHead.initialize(TORSO_AND_HEAD_SPHERE_RADIUS, TORSO_AND_HEAD_SPHERE_CENTER, TORSO_AND_HEAD_SPHERE_COLOR,
		TORSO_AND_HEAD_CYLINDER_RADIUS, TORSO_AND_HEAD_CYLINDER_LENGTH, TORSO_AND_HEAD_CYLINDER_COLOR,
		TORSO_AND_HEAD_MIN_PITCH, TORSO_AND_HEAD_MIN_PITCH, TORSO_AND_HEAD_MAX_PITCH, TORSO_AND_HEAD_PITCH_INCREMENT);

	// Initialize Shoulders
	Shoulders.initialize(SHOULDERS_SPHERE_RADIUS, SHOULDERS_SPHERE_CENTER, SHOULDERS_SPHERE_COLOR,
		SHOULDERS_CYLINDER_RADIUS, SHOULDERS_CYLINDER_LENGTH, SHOULDERS_CYLINDER_COLOR,
		SHOULDERS_ROLL, SHOULDERS_MIN_ROLL, SHOULDERS_MAX_ROLL, -SHOULDERS_ROLL_INCREMENT,
		SHOULDERS_YAW, SHOULDERS_MIN_YAW, SHOULDERS_MAX_YAW, SHOULDERS_YAW_INCREMENT);

	// Initialize Humeruses
	LeftArm[0].initialize(HUMERUS_SPHERE_RADIUS, HUMERUS_SPHERE_CENTER, HUMERUS_SPHERE_COLOR,
		HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH, HUMERUS_CYLINDER_COLOR,
		HUMERUS_MIN_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, HUMERUS_PITCH_INCREMENT);
	RightArm[0].initialize(HUMERUS_SPHERE_RADIUS, HUMERUS_SPHERE_CENTER, HUMERUS_SPHERE_COLOR,
		HUMERUS_CYLINDER_RADIUS, HUMERUS_CYLINDER_LENGTH, HUMERUS_CYLINDER_COLOR,
		HUMERUS_MAX_PITCH, HUMERUS_MIN_PITCH, HUMERUS_MAX_PITCH, -HUMERUS_PITCH_INCREMENT);

	// Initialize Forearms
	LeftArm[1].initialize(FOREARM_SPHERE_RADIUS, FOREARM_SPHERE_CENTER, FOREARM_SPHERE_COLOR,
		FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH, FOREARM_CYLINDER_COLOR,
		FOREARM_MIN_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, -FOREARM_PITCH_INCREMENT);
	RightArm[1].initialize(FOREARM_SPHERE_RADIUS, FOREARM_SPHERE_CENTER, FOREARM_SPHERE_COLOR,
		FOREARM_CYLINDER_RADIUS, FOREARM_CYLINDER_LENGTH, FOREARM_CYLINDER_COLOR,
		FOREARM_MAX_PITCH, FOREARM_MIN_PITCH, FOREARM_MAX_PITCH, FOREARM_PITCH_INCREMENT);

	LeftArm[2].initialize(HAND_SPHERE_RADIUS, HAND_SPHERE_CENTER, HAND_SPHERE_COLOR,
		HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH, HAND_CYLINDER_COLOR,
		HAND_MIN_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, -HAND_PITCH_INCREMENT);
	RightArm[2].initialize(HAND_SPHERE_RADIUS, HAND_SPHERE_CENTER, HAND_SPHERE_COLOR,
		HAND_CYLINDER_RADIUS, HAND_CYLINDER_LENGTH, HAND_CYLINDER_COLOR,
		HAND_MAX_PITCH, HAND_MIN_PITCH, HAND_MAX_PITCH, HAND_PITCH_INCREMENT);

	// Initialize Hips
	Hips.initialize(HIPS_SPHERE_RADIUS, HIPS_SPHERE_CENTER, HIPS_SPHERE_COLOR,
		HIPS_CYLINDER_RADIUS, HIPS_CYLINDER_LENGTH, HIPS_CYLINDER_COLOR,
		HIPS_ROLL, HIPS_MIN_ROLL, HIPS_MAX_ROLL, -HIPS_ROLL_INCREMENT,
		HIPS_YAW, HIPS_MIN_YAW, HIPS_MAX_YAW, HIPS_YAW_INCREMENT);

	// Initialize Thighs
	LeftLeg[0].initialize(THIGH_SPHERE_RADIUS, THIGH_SPHERE_CENTER, THIGH_SPHERE_COLOR,
		THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH, THIGH_CYLINDER_COLOR,
		THIGH_MIN_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, THIGH_PITCH_INCREMENT);
	RightLeg[0].initialize(THIGH_SPHERE_RADIUS, THIGH_SPHERE_CENTER, THIGH_SPHERE_COLOR,
		THIGH_CYLINDER_RADIUS, THIGH_CYLINDER_LENGTH, THIGH_CYLINDER_COLOR,
		THIGH_MAX_PITCH, THIGH_MIN_PITCH, THIGH_MAX_PITCH, -THIGH_PITCH_INCREMENT);
	// Initialize Shins
	LeftLeg[1].initialize(SHIN_SPHERE_RADIUS, SHIN_SPHERE_CENTER, SHIN_SPHERE_COLOR,
		SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH, SHIN_CYLINDER_COLOR,
		SHIN_MIN_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, -SHIN_PITCH_INCREMENT);
	RightLeg[1].initialize(SHIN_SPHERE_RADIUS, SHIN_SPHERE_CENTER, SHIN_SPHERE_COLOR,
		SHIN_CYLINDER_RADIUS, SHIN_CYLINDER_LENGTH, SHIN_CYLINDER_COLOR,
		SHIN_MAX_PITCH, SHIN_MIN_PITCH, SHIN_MAX_PITCH, SHIN_PITCH_INCREMENT);
	// Initialize Heels
	LeftLeg[2].initialize(HEEL_SPHERE_RADIUS, HEEL_SPHERE_CENTER, HEEL_SPHERE_COLOR,
		HEEL_CYLINDER_RADIUS, HEEL_CYLINDER_LENGTH, HEEL_CYLINDER_COLOR,
		HEEL_MIN_PITCH, HEEL_MIN_PITCH, HEEL_MAX_PITCH, HEEL_PITCH_INCREMENT);
	RightLeg[2].initialize(HEEL_SPHERE_RADIUS, HEEL_SPHERE_CENTER, HEEL_SPHERE_COLOR,
		HEEL_CYLINDER_RADIUS, HEEL_CYLINDER_LENGTH, HEEL_CYLINDER_COLOR,
		HEEL_MAX_PITCH, HEEL_MIN_PITCH, HEEL_MAX_PITCH, -HEEL_PITCH_INCREMENT);
	// Initialize Toes
	LeftLeg[3].initialize(TOE_SPHERE_RADIUS, TOE_SPHERE_CENTER, TOE_SPHERE_COLOR,
		TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH, TOE_CYLINDER_COLOR,
		TOE_MIN_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, TOE_PITCH_INCREMENT);
	RightLeg[3].initialize(TOE_SPHERE_RADIUS, TOE_SPHERE_CENTER, TOE_SPHERE_COLOR,
		TOE_CYLINDER_RADIUS, TOE_CYLINDER_LENGTH, TOE_CYLINDER_COLOR,
		TOE_MAX_PITCH, TOE_MIN_PITCH, TOE_MAX_PITCH, -TOE_PITCH_INCREMENT);
}

// Set all body parts of runner to parameterized color.
void Runner::setColor(const float color[])
{
	float c[3];
	c[0] = color[0];
	c[1] = color[1];
	c[2] = color[2];
	RightLeg[0].setSphereColor(c);
	RightLeg[1].setSphereColor(c);
	RightLeg[2].setSphereColor(c);
	RightLeg[3].setSphereColor(c);
	LeftLeg[0].setSphereColor(c);
	LeftLeg[1].setSphereColor(c);
	LeftLeg[2].setSphereColor(c);
	LeftLeg[3].setSphereColor(c);
	TorsoAndHead.setSphereColor(c);
	TorsoAndHead.setCylinderColor(c);
	Hips.setSphereColor(c);
	Shoulders.setSphereColor(c);
	RightArm[0].setSphereColor(c);
	RightArm[1].setSphereColor(c);
	RightArm[2].setSphereColor(c);
	LeftArm[0].setSphereColor(c);
	LeftArm[1].setSphereColor(c);
	LeftArm[2].setSphereColor(c);
}

// Set up the quadric object to display the graphical components of the Runner.
void Runner::draw()
{
	float offset[3];
	float pos[3];
	float spin;
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);

	pos[1] = CHARACTER_ELEVATION;
	if ((currGridPos[0] == goalGridPos[0]) || (currGridPos[1] == goalGridPos[1]))
	{
		pos[0] = ((countdown * currGridPos[0] + (REGULAR_COUNTDOWN_MAX - countdown) * goalGridPos[0]) /
			float(REGULAR_COUNTDOWN_MAX) + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
		pos[2] = ((countdown * currGridPos[1] + (REGULAR_COUNTDOWN_MAX - countdown) * goalGridPos[1]) /
			float(REGULAR_COUNTDOWN_MAX) + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	}
	else
	{
		pos[0] = ((countdown * currGridPos[0] + (DIAGONAL_COUNTDOWN_MAX - countdown) * goalGridPos[0]) /
			float(DIAGONAL_COUNTDOWN_MAX) + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
		pos[2] = ((countdown * currGridPos[1] + (DIAGONAL_COUNTDOWN_MAX - countdown) * goalGridPos[1]) /
			float(DIAGONAL_COUNTDOWN_MAX) + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	}
	if (orientCountdown == 0)
		spin = orient;
	else
		spin = (orientCountdown * orient + (SPIN_COUNTDOWN_MAX - orientCountdown) * orientGoal) /
		float(SPIN_COUNTDOWN_MAX);

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glTranslatef(pos[0], pos[1], pos[2]);

	glRotatef(spin, 0, 1, 0);

	Hips.getSphereCenter(offset);
	glTranslatef(offset[0], offset[1], offset[2]);
	glPushMatrix();
	glRotatef(Hips.getCurrentYaw(), 0.0, 1.0, 0.0);
	glRotatef(Hips.getCurrentRoll(), 0.0, 0.0, 1.0);
	Hips.draw(qObj);

	glPushMatrix();
	glTranslatef(0.0, TorsoAndHead.getCylinderLength(), 0.0);
	TorsoAndHead.draw(qObj);
	glPopMatrix();

	glPushMatrix();
	Shoulders.getSphereCenter(offset);
	glTranslatef(offset[0], offset[1], offset[2]);
	glPushMatrix();
	glRotatef(Shoulders.getCurrentYaw(), 0.0, 1.0, 0.0);
	glRotatef(Shoulders.getCurrentRoll(), 0.0, 0.0, 1.0);

	Shoulders.draw(qObj);

	glRotatef(180.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(Shoulders.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(LeftArm[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftArm[0].draw(qObj);
	glTranslatef(0.0, -LeftArm[0].getCylinderLength(), 0.0);
	glRotatef(LeftArm[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftArm[1].draw(qObj);
	glTranslatef(0.0, -LeftArm[1].getCylinderLength(), 0.0);
	LeftArm[2].draw(qObj);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-Shoulders.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(RightArm[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightArm[0].draw(qObj);
	glTranslatef(0.0, -RightArm[0].getCylinderLength(), 0.0);
	glRotatef(RightArm[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightArm[1].draw(qObj);
	glTranslatef(0.0, -RightArm[1].getCylinderLength(), 0.0);
	RightArm[2].draw(qObj);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(Hips.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(LeftLeg[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftLeg[0].draw(qObj);
	glTranslatef(0.0, -LeftLeg[0].getCylinderLength(), 0.0);
	glRotatef(LeftLeg[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftLeg[1].draw(qObj);
	glTranslatef(0.0, -LeftLeg[1].getCylinderLength(), 0.0);
	glRotatef(LeftLeg[2].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftLeg[2].draw(qObj);
	glTranslatef(0.0, -LeftLeg[2].getCylinderLength(), 0.0);
	glRotatef(LeftLeg[3].getCurrentPitch(), 1.0, 0.0, 0.0);
	LeftLeg[3].draw(qObj);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-Hips.getCylinderLength() / 2, 0.0, 0.0);
	glRotatef(RightLeg[0].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightLeg[0].draw(qObj);
	glTranslatef(0.0, -RightLeg[0].getCylinderLength(), 0.0);
	glRotatef(RightLeg[1].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightLeg[1].draw(qObj);
	glTranslatef(0.0, -RightLeg[1].getCylinderLength(), 0.0);
	glRotatef(RightLeg[2].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightLeg[2].draw(qObj);
	glTranslatef(0.0, -RightLeg[2].getCylinderLength(), 0.0);
	glRotatef(RightLeg[3].getCurrentPitch(), 1.0, 0.0, 0.0);
	RightLeg[3].draw(qObj);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(qObj);
	glColor3f(1, 1, 1);
}

// Return current location of Runner in 2-D image space coordinates.
void Runner::getImageSpacePosition(float pos[])
{
	if ((currGridPos[0] == goalGridPos[0]) || (currGridPos[1] == goalGridPos[1]))
	{
		pos[0] = ((countdown * currGridPos[0] + (REGULAR_COUNTDOWN_MAX - countdown) * goalGridPos[0]) /
			float(REGULAR_COUNTDOWN_MAX) + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
		pos[1] = ((countdown * currGridPos[1] + (REGULAR_COUNTDOWN_MAX - countdown) * goalGridPos[1]) /
			float(REGULAR_COUNTDOWN_MAX) + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	}
	else
	{
		pos[0] = ((countdown * currGridPos[0] + (DIAGONAL_COUNTDOWN_MAX - countdown) * goalGridPos[0]) /
			float(DIAGONAL_COUNTDOWN_MAX) + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
		pos[1] = ((countdown * currGridPos[1] + (DIAGONAL_COUNTDOWN_MAX - countdown) * goalGridPos[1]) /
			float(DIAGONAL_COUNTDOWN_MAX) + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	}
}

// Update the positions and orientations associated
// with the joints and cross-joints of the Runner.
void Runner::update()
{
	/***********************************************************/
	/* THE CODE IN THIS BLOCK ASSUMES THAT THE RUNNER FOLLOWS  */
	/* A HARD-CODED PATH. IT MUST BE ELIMINATED TO ACCOMMODATE */
	/* A MORE DYNAMIC, GOAL-ORIENTED PATH PLAN.                */
	/***********************************************************/
	float posDiff[2];

	// Move along a grid edge
	if (countdown > 0)
	{
		countdown--;

		// Reach the next grid point
		if (countdown == 0)
		{
			posDiff[0] = goalGridPos[0] - currGridPos[0];
			posDiff[1] = goalGridPos[1] - currGridPos[1];
			currGridPos[0] = goalGridPos[0];
			currGridPos[1] = goalGridPos[1];

			// Start to spin in place at a grid corner
			if (((currGridPos[0] == 0) || (currGridPos[0] == GRID_SIZE - 1)) &&
				((currGridPos[1] == 0) || (currGridPos[1] == GRID_SIZE - 1)))
			{
				orientCountdown = SPIN_COUNTDOWN_MAX;
				orientGoal = orient + 135.0;
			}

			// Proceed across the next grid edge
			else
			{
				goalGridPos[0] = currGridPos[0] + posDiff[0];
				goalGridPos[1] = currGridPos[1] + posDiff[1];
				if ((posDiff[0] == 0) || (posDiff[1] == 0))
					countdown = REGULAR_COUNTDOWN_MAX;
				else
					countdown = DIAGONAL_COUNTDOWN_MAX;
			}
		}
	}

	// Spin the Runner in place at the current grid point
	// until it is reoriented to face the proper direction.
	if (orientCountdown > 0)
	{
		orientCountdown--;

		// After turning, proceed down the next grid edge
		if (orientCountdown == 0)
		{
			orient = orientGoal;
			pathIndex = (pathIndex + 1) % NBR_PATHS;
			switch (pathIndex)
			{
			case 0: { goalGridPos[0] = 1;             goalGridPos[1] = 1;             countdown = DIAGONAL_COUNTDOWN_MAX; break; }
			case 1: { goalGridPos[0] = GRID_SIZE - 1; goalGridPos[1] = GRID_SIZE - 2; countdown = REGULAR_COUNTDOWN_MAX;  break; }
			case 2: { goalGridPos[0] = GRID_SIZE - 2; goalGridPos[1] = 1;             countdown = DIAGONAL_COUNTDOWN_MAX; break; }
			case 3: { goalGridPos[0] = 1;             goalGridPos[1] = GRID_SIZE - 1; countdown = REGULAR_COUNTDOWN_MAX;  break; }
			case 4: { goalGridPos[0] = GRID_SIZE - 2; goalGridPos[1] = GRID_SIZE - 2; countdown = DIAGONAL_COUNTDOWN_MAX; break; }
			case 5: { goalGridPos[0] = 0;             goalGridPos[1] = 1;             countdown = REGULAR_COUNTDOWN_MAX;  break; }
			case 6: { goalGridPos[0] = 1;             goalGridPos[1] = GRID_SIZE - 2; countdown = DIAGONAL_COUNTDOWN_MAX; break; }
			default: { goalGridPos[0] = GRID_SIZE - 2; goalGridPos[1] = 0;             countdown = REGULAR_COUNTDOWN_MAX;  break; }
			};
		}
	}
	/*********************************************/
	/* END OF HARD-CODED, STATIC PATH PLAN CODE. */
	/*********************************************/

	// Update the positions and orientations associated
	// with the joints and cross-joints of the Runner.
	Hips.update(ANIM_VEL_SCALE_FACTOR);
	Shoulders.update(ANIM_VEL_SCALE_FACTOR);
	TorsoAndHead.update(ANIM_VEL_SCALE_FACTOR);

	int i;
	for (i = 0; i < 3; i++)
	{
		LeftArm[i].update(ANIM_VEL_SCALE_FACTOR);
		RightArm[i].update(ANIM_VEL_SCALE_FACTOR);
	}
	for (i = 0; i < 4; i++)
	{
		LeftLeg[i].update(ANIM_VEL_SCALE_FACTOR);
		RightLeg[i].update(ANIM_VEL_SCALE_FACTOR);
	}
}

// Set the material properties of the Runner
void SetMaterialProperties()
{
	float mat_ambient[] = { AMBIENT_COEFF,  AMBIENT_COEFF,  AMBIENT_COEFF,  1.0 };
	float mat_diffuse[] = { DIFFUSE_COEFF,  DIFFUSE_COEFF,  DIFFUSE_COEFF,  1.0 };
	float mat_specular[] = { SPECULAR_COEFF, SPECULAR_COEFF, SPECULAR_COEFF, 1.0 };
	float mat_shininess[] = { SPECULAR_EXPON };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}
