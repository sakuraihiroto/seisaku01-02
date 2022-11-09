#pragma once
#include "Matrix4.h"
#include <math.h>
#include "WorldTransform.h"

class MatWorld
{
public:

	Matrix4 Identity();

	Matrix4 Scaling(Vector3 scale);

	Matrix4 RotationZ(float rotationZ);

	Matrix4 RotationX(float rotationX);

	Matrix4 RotationY(float rotationY);

	Matrix4 Trans(Vector3 trans);

	Matrix4 CreateMatWorld(const WorldTransform& worldTransform);

	Vector3 CreateVector(Vector3& v, const Matrix4& m);
};

