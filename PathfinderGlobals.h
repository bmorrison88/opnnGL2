///////////////////////////////////////////////////////
// PathfinderGlobals.h - Global Constant Definitions //
///////////////////////////////////////////////////////

#ifndef PATHFINDER_GLOBALS_H

const float PI = 3.1415926535;

// Window Position/Resizing Constants
const int INIT_WINDOW_POSITION[2] = { 50, 50 };
const float ASPECT_RATIO = 1.0;

// Lighting Constants
const float LIGHT_0_POSITION[] = { 0.0, 5.0, 0.0, 0.0 };
const float LIGHT_1_POSITION[] = { 0.0, -50.0, 50.0, 0.0 };
const float LIGHT_AMBIENT[] = { 0.8, 0.8, 0.8, 1.0 };
const float LIGHT_DIFFUSE[] = { 0.9, 0.9, 0.9, 1.0 };
const float LIGHT_SPECULAR[] = { 1.0, 1.0, 1.0, 1.0 };
const float LIGHT_MODEL_AMBIENT[] = { 0.2, 0.2, 0.2, 1.0 };

// Texture Map Filenames
const char GROUND_BMP_FILENAME[] = "Bitmaps/dirt.bmp";
const char CRATER_BMP_FILENAME[] = "Bitmaps/crater.bmp";

// Viewer Positioning Constants
const float VIEWER_DISTANCE = 48.0;
const float INITIAL_VIEWER_AZIMUTH = 0.0;
const float INITIAL_VIEWER_ZENITH = PI / 60.0;
const float VIEWER_ANGLE_INCREMENT = PI / 60.0;
const float LOOK_AT_POSITION[] = { 0.0, 0.0, 0.0 };

// Scene Constants
const float GROUND_WIDTH = 64.0;
const float GROUND_DEPTH = 64.0;
const float CRATER_RADIUS = 4.0;
const int   NBR_CRATERS = 12;

// Grid Constants
const int   GRID_SIZE = 32;
const float GRID_EDGE_COLOR[3] = { 0.9, 0.9, 0.0 };
const float GRID_POINT_COLOR[3] = { 0.9, 0.0, 0.0 };

// Game Character Constants
const float RUNNER_RESCALE = 10.0;
const float ANIM_VEL_SCALE_FACTOR = 4.0;
const float RUNNER_RADIUS_SIZE = 0.24;
const float RUNNER_COLOR[3] = { 0.2, 0.2, 0.4 };

const float TORSO_AND_HEAD_SPHERE_RADIUS = 3.7 / RUNNER_RESCALE;
const float TORSO_AND_HEAD_ABOVE_SPHERE_RADIUS = 2.75 / RUNNER_RESCALE;
const float TORSO_AND_HEAD_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE }; // elbow
const float TORSO_AND_HEAD_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float TORSO_AND_HEAD_CYLINDER_RADIUS = 2.25 / RUNNER_RESCALE;
const float TORSO_AND_HEAD_CYLINDER_LENGTH = 11.0 / RUNNER_RESCALE;
const float TORSO_AND_HEAD_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float TORSO_AND_HEAD_PITCH = 0.0;
const float TORSO_AND_HEAD_MIN_PITCH = 0.0;
const float TORSO_AND_HEAD_MAX_PITCH = 0.0;
const float TORSO_AND_HEAD_PITCH_INCREMENT = 0.0;

const float SHOULDERS_SPHERE_RADIUS = 3.25 / RUNNER_RESCALE;
const float SHOULDERS_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 6.5 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float SHOULDERS_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float SHOULDERS_CYLINDER_RADIUS = 0.2 / RUNNER_RESCALE;
const float SHOULDERS_CYLINDER_LENGTH = 6.5 / RUNNER_RESCALE;
const float SHOULDERS_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float SHOULDERS_ROLL = 0.0;
const float SHOULDERS_MIN_ROLL = -7.5;
const float SHOULDERS_MAX_ROLL = 7.5;
const float SHOULDERS_ROLL_INCREMENT = -0.5;
const float SHOULDERS_YAW = 0.0;
const float SHOULDERS_MIN_YAW = -7.5;
const float SHOULDERS_MAX_YAW = 7.5;
const float SHOULDERS_YAW_INCREMENT = -0.5;

