#include "Function.h"
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	result.m[0][0] = matrix1.m[0][0] + matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] + matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] + matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] + matrix2.m[1][1];
	return result;
};
Matrix2x2 Substract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	result.m[0][0] = matrix1.m[0][0] - matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] - matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] - matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] - matrix2.m[1][1];
	return result;
};
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result;
	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0];
	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1];
	return result;
};
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix2) {
	Vector2 result;
	result.x = vector.x * matrix2.m[0][0] + vector.y * matrix2.m[1][0];
	result.y = vector.x * matrix2.m[0][1] + vector.y * matrix2.m[1][1];
	return result;
};

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result;
	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + matrix1.m[0][1] * matrix2.m[1][0] + matrix1.m[0][2] * matrix2.m[2][0];
	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + matrix1.m[0][1] * matrix2.m[1][1] + matrix1.m[0][2] * matrix2.m[2][1];
	result.m[0][2] = matrix1.m[0][0] * matrix2.m[0][2] + matrix1.m[0][1] * matrix2.m[1][2] + matrix1.m[0][2] * matrix2.m[2][2];
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + matrix1.m[1][1] * matrix2.m[1][0] + matrix1.m[1][2] * matrix2.m[2][0];
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + matrix1.m[1][1] * matrix2.m[1][1] + matrix1.m[1][2] * matrix2.m[2][1];
	result.m[1][2] = matrix1.m[1][0] * matrix2.m[0][2] + matrix1.m[1][1] * matrix2.m[1][2] + matrix1.m[1][2] * matrix2.m[2][2];
	result.m[2][0] = matrix1.m[2][0] * matrix2.m[0][0] + matrix1.m[2][1] * matrix2.m[1][0] + matrix1.m[2][2] * matrix2.m[2][0];
	result.m[2][1] = matrix1.m[2][0] * matrix2.m[0][1] + matrix1.m[2][1] * matrix2.m[1][1] + matrix1.m[2][2] * matrix2.m[2][1];
	result.m[2][2] = matrix1.m[2][0] * matrix2.m[0][2] + matrix1.m[2][1] * matrix2.m[1][2] + matrix1.m[2][2] * matrix2.m[2][2];
	return result;
}

//同時座標変換
Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 MakeTlanslateMatrix(Vector2 translate) {
	Matrix3x3 result;
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;
	return result;
}
Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);
	result.m[0][2] = 0;
	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);
	result.m[1][2] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	return result;
};
Matrix3x3 MakeScaleMatrix(Vector2 scale)
{
	Matrix3x3 result;
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	return result;
}

//Weird rotation
//Matrix3x3 MakeAffineMatrix(Vector2 translate,Vector2 scale, float rotate)
//{
//	Matrix3x3 result;
//	result.m[0][0] = scale.x * cosf(rotate);
//	result.m[0][1] = scale.x * sinf(rotate);
//	result.m[0][2] = 0.0f;
//	result.m[1][0] = - (scale.y * cosf(rotate));
//	result.m[1][1] = scale.y * cosf(rotate);
//	result.m[1][2] = 0.0f;
//	result.m[2][0] = translate.x;
//	result.m[2][1] = translate.y;
//	result.m[2][2] = 1.0f;
//	return result;
//}

Matrix3x3 MakeAffineMatrix(Vector2 translate, Vector2 scale, float rotate)
{
	Matrix3x3 result;
	result.m[0][0] = scale.x * cosf(rotate);
	result.m[0][1] = scale.x * sinf(rotate);
	result.m[0][2] = 0.0f;
	result.m[1][0] = -(scale.y * sinf(rotate));
	result.m[1][1] = scale.y * cosf(rotate);
	result.m[1][2] = 0.0f;
	result.m[2][0] = translate.x;
	result.m[2][1] = translate.y;
	result.m[2][2] = 1.0f;
	return result;
}

Vector2 ToScreen(const Vector2* world) {
	const Vector2 kWorldToScreenTranslate = { 0.0f, 500.0f };
	const Vector2 kWorldToScreenScale = { 1.0f, -1.0f };
	return{
		(world->x * kWorldToScreenScale.x) + kWorldToScreenTranslate.x,
		(world->y * kWorldToScreenScale.y) + kWorldToScreenTranslate.y,
	};
}