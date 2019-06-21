#ifndef MAP_H
#define MAP_H

#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"

#include "Camera.h"

class Map
{
    public:
        Map();
        // Stockage des références aux textures
        GLuint ListeTextures[30];
        GLuint Skybox[6];
        void LoadTextures(void);
        void DrawGround(void);
        void DrawAllBatiment();
        void DrawAllCible();
        void DrawSkybox(Camera *cam);
        float cibleTabX[6] = {-30,-5,5.31,24.15,6,-0.28};
        float cibleTabZ[6] = {3,-18,-30,-39.7,-6.4,30.64};

    protected:
    private:
        void DrawTour();
        void DrawBatiment();
        void DrawBatiment2();
        void Cible();
};

#endif // MAP_H