const float HUMERUS_SPHERE_RADIUS = 2.5 / RUNNER_RESCALE;
const float HUMERUS_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float HUMERUS_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HUMERUS_CYLINDER_RADIUS = 0.3 / RUNNER_RESCALE;
const float HUMERUS_CYLINDER_LENGTH = 2.5 / RUNNER_RESCALE;
const float HUMERUS_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HUMERUS_PITCH = 0.0;
const float HUMERUS_MIN_PITCH = -45.0;
const float HUMERUS_MAX_PITCH = 45.0;
const float HUMERUS_PITCH_INCREMENT = 3.0;

const float FOREARM_SPHERE_RADIUS = 1.5 / RUNNER_RESCALE;
const float FOREARM_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, -HUMERUS_CYLINDER_LENGTH / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float FOREARM_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float FOREARM_CYLINDER_RADIUS = 0.3 / RUNNER_RESCALE;
const float FOREARM_CYLINDER_LENGTH = 2.5 / RUNNER_RESCALE;
const float FOREARM_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float FOREARM_PITCH = 0.0;
const float FOREARM_MIN_PITCH = 0.0;
const float FOREARM_MAX_PITCH = 90.0;
const float FOREARM_PITCH_INCREMENT = 3.0;

const float HAND_SPHERE_RADIUS = 2.0 / RUNNER_RESCALE;
const float HAND_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 0.4 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float HAND_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HAND_CYLINDER_RADIUS = 0.0 / RUNNER_RESCALE;
const float HAND_CYLINDER_LENGTH = 0.0 / RUNNER_RESCALE;
const float HAND_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HAND_PITCH = 0.0;
const float HAND_MIN_PITCH = 0.0;
const float HAND_MAX_PITCH = 0.0;
const float HAND_PITCH_INCREMENT = 0.0;

const float HIPS_SPHERE_RADIUS = 1.75 / RUNNER_RESCALE;
const float HIPS_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float HIPS_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HIPS_CYLINDER_RADIUS = 0.25 / RUNNER_RESCALE;
const float HIPS_CYLINDER_LENGTH = 3.5 / RUNNER_RESCALE;
const float HIPS_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HIPS_ROLL = 0.0;
const float HIPS_MIN_ROLL = -7.5;
const float HIPS_MAX_ROLL = 7.5;
const float HIPS_ROLL_INCREMENT = 0.5;
const float HIPS_YAW = 0.0;
const float HIPS_MIN_YAW = -7.5;
const float HIPS_MAX_YAW = 7.5;
const float HIPS_YAW_INCREMENT = 0.5;

const float THIGH_SPHERE_RADIUS = 2.75 / RUNNER_RESCALE;
const float THIGH_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float THIGH_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float THIGH_CYLINDER_RADIUS = 0.25 / RUNNER_RESCALE;
const float THIGH_CYLINDER_LENGTH = 3.5 / RUNNER_RESCALE;
const float THIGH_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float THIGH_PITCH = 0.0;
const float THIGH_MIN_PITCH = -45.0;
const float THIGH_MAX_PITCH = 45.0;
const float THIGH_PITCH_INCREMENT = 3.0;

const float SHIN_SPHERE_RADIUS = 2.0 / RUNNER_RESCALE;
const float SHIN_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, -THIGH_CYLINDER_LENGTH / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE };
const float SHIN_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float SHIN_CYLINDER_RADIUS = 0.25 / RUNNER_RESCALE;
const float SHIN_CYLINDER_LENGTH = 3.5 / RUNNER_RESCALE;
const float SHIN_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float SHIN_PITCH = 0.0;
const float SHIN_MIN_PITCH = 0.0;
const float SHIN_MAX_PITCH = 90.0;
const float SHIN_PITCH_INCREMENT = 3.0;

