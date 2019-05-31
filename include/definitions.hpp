//#include <corecrt_math_defines.h>

// CONFIGURATION //
// Fenêtre
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

// Variables de taille de la classe Object
#define NUMBER_OBJECTS 20
#define NUMBER_COLORS 15
#define NUMBER_PARTS 10

// Objects
#define TETE 0
#define CORPS 1
#define CASQUE 2
#define BRAS 3
#define AVANT_BRAS 4
#define CANON 5
#define JAMBE 6
#define AVANT_JAMBE 7
#define PIED 8
#define SECTION 9
#define BULLET 10
#define EYES 11
#define PUPILLE 12

// Colors
#define BLUE 0
#define BLUE_LIGHT 1
#define WHITE 2
#define BEIGE 3
#define RED 4
#define RED_LIGHT 5
#define BLACK 6

// Megaman
#define VITESSE 1.5
#define PUISSANCE_BULLET 0.1
#define PUISSANCE_MAX_BULLET 2
#define TIME_SHOOT 1
#define VITESSE_WALK 0.1


// CAN'T TOUCH THIS //
// Formes
#define GL_CERCLE 0x0010
#define GL_TRAPEZE 0x0011
#define GL_TRAPEZE3D 0x0021
#define GL_POLYGON3D 0x0022
#define GL_RECTANGLE 0x0023
#define GL_CIRCLE_ARC 0x0024

// Touches
#define SPACEBAR 32

// Maths
//#define DEG2RAD(x) x * (M_PI/180)
#define DEG2RAD(x) x * (3.14/180)
