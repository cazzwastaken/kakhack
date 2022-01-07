#include "entity.h"

#include "../../core/interfaces.h"

Matrix3x4* BaseEntity::GetBoneMatrix()
{
	Matrix3x4 matrix[256];

	if (this->SetupBones(matrix, 256, 256, i::globals->currentTime))
		return matrix;
	else
		return nullptr;
}

Vector BaseEntity::GetBonePosition(int bone)
{
	Matrix3x4 matrix[256];

	if (this->SetupBones(matrix, 256, 256, i::globals->currentTime))
		return matrix[bone].at(3);
	else
		return { };
}
