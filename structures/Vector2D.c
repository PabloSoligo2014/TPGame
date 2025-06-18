#include "Vector2D.h"

float Vector2D_getX(Vector2D* self) {
    float x = self->x;
    return x;
}

float Vector2D_getY(Vector2D* self) {
    return (self->y);
}


void Vector2D_setX(Vector2D* self, float x) {
    self->x = x;
}

void Vector2D_setY(Vector2D* self, float y) {
    self->y = y;
}


float Vector2D_length(Vector2D* self) {
    return sqrt(self->x * self->x + self->y * self->y);
}

void Vector2D_add(Vector2D* self1, Vector2D* self2) {
    Vector2D_setX(self1, self1->x + self2->x);
    Vector2D_setY(self1, self1->y + self2->y);
}

Vector2D Vector2D_mult(Vector2D* self, float scalar) {
    Vector2D v2;
    Vector2D_setX(&v2, self->x * scalar);
    Vector2D_setY(&v2, self->y * scalar);

    return v2;
}

Vector2D Vector2D_subst(Vector2D* self1, Vector2D* self2) {
    Vector2D v3;
    Vector2D_setX(&v3, self1->x - self2->x);
    Vector2D_setY(&v3, self1->y - self2->y);

    return v3;
}

Vector2D Vector2D_div(Vector2D* self, float scalar) {
    Vector2D v2;
    Vector2D_setX(&v2, self->x / scalar);
    Vector2D_setY(&v2, self->y / scalar);

    return v2;
}

void Vector2D_normalize(Vector2D* self) {
    float l = Vector2D_length(self);
    Vector2D v2;
    if (l > 0) {
        v2 = Vector2D_div(&v2, l);
        Vector2D_setX(self, v2.x);
        Vector2D_setY(self, v2.y);
    }
}
