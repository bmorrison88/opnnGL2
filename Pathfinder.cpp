///////////////////////////////////////////////////////////////////////////
// Pathfinder.cpp - Pathfinding Preliminary                              //
//                                                                       //
// Sets up a texture-mapped field of play, with texture-mapped "crater"  //
// obstacles (randomly placed) and a shaded character. The character     //
// ignores the obstacles, but rotates 135 degrees in place whenever it   //
// encounters the edge of the playing field, progressing once it's aimed //
// along a grid edge once again. The user may toggle the grid display,   //
// which relies on a flood-fill algorithm to determine which points and  //
// edges are not covered by the obstacles. A reset key repositions the   //
// obstacles in random (non-overlapping) locations and places the        //
// character back in its starting position.                              //
///////////////////////////////////////////////////////////////////////////

#include <gl/freeglut.h>
#include <cmath>			// Header File For Math Library
#include <ctime>			// Header File For Accessing System Time
#include "RGBpixmap.h" 
#include "Runner.h"
#include "Paintball.h"
#include "PathfinderGlobals.h"

using namespace std;

/********************/
/* Global Variables */
/********************/

// Viewer positioning angles.
float viewerAzimuth = INITIAL_VIEWER_AZIMUTH;
float viewerZenith = INITIAL_VIEWER_ZENITH;

// ID numbers for all texture maps.
GLuint GroundTextureName = 1;
GLuint CraterTextureName = 2;

// Location of the centers of the crater obstacles.
float CraterPosition[NBR_CRATERS][3];

// Grid-based boolean values.
bool gridToggle = false;
bool grid[GRID_SIZE][GRID_SIZE][9]; // 0-coord = Is point activated? Coords 1-8 = Is edge (N,NE,E,SE,S,SW,W,NW) activated?

									// Shaded character.
Runner guy;
float goalPos[2];
bool painting = false;
bool start = true;
int curColor = 1;
Paintball splash(true);

// The initial window and viewport sizes (in pixels), set to ensure that
// the aspect ration for the viewport, will be a constant. If the window
// is resized, the viewport will be adjusted to preserve the aspect ratio.
GLint currWindowSize[2] = { 900, 900 / ASPECT_RATIO };
GLint currViewportSize[2] = { 900, 900 / ASPECT_RATIO };


/***********************/
/* Function prototypes */
/***********************/
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition);
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition);
void TimerFunction(int value);
void Display();

void MakeAllImages();
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha);

void DrawGround();
void TextureMapQuad(GLuint textureName, GLfloat textureCoord[4][2], const GLfloat coord[4][3], const GLfloat normal[3]);
void ResetCraters();

void GenerateGrid();
void FloodGrid(int i, int j);
bool OpenGridPoint(int i, int j);
bool OpenGridEdge(int i0, int j0, int i1, int j1);
bool GridConnected();
void DrawGrid();
void DrawGoal();

void ResetCharacter();
void UpdateCharacter();
void DrawCharacter();

void SetLights();
void UpdateLight();

void ResizeWindow(GLsizei w, GLsizei h);
float GenerateRandomNumber(float lowerBound, float upperBound);


/****************************/
/* Function implementations */
/****************************/

// The main function sets up the data and the   //
// environment to display the textured objects. //
void main(int argc, char **argv)
{
	/* Set up the display window. */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL | GLUT_DEPTH);
	glutInitWindowPosition(INIT_WINDOW_POSITION[0], INIT_WINDOW_POSITION[1]);
	glutInitWindowSize(currWindowSize[0], currWindowSize[1]);
	glutCreateWindow("Grid-Based Texture-Mapped Obstacles - PATHFINDING AND OBSTACLE AVOIDANCE NOT IMPLEMENTED");

	// Specify the resizing and refreshing routines.
	glutReshapeFunc(ResizeWindow);
	glutKeyboardFunc(KeyboardPress);
	glutSpecialFunc(NonASCIIKeyboardPress);
	glutDisplayFunc(Display);
	glutTimerFunc(20, TimerFunction, 1);
	glViewport(0, 0, currWindowSize[0], currWindowSize[1]);

	// Set up standard lighting, shading, and depth testing.
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_NORMALIZE);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	SetLights();

	// Set up all texture maps and texture-mapped objects.
	ResetCraters();
	ResetCharacter();
	MakeAllImages();
	glutMainLoop();
}

