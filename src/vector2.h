#ifndef VECTOR_2_H
#define VECTOR_2_H

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

// Add two Vectors
Vector2 Vector2_Add(Vector2 v1, Vector2 v2);

// Substract two Vectors
Vector2 Vector2_Sub(Vector2 v1, Vector2 v2);

// Scale a Vector
Vector2 Vector2_Scale(Vector2 v, float scalar);

// Magnitude of a Vector
float Vector2_Magnitude(Vector2 v);

// Normalise a Vector
Vector2 Vector2_Normalise(Vector2 v);

// Dot product of two vectors
float Vector2_Dot(Vector2 v1, Vector2 v2);



#endif 