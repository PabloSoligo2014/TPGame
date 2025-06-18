#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

#include <math.h>

typedef struct svector2D {
    float x;
    float y;
} Vector2D;

float Vector2D_getX(Vector2D* self);
float Vector2D_getY(Vector2D* self);

void Vector2D_setX(Vector2D* self, float x);
void Vector2D_setY(Vector2D* self, float y);

float Vector2D_length(Vector2D* self);
void Vector2D_add(Vector2D* self1, Vector2D* self2);
Vector2D Vector2D_mult(Vector2D* self, float scalar);
Vector2D Vector2D_subst(Vector2D* self1, Vector2D* self2);
Vector2D Vector2D_div(Vector2D* self, float scalar);
void Vector2D_normalize(Vector2D* self);

#endif // VECTOR2D_H_INCLUDED
