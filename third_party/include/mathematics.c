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

void projetOrtho(Vec A, Vec B, Vec C, Vec *K, Vec *Bp, Vec *Mem)
{
    float a1 = (B.y - A.y) / (B.x - A.x);
    float b1 = C.y - (a1 * C.x);
    float a2 = (Bp->y - K->y) / (Bp->x - K->x);
    float b2 = Bp->y - (a2 * Bp->x);
    float x = (b2 - b1) / (a1 - a2);
    float y = a2 * x + b2;
    Mem->x = x;
    Mem->y = y;
}

void rangeCreator(Vec A, Vec B, Vec C, Vec *K, Vec *Bp)
{
    Vec AK;
    Vec AB;
    Vec KBp;
    AB = negate(B, A);
    AK.x = AB.x * 2;
    AK.y = AB.y * 2;
    KBp.y = AK.y;
    KBp.x = -(AK.y * AK.y) / AK.x;
    K->x = B.x + AB.x;
    K->y = B.y + AB.y;
    Bp->x = KBp.x + K->x;
    Bp->y = KBp.y + K->y;
    projetOrtho(A, B, C, K, Bp, Bp);
}

float minFinder(float *k1, int n)
{
    float comp;

    for (int i = 0; i < n; i++)
    {
        if (i == 0 || k1[i] < comp)
        {
            comp = k1[i];
        }
    }
    return comp;
}

bool colTriangle(Vec A1, Vec B1, Vec C1, Vec A2, Vec B2, Vec C2)
{
    Vec K;
    Vec Bp;
    Vec Mem;

    float *k = malloc(sizeof(float) * 3);

    rangeCreator(A1, B1, C1, &K, &Bp);
    projetOrtho(A1, B1, A2, &K, &Bp, &Mem);
    k[0] = Bp.x / Mem.x;

    projetOrtho(A1, B1, B2, &K, &Bp, &Mem);
    k[1] = Bp.x / Mem.x;
    projetOrtho(A1, B1, C2, &K, &Bp, &Mem);
    k[2] = Bp.x / Mem.x;
    k[0] = minFinder(k, 3);
    k[0] = sqrt(k[0] * k[0]);
    if (k[0] < 1)
    {
        rangeCreator(B1, C1, A1, &K, &Bp);
        projetOrtho(B1, C1, A2, &K, &Bp, &Mem);
        k[0] = Bp.x / Mem.x;
        projetOrtho(B1, C1, B2, &K, &Bp, &Mem);
        k[1] = Bp.x / Mem.x;
        projetOrtho(B1, C1, C2, &K, &Bp, &Mem);
        k[2] = Bp.x / Mem.x;
        k[0] = minFinder(k, 3);
        k[0] = sqrt(k[0] * k[0]);
        if (k[0] < 1)
        {
            rangeCreator(C1, A1, B1, &K, &Bp);
            projetOrtho(C1, A1, A2, &K, &Bp, &Mem);
            k[0] = Bp.x / Mem.x;
            projetOrtho(C1, A1, B2, &K, &Bp, &Mem);
            k[1] = Bp.x / Mem.x;
            projetOrtho(C1, A1, C2, &K, &Bp, &Mem);
            k[2] = Bp.x / Mem.x;
            k[0] = minFinder(k, 3);
            k[0] = sqrt(k[0] * k[0]);
            if (k[0] < 1)
            {

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

Vec negate(Vec lhs, Vec rhs)
{
    Vec ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    return ret;
}
