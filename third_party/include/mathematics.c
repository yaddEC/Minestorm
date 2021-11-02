#include "mathematics.h"
#define PI 3.14159265358979323846
float puissance(float a, float b)
{
    int i = 1;
    float r = a;
    while (i != b)
    {
        r = r * a;
        i++;
    }
    printf("\n%f exposant %f est egale a %f \n", a, b, r);
    return r;
}

float carre(float a)
{
    float r;
    r = a * a;
    printf("\nle carre de %f est egale a %f\n", a, r);
    return r;
}

float racine_carre(float a)
{
    float r = sqrt(a);
    printf("\nLa racine carre de %f est egale a %f\n", a, r);
    return r;
}

float fcos(float a)
{
    float r = cos(a);
    printf("\nCos(%f) = %f\n", a, r);
    return r;
}
float fsin(float a)
{
    float r = sin(a);
    printf("\nSin(%f) = %f\n", a, r);
    return r;
}
float ftan(float a)
{
    float r = tan(a);
    printf("\nTan(%f) = %f\n", a, r);
    return r;
}

float degToRad(float deg)
{
    return deg * (PI / 180);
}

Vec rotateVec(Vec tor, Vec origin, float angle)
{
    Vec tor2;

    tor2.x = cos(degToRad(angle)) * (tor.x - origin.x) - sin(degToRad(angle)) * (tor.y - origin.y) + origin.x;
    tor2.y = sin(degToRad(angle)) * (tor.x - origin.x) + cos(degToRad(angle)) * (tor.y - origin.y) + origin.y;

    return tor2;
}


