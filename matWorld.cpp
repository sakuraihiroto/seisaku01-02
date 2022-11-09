#include "matWorld.h"

Matrix4 MatWorld::Identity()
{
	Matrix4 matIdentity;
	matIdentity.m[0][0] = 1;
	matIdentity.m[1][1] = 1;
	matIdentity.m[2][2] = 1;
	matIdentity.m[3][3] = 1;
	return matIdentity;
}

Matrix4 MatWorld::Scaling(Vector3 scale)
{
	Matrix4 matScale;
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
	matScale.m[3][3] = 1;
	return matScale;
}

Matrix4 MatWorld::RotationZ(float rotationZ)
{
	Matrix4 matRotZ;
	matRotZ.m[0][0] = cos(rotationZ);
	matRotZ.m[0][1] = sin(rotationZ);
	matRotZ.m[1][0] = -sin(rotationZ);
	matRotZ.m[1][1] = cos(rotationZ);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;
	return matRotZ;
}

Matrix4 MatWorld::RotationX(float rotationX)
{
	Matrix4 matRotX;
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cos(rotationX);
	matRotX.m[1][2] = sin(rotationX);
	matRotX.m[2][1] = -sin(rotationX);
	matRotX.m[2][2] = cos(rotationX);
	matRotX.m[3][3] = 1;
	return matRotX;
}

Matrix4 MatWorld::RotationY(float rotationY)
{
	Matrix4 matRotY;
	matRotY.m[0][0] = cos(rotationY);
	matRotY.m[1][1] = 1;
	matRotY.m[0][2] = -sin(rotationY);
	matRotY.m[2][2] = cos(rotationY);
	matRotY.m[2][0] = sin(rotationY);
	matRotY.m[3][3] = 1;
	return matRotY;
}

Matrix4 MatWorld::Trans(Vector3 trans)
{
	Matrix4 matTrans;
	matTrans = Identity();
	matTrans.m[3][0] = trans.x;
	matTrans.m[3][1] = trans.y;
	matTrans.m[3][2] = trans.z;
	return matTrans;
}

Matrix4 MatWorld::CreateMatWorld(const WorldTransform& worldTransform)
{
	Matrix4 matWorld = Identity();
	matWorld *= Scaling(worldTransform.scale_);
	matWorld *= RotationZ(worldTransform.rotation_.z);
	matWorld *= RotationX(worldTransform.rotation_.x);
	matWorld *= RotationY(worldTransform.rotation_.y);
	matWorld *= Trans(worldTransform.translation_);

	return matWorld;
}

Vector3 MatWorld::CreateVector(Vector3& v, const Matrix4& m)
{
	v.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0];
	v.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1];
	v.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2];
	return v;
}