// Function to react to ASCII keyboard keys pressed by the user. //
// Used to reset obstacle positions and to toggle grid display.  //
void KeyboardPress(unsigned char pressedKey, int mouseXPosition, int mouseYPosition)
{
	char pressedChar = char(pressedKey);
	switch (pressedKey)
	{
	case 'r':
	case 'R': { ResetCraters(); ResetCharacter(); break; }
	case 'g':
	case 'G': { gridToggle = !gridToggle; break; }
	}
}

// Function to react to non-ASCII keyboard keys pressed by the user. //
// Used to alter spherical coordinates of the viewer's position.     //
void NonASCIIKeyboardPress(int pressedKey, int mouseXPosition, int mouseYPosition)
{
	glutIgnoreKeyRepeat(false);
	switch (pressedKey)
	{
	case GLUT_KEY_RIGHT: {
		viewerAzimuth += VIEWER_ANGLE_INCREMENT;
		if (viewerAzimuth > 2 * PI)
			viewerAzimuth -= 2 * PI;
		break;
	}
	case GLUT_KEY_LEFT: {
		viewerAzimuth -= VIEWER_ANGLE_INCREMENT;
		if (viewerAzimuth < 0.0)
			viewerAzimuth += 2 * PI;
		break;
	}
	case GLUT_KEY_UP: {
		viewerZenith -= VIEWER_ANGLE_INCREMENT;
		if (viewerZenith < VIEWER_ANGLE_INCREMENT)
			viewerZenith = VIEWER_ANGLE_INCREMENT;
		break;
	}
	case GLUT_KEY_DOWN: {
		viewerZenith += VIEWER_ANGLE_INCREMENT;
		if (viewerZenith > PI / 2 - VIEWER_ANGLE_INCREMENT)
			viewerZenith = PI / 2 - VIEWER_ANGLE_INCREMENT;
		break;
	}
	}
}

// Function to update any animation. //
void TimerFunction(int value)
{
	float pos[2];
	UpdateCharacter();
	glutPostRedisplay();
	glutTimerFunc(20, TimerFunction, 1);

	guy.getImageSpacePosition(pos);
	if ((pos[0] == GOAL_POS[0]) && (pos[1] == GOAL_POS[2]))
	{
		painting = true;
		splash.setColor(COLORS[curColor][0], COLORS[curColor][1], COLORS[curColor][2]);
		guy.setColor(COLORS[curColor]);
	}
	if (painting)
	{
		painting = splash.incrementExplosion();
		if (!painting)
		{
			splash.reset();
			curColor = (curColor + 1) % NBR_GOAL_COLORS;
			splash.setColor(COLORS[curColor][0], COLORS[curColor][1], COLORS[curColor][2]);
		}
	}
}

// Principal display routine: sets up material, lighting, //
// and camera properties, clears the frame buffer, and    //
// draws all texture-mapped objects within the window.    //
void Display()
{
	// Initialize lighting.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LIGHT_MODEL_AMBIENT);
	glEnable(GL_LIGHTING);

	// Set up the properties of the viewing camera.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, ASPECT_RATIO, 0.2, 100.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Position and orient viewer.
	gluLookAt(LOOK_AT_POSITION[0] + VIEWER_DISTANCE * sin(viewerZenith) * sin(viewerAzimuth),
		LOOK_AT_POSITION[1] + VIEWER_DISTANCE * cos(viewerZenith),
		LOOK_AT_POSITION[2] + VIEWER_DISTANCE * sin(viewerZenith) * cos(viewerAzimuth),
		LOOK_AT_POSITION[0], LOOK_AT_POSITION[1], LOOK_AT_POSITION[2],
		0.0, 1.0, 0.0);

	// Render scene.
	UpdateLight();
	DrawGround();
	if (gridToggle)
		DrawGrid();
	DrawGoal();
	DrawCharacter();

	// Reset for next time interval.
	glDisable(GL_LIGHTING);
	glutSwapBuffers();
	glFlush();
}

// Create the textures associated with all texture-mapped objects being displayed. //
void MakeAllImages()
{
	MakeImage(GROUND_BMP_FILENAME, GroundTextureName, false);
	MakeImage(CRATER_BMP_FILENAME, CraterTextureName, true);
	return;
}

// Convert the bitmap with the parameterized name into an OpenGL texture. //
void MakeImage(const char bitmapFilename[], GLuint &textureName, bool hasAlpha)
{
	RGBpixmap pix;
	pix.readBMPFile(bitmapFilename, hasAlpha);
	pix.setTexture(textureName);
	return;
}

