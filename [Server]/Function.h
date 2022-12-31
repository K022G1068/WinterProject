#pragma once
#include"Struct.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<assert.h>

//Vector2
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix2);

//Matrix2x2
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Substract(Matrix2x2 matrix1, Matrix2x2 matrix2);
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

//Matrix3x3
Matrix3x3 MakeTlanslateMatrix(Vector2 translate);
Matrix3x3 MakeScaleMatrix(Vector2 scale);
//Matrix3x3 MakeRotateMatrix(float theta);
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);
Matrix3x3 MakeAffineMatrix(Vector2 translate, Vector2 scale, float rotate);

Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

//Toscreen
Vector2 ToScreen(const Vector2* world);