#include "vector2.h"
#include <math.h>

Vector2 Vector2_Add(Vector2 v1, Vector2 v2)
{
    return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

Vector2 Vector2_Sub(Vector2 v1, Vector2 v2)
{
    return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

Vector2 Vector2_Scale(Vector2 v, float scalar)
{
    return (Vector2){v.x * scalar, v.y * scalar};
}

float Vector2_Magnitude(Vector2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

Vector2 Vector2_Normalise(Vector2 v)
{
    float magnitude = Vector2_Magnitude(v);
    if (magnitude == 0) return (Vector2){0, 0};
    return Vector2_Scale(v, 1.0f / magnitude);
}

float Vector2_Dot(Vector2 v1, Vector2 v2) {
    return v1.x * v2.x + v1.y * v2.y;
}