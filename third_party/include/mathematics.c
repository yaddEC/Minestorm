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

float minFinder(float k1, float k2, float k3)
{
    if (k1 < k2 && k1 < k3)
    {
        return k1;
    }
    if (k2 < k1 && k2 < k3)
    {
        return k2;
    }
    if (k3 < k2 && k3 < k1)
    {
        return k3;
    }
    return 1;
}

bool checkColTriangle(Vec A1, Vec B1, Vec C1, Vec A2, Vec B2, Vec C2)
{
    Vec K;
    Vec Bp;
    Vec Kpb;
    Vec Mem;
    Vec Memo;
    Vec Mem2;
    Vec Memo2;
    Vec Mem3;
    Vec Memo3;

    float k1;
    float k2;
    float k3;
    float kmin;

    rangeCreator(A1, B1, C1, &K, &Bp);

    projetOrtho(A1, B1, A2, &K, &Bp, &Mem);

    Kpb = negate(Bp, K);
    Memo = negate(Mem, Bp);

    k1 = Kpb.x / Memo.x;

    projetOrtho(A1, B1, B2, &K, &Bp, &Mem2);
    Memo2 = negate(Mem2, Bp);
    k2 = Kpb.x / Memo2.x;

    projetOrtho(A1, B1, C2, &K, &Bp, &Mem3);
    Memo3 = negate(Mem3, Bp);
    k3 = Kpb.x / Memo3.x;

    kmin = minFinder(k1, k2, k3);
    kmin = sqrt(kmin * kmin);

   
    if (kmin >= 1)
    {
        return true;
    }

    return false;
}
bool colTriangle(Vec A1, Vec B1, Vec C1, Vec A2, Vec B2, Vec C2)
{
    if (checkColTriangle(A1, B1, C1, A2, B2, C2) == true && checkColTriangle(B1, A1, C1, A2, B2, C2) == true && checkColTriangle(C1, B1, A1, A2, B2, C2) == true && checkColTriangle(B1, C1, A1, A2, B2, C2) == true && checkColTriangle(A1, C1, B1, A2, B2, C2) == true && checkColTriangle(C1, A1, B1, A2, B2, C2) == true)
    {
        return true;
    }
    return false;
}

Vec negate(Vec lhs, Vec rhs)
{
    Vec ret;
    ret.x = lhs.x - rhs.x;
    ret.y = lhs.y - rhs.y;
    return ret;
}