// Display the texture-mapped playing field (using a simple rectangle), as well //
// as the texture-mapped obstacles (using a quadric surface, i.e., a disk).     //
void DrawGround()
{
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);
	const GLfloat groundCoord[4][3] = { { -GROUND_WIDTH / 2, 0.0,  GROUND_DEPTH / 2 } ,
	{ GROUND_WIDTH / 2, 0.0,  GROUND_DEPTH / 2 } ,
	{ GROUND_WIDTH / 2, 0.0, -GROUND_DEPTH / 2 } ,
	{ -GROUND_WIDTH / 2, 0.0, -GROUND_DEPTH / 2 } };
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GroundTextureName);

	// Display the texture-mapped playing field.
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(groundCoord[0][0], groundCoord[0][1], groundCoord[0][2]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(groundCoord[1][0], groundCoord[1][1], groundCoord[1][2]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(groundCoord[2][0], groundCoord[2][1], groundCoord[2][2]);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(groundCoord[3][0], groundCoord[3][1], groundCoord[3][2]);
	glEnd();

	// Display the texture-mapped obstacles, slightly above the playing field.
	for (int i = 0; i < NBR_CRATERS; i++)
	{
		glPushMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTranslatef(CraterPosition[i][0], CraterPosition[i][1], CraterPosition[i][2]);
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glBindTexture(GL_TEXTURE_2D, CraterTextureName);
		gluDisk(quadro, 0.0, CRATER_RADIUS, 24, 12);
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glFlush();
}

// Draw the parameterized texture on the parameterized quadrilateral. //
void TextureMapQuad(GLuint textureName, float textureCoord[4][2], const float coord[4][3], const float normal[3])
{
	glBindTexture(GL_TEXTURE_2D, textureName);
	glBegin(GL_QUADS);
	glNormal3f(normal[0], normal[1], normal[2]);
	for (int i = 0; i < 4; i++)
	{
		glTexCoord2f(textureCoord[i][0], textureCoord[i][1]);
		glVertex3f(coord[i][0], coord[i][1], coord[i][2]);
	}
	glEnd();
}

// Randomly generate three obstacles, positioned so that they do not overlap. //
void ResetCraters()
{
	bool finalized = false;
	bool confirmed;
	int noOverlapCount;
	while (!finalized)
	{
		for (int i = 0; i < NBR_CRATERS; i++)
		{
			confirmed = false;
			while (!confirmed)
			{
				// Note: x-coordinate is moved far enough to ensure that first grid point (the flood-fill seed) is open.
				CraterPosition[i][0] = GenerateRandomNumber(-GROUND_WIDTH / 2 + 1.25* CRATER_RADIUS, GROUND_WIDTH / 2 - CRATER_RADIUS);
				CraterPosition[i][1] = 0.01 + 0.01 * i;
				CraterPosition[i][2] = GenerateRandomNumber(-GROUND_DEPTH / 2 + CRATER_RADIUS, GROUND_DEPTH / 2 - CRATER_RADIUS);
				noOverlapCount = 0;
				for (int j = 0; j < i; j++)
					if (sqrt(pow(CraterPosition[j][0] - CraterPosition[i][0], 2) +
						pow(CraterPosition[j][2] - CraterPosition[i][2], 2)) > 2 * CRATER_RADIUS)
						noOverlapCount++;
				confirmed = (noOverlapCount == i);
			}
		}
		GenerateGrid();
		finalized = GridConnected();
	}
}

// Generate the set of valid points and edges of the grid, i.e., those not affected by the obstacles. //
void GenerateGrid()
{
	int i, j, k;
	for (i = 0; i < GRID_SIZE; i++)
		for (j = 0; j < GRID_SIZE; j++)
			for (k = 0; k < 9; k++)
				grid[i][j][k] = false;

	// Use the first grid point as a seed point for the flood-fill.
	grid[0][0][0] = true;
	FloodGrid(0, 0);
}

// Recursively determine the valid grid points and edges. The parameterized point has //
// been determined to be valid. Any of its neighbors that are not obstructed will     //
// have their edges with this point validated. If the neighbor hasn't already been    //
// validated, then it is validated and the recursion continues with that point.       //
void FloodGrid(int i, int j)
{
	int nbr_i, nbr_j, nbr_k;
	for (int k = 1; k < 9; k++)
	{
		switch (k)
		{
		case 1: case 2: case 8: {nbr_i = i - 1; break; }  // Northern neighbor
		case 4: case 5: case 6: {nbr_i = i + 1; break; }  // Southern neighbor
		default: {nbr_i = i; break; }    // Horizontal neighbor
		}
		switch (k)
		{
		case 6: case 7: case 8: {nbr_j = j - 1; break; }  // Western neighbor
		case 2: case 3: case 4: {nbr_j = j + 1; break; }  // Eastern neighbor
		default: {nbr_j = j; break; }    // Vertical neighbor
		}

		// Check whether the neighbor is inside the playing field and not obstructed.
		if ((nbr_i >= 0) && (nbr_j >= 0) && (nbr_i < GRID_SIZE) && (nbr_j < GRID_SIZE) && (OpenGridPoint(nbr_i, nbr_j)))
		{
			if (!grid[nbr_i][nbr_j][0])
			{
				grid[nbr_i][nbr_j][0] = true;
				FloodGrid(nbr_i, nbr_j);
			}
			if (OpenGridEdge(i, j, nbr_i, nbr_j))
			{
				nbr_k = (k + 3) % 8 + 1;
				grid[i][j][k] = grid[nbr_i][nbr_j][nbr_k] = true;
			}
		}
	}
}

// Determine whether the designated grid point is within the     //
// circular radius of any of the obstacles on the playing field. //
bool OpenGridPoint(int i, int j)
{
	float coord_x = (j + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
	float coord_z = (i + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	for (int k = 0; k < NBR_CRATERS; k++)
		if (sqrt(pow(coord_x - CraterPosition[k][0], 2) + pow(coord_z - CraterPosition[k][2], 2)) <= CRATER_RADIUS)
			return false;
	return true;
}

// Determine whether the designated grid edge intersects the   //
// circumference of any of the obstacles on the playing field. //
bool OpenGridEdge(int i0, int j0, int i1, int j1)
{
	float x0 = (j0 + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
	float z0 = (i0 + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	float x1 = (j1 + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
	float z1 = (i1 + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
	float quad_coeff, lin_coeff, const_coeff, discriminant;
	float intersection_t;
	for (int k = 0; k < NBR_CRATERS; k++)
	{
		quad_coeff = pow(x0 - x1, 2) + pow(z0 - z1, 2);
		lin_coeff = 2 * ((x0 - CraterPosition[k][0]) * (x1 - x0) + (z0 - CraterPosition[k][2]) * (z1 - z0));
		const_coeff = pow(x0 - CraterPosition[k][0], 2) + pow(z0 - CraterPosition[k][2], 2) - pow(CRATER_RADIUS, 2);
		discriminant = pow(lin_coeff, 2) - 4 * quad_coeff * const_coeff;
		if (discriminant >= 0)
		{
			intersection_t = (-1 * lin_coeff + sqrt(discriminant)) / (2 * quad_coeff);
			if ((intersection_t >= 0) && (intersection_t <= 1))
				return false;
			else
			{
				intersection_t = (-1 * lin_coeff - sqrt(discriminant)) / (2 * quad_coeff);
				if ((intersection_t >= 0) && (intersection_t <= 1))
					return false;
			}
		}
	}
	return true;
}

// Determine whether the flood-filled grid contains all grid //
// points that are not covered by any of the craters.        //
bool GridConnected()
{
	for (int i = 0; i < GRID_SIZE; i++)
		for (int j = 0; j < GRID_SIZE; j++)
			if (grid[i][j][0] != OpenGridPoint(i, j))
				return false;
	return true;
}

// Render the valid grid points and edges. The edges are placed at a height above //
// the obstacles, while the grid points are placed slightly above the grid edges. //
void DrawGrid()
{
	float coord_x, coord_y, coord_z, nbr_x, nbr_y, nbr_z;
	float fSizes[2];
	float normalSize;
	GLUquadricObj* quadro = gluNewQuadric();
	gluQuadricNormals(quadro, GLU_SMOOTH);
	gluQuadricTexture(quadro, GL_TRUE);

	glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes);
	normalSize = fSizes[0];
	glLineWidth(normalSize);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < GRID_SIZE; i++)
		for (int j = 0; j < GRID_SIZE; j++)
		{
			glColor3fv(GRID_EDGE_COLOR);
			if (grid[i][j][0])
			{
				coord_x = (j + 0.5) * GROUND_WIDTH / GRID_SIZE - 0.5 * GROUND_WIDTH;
				coord_y = 0.05;
				coord_z = (i + 0.5) * GROUND_DEPTH / GRID_SIZE - 0.5 * GROUND_DEPTH;
				for (int k = 1; k < 9; k++)
				{
					if (grid[i][j][k])
					{
						switch (k)
						{
						case 2: case 3: case 4: { nbr_x = coord_x + GROUND_WIDTH / GRID_SIZE; break; }
						case 6: case 7: case 8: { nbr_x = coord_x - GROUND_WIDTH / GRID_SIZE; break; }
						default: { nbr_x = coord_x; break; }
						}
						nbr_y = coord_y;
						switch (k)
						{
						case 4: case 5: case 6: { nbr_z = coord_z + GROUND_DEPTH / GRID_SIZE; break; }
						case 1: case 2: case 8: { nbr_z = coord_z - GROUND_DEPTH / GRID_SIZE; break; }
						default: { nbr_z = coord_z; break; }
						}
						glBegin(GL_LINES);
						glVertex3f(coord_x, coord_y, coord_z);
						glVertex3f(nbr_x, nbr_y, nbr_z);
						glEnd();
					}
				}
				glPushMatrix();
				glColor3fv(GRID_POINT_COLOR);
				glTranslatef(coord_x, coord_y + 0.01, coord_z);
				glRotatef(-90.0, 1.0, 0.0, 0.0);
				gluDisk(quadro, 0.0, 0.1, 24, 12);
				glPopMatrix();
			}
		}
	glEnable(GL_LIGHTING);
}

// If the goal position has not been reached, draw the spherical goal object in its position.
// If the goal position has ben reached, draw the "exploding paintball" in that position.
void DrawGoal()
{
	GLUquadricObj *qObj;
	qObj = gluNewQuadric();
	gluQuadricDrawStyle(qObj, GLU_FILL);
	if (!painting)
	{
		glColor3f(COLORS[curColor][0], COLORS[curColor][1], COLORS[curColor][2]);
		glPushMatrix();
		glTranslatef(GOAL_POS[0], GOAL_POS[1], GOAL_POS[2]);
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluSphere(qObj, 0.4f, 16, 16);
		glPopMatrix();
	}
	if (painting)
		splash.draw(qObj);
	gluDeleteQuadric(qObj);
	glColor3f(1, 1, 1);
}

// Reset the character to its initial position and orientation. //
void ResetCharacter()
{
	int currPos[2] = { GRID_SIZE / 2, GRID_SIZE / 2 };
	int goalPos[2] = { currPos[0] + 1, currPos[1] + 1 };
	guy.init(currPos, goalPos, DIAGONAL_COUNTDOWN_MAX, 45.0, 0.0, 0, 0);
}

// Update the character's position and orientation.
// Terminology clarification: "Position" and "Orientation" are
// used to refer to grid-based information, while "Location" 
// and "Spin" refer to 3D position and orientation.
void UpdateCharacter()
{
	guy.update();
}

// Render the texture-mapped character in its current position and aimed in its proper orientation. //
void DrawCharacter()
{
	guy.draw();
}

// Set the two lights to illuminate the scene. //
void SetLights()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LIGHT_AMBIENT);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LIGHT_DIFFUSE);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LIGHT_SPECULAR);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
}

// Enable the scene's lighting. //
void UpdateLight()
{
	glPushMatrix();
	glLightfv(GL_LIGHT0, GL_POSITION, LIGHT_0_POSITION);
	glLightfv(GL_LIGHT1, GL_POSITION, LIGHT_1_POSITION);
	glPopMatrix();

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

// Window-reshaping callback, adjusting the viewport to be as large  //
// as possible within the window, without changing its aspect ratio. //
void ResizeWindow(GLsizei w, GLsizei h)
{
	currWindowSize[0] = w;
	currWindowSize[1] = h;
	if (ASPECT_RATIO > w / h)
	{
		currViewportSize[0] = w;
		currViewportSize[1] = w / ASPECT_RATIO;
	}
	else
	{
		currViewportSize[1] = h;
		currViewportSize[0] = h * ASPECT_RATIO;
	}

	glViewport(0.5*(w - currViewportSize[0]), 0.5*(h - currViewportSize[1]), currViewportSize[0], currViewportSize[1]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// Generate a random floating-point value between the two parameterized values. //
float GenerateRandomNumber(float lowerBound, float upperBound)
{
	static bool firstTime = true;
	static time_t randomNumberSeed;

	if (firstTime)
	{
		time(&randomNumberSeed);
		firstTime = false;
		srand(randomNumberSeed);
	}

	return (lowerBound + ((upperBound - lowerBound) * (float(rand()) / RAND_MAX)));
}