const float HEEL_SPHERE_RADIUS = 2.5 / RUNNER_RESCALE;
const float HEEL_SPHERE_CENTER[] = { 0.0, -SHIN_CYLINDER_LENGTH / RUNNER_RESCALE, 0.0 };
const float HEEL_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HEEL_CYLINDER_RADIUS = 0.25 / RUNNER_RESCALE;
const float HEEL_CYLINDER_LENGTH = 2.5 / RUNNER_RESCALE;
const float HEEL_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float HEEL_PITCH = -90.0;
const float HEEL_MIN_PITCH = -105.0;
const float HEEL_MAX_PITCH = -75.0;
const float HEEL_PITCH_INCREMENT = 1.0;

const float TOE_SPHERE_RADIUS = 2.0 / RUNNER_RESCALE;
const float TOE_SPHERE_CENTER[] = { 0.0 / RUNNER_RESCALE, 0.0 / RUNNER_RESCALE, HEEL_CYLINDER_LENGTH / RUNNER_RESCALE };
const float TOE_SPHERE_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float TOE_CYLINDER_RADIUS = 0.0 / RUNNER_RESCALE;
const float TOE_CYLINDER_LENGTH = 0.0 / RUNNER_RESCALE;
const float TOE_CYLINDER_COLOR[] = { RUNNER_COLOR[0], RUNNER_COLOR[1], RUNNER_COLOR[2] };
const float TOE_PITCH = 0.0;
const float TOE_MIN_PITCH = 0.0;
const float TOE_MAX_PITCH = 0.0;
const float TOE_PITCH_INCREMENT = 0.0;

const float CHARACTER_ELEVATION = HIPS_SPHERE_RADIUS + THIGH_CYLINDER_LENGTH +
SHIN_CYLINDER_LENGTH + HEEL_SPHERE_RADIUS;

// Character Path Constants
const int REGULAR_COUNTDOWN_MAX = 10;
const int DIAGONAL_COUNTDOWN_MAX = 14;
const int SPIN_COUNTDOWN_MAX = 15;
const int NBR_PATHS = 8;

// Material Properties Constants
const float AMBIENT_COEFF = -1.0;    // Minimal ambient reflectance.
const float DIFFUSE_COEFF = 1.0;    // Maximal diffuse reflectance.
const float SPECULAR_COEFF = 1.0;    // Maximal specular reflectance.
const float SPECULAR_EXPON = 20.0;    // Low level of shininess (scale: 0-128).

//paint splash 
const int   NBR_GOAL_COLORS = 9;
const float COLORS[NBR_GOAL_COLORS - 1][3] = { { 0.8f,0.2f,0.2f },{ 0.2f,0.8f,0.2f },{ 0.2f,0.2f,0.8f },{ 0.8f,0.8f,0.2f },{ 0.8f,0.2f,0.8f },{ 0.2f,0.8f,0.8f },{ 0.7f,0.7f,0.7f },{ 0.1f,0.1f,0.1f } };
const int   NBR_DROPLETS = 128;						//Total number of droplets per paintball
const float DROPLET_RAD = .05f;						//Radius of a single droplet on a paintball
const int   PAINTBALL_RAD_MOD = 5;					//Used in the randomization of the droplet's distance from center
const int   PAINTBALL_VEC_MOD = 15;					//Used in the randomization of the paintball's movement vector
const int   DROPLET_ROT_MOD = 360;					//Used in the randomization of the paintball's rotation
const int   DROPLET_LIMIT_ROT = 70;
const int   PAINTBALL_ROT_MOD = 10;					//Used in the randomization of the droplet's rotation around the paintball
const int   GOAL_POS[3] = { 0.0f, 1.0f, 0.0f };
const int   COLOR_RANGE = 25;						//Used for limiting the color range
const int   COLOR_INTENSITY = 50;					//Used for limiting the color's intensity
const float FAR_CLIP = -60.0f;						//Far clipping plane
const float MAX_Z = -120.0f;						//Maximum starting distance. Used for randomizing the appearance of each molecule
const int   NBR_TARGETS = 5;						//Total Number of paintballs
const float Z_SPEED = .8f;							//Speed mod for paintballs.
const float EXPLOSION_CONST = .05f;					//Used for affecting the speed of each droplet's explosion,
													// so interior droplets explode faster.

#define PATHFINDER_GLOBALS_H
#endif