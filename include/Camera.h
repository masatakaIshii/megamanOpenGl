#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#define MOVE_SPEED 0.1f
#define SENSIBILITY 0.005f
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
class Camera
{
    public:
        Camera();

        char locked;

        float posx;
        float posy;
        float posz;

        float dirx;
        float diry;
        float dirz;

        char deltaForward;
        char deltaStrafe;

        void updatePos(void);
        void releaseCam(void);
        void grabCam(int x, int y);
        void orienterCam(int x, int y);


    protected:
    private:


        float angleh;
        float anglev;

        int xOrigin;
        int yOrigin;
        float deltaAnglex;
        float deltaAngley;



};

#endif // CAMERA_H
