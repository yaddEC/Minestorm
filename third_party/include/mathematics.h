
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


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
float degToRad(float deg);
Vec rotateVec (Vec tor, Vec origin, float angle );
bool colPointTriangle(Vec P, Vec A, Vec B, Vec C);
bool colTriangle(Vec A1, Vec B1, Vec C1, Vec A2, Vec B2, Vec C2);

Vec negate(Vec lhs, Vec rhs);