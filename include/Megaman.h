#ifndef MEGAMAN_H
#define MEGAMAN_H
#include <iostream>
#include <iterator>
#include <time.h>
#include <list>
#include <GL/gl.h>
#include <GL/glu.h>

#include "glut.h"
#include "SOIL.h"
#include "object.hpp"

using namespace std;

class Megaman{
    public:
        Megaman();

        void Draw();
        void Update(int value);

        // Actions
        bool canon;
        bool shoot;
        bool bullet;
        bool shootBullet;
        bool fire;
        bool walk;
        bool rightLeg;
        int walkEtape;
        time_t seconds;
        float puissance;
        list<float> keepPuissance;

        // Transformations
        float angleArmX = 0;
        float angleForearmY = 0;
        float translateArmZ = 0;
        float translateArmY = 0;
        float translateBulletX[10];
        float translateBulletZ[10];
        float angleForelegX = 0;
        float angleLegX = 0;
        float translateForelegZ = -0.2;
        float angleForelegX_2 = 0;
        float angleLegX_2 = 0;
        float translateForelegZ_2 = -0.2;

    protected:

    private:
        // Draw
        void SetColors(Object *megaman);
        void SetArms(Object *megaman);
        void SetLegs(Object *megaman);

        // Update
        void MoveArm();
        void Walk();
        void ShootBullet();
};


#endif // MEGAMAN_H
