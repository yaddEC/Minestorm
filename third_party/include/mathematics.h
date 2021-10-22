
#include <math.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct Vec {
float x;
float y;
} Vec;

float puissance (float a, float b);
float carre(float a);
float racine_carre(float a);
float fcos(float a);
float fsin(float a);
float ftan(float a);
float valeur_absolu (float a);
float degToRad(float deg);
Vec rotateVec (Vec tor, Vec origin, float angle );
bool checkColTriangle(Vec P1,Vec P2,Vec P3, Vec A, Vec B, Vec C);
void rangeCreator(Vec A, Vec B, Vec* xKBp, Vec* yKBp );

Vec negate(Vec lhs, Vec rhs);