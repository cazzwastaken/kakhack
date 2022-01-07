#pragma once
#include "vector.h"

using Matrix3x3 = float[3][3];
struct Matrix3x4
{
	Matrix3x4() = default;

	constexpr Matrix3x4(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23)
	{
		data[0][0] = m00; data[0][1] = m01; data[0][2] = m02; data[0][3] = m03;
		data[1][0] = m10; data[1][1] = m11; data[1][2] = m12; data[1][3] = m13;
		data[2][0] = m20; data[2][1] = m21; data[2][2] = m22; data[2][3] = m23;
	}

	constexpr Matrix3x4(const Vector& x, const Vector& y, const Vector& z, const Vector& origin)
	{
		Init(x, y, z, origin);
	}

	constexpr void Init(const Vector& forward, const Vector& left, const Vector& up, const Vector& origin)
	{
		SetForward(forward);
		SetLeft(left);
		SetUp(up);
		SetOrigin(origin);
	}

	constexpr void SetForward(const Vector& forward)
	{
		this->data[0][0] = forward.x;
		this->data[1][0] = forward.y;
		this->data[2][0] = forward.z;
	}

	constexpr void SetLeft(const Vector& left)
	{
		this->data[0][1] = left.x;
		this->data[1][1] = left.y;
		this->data[2][1] = left.z;
	}

	constexpr void SetUp(const Vector& up)
	{
		this->data[0][2] = up.x;
		this->data[1][2] = up.y;
		this->data[2][2] = up.z;
	}

	constexpr void SetOrigin(const Vector& origin)
	{
		this->data[0][3] = origin.x;
		this->data[1][3] = origin.y;
		this->data[2][3] = origin.z;
	}

	constexpr void Invalidate()
	{
		for (auto& subData : data)
		{
			for (auto& number : subData)
				number = std::numeric_limits<float>::infinity();
		}
	}

	float* operator[](const int index)
	{
		return data[index];
	}

	const float* operator[](const int index) const
	{
		return data[index];
	}

	[[nodiscard]] constexpr Vector at(const int index) const
	{
		return Vector(data[0][index], data[1][index], data[2][index]);
	}

	float* Base()
	{
		return &data[0][0];
	}

	[[nodiscard]] const float* Base() const
	{
		return &data[0][0];
	}

	float data[3][4] = { };
};

__declspec(align(16)) class Matrix3x4a : public Matrix3x4
{
public:
	Matrix3x4a& operator=(const Matrix3x4& source)
	{
		std::copy_n(source.Base(), sizeof(float) * 3U * 4U, this->Base());
		return *this;
	}
};

struct ViewMatrix
{
	ViewMatrix() = default;

	constexpr ViewMatrix(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33)
	{
		data[0][0] = m00; data[0][1] = m01; data[0][2] = m02; data[0][3] = m03;
		data[1][0] = m10; data[1][1] = m11; data[1][2] = m12; data[1][3] = m13;
		data[2][0] = m20; data[2][1] = m21; data[2][2] = m22; data[2][3] = m23;
		data[3][0] = m30; data[3][1] = m31; data[3][2] = m32; data[3][3] = m33;
	}

	constexpr ViewMatrix(const Matrix3x4& from, const Vector4D& additionalColumn = { })
	{
		data[0][0] = from.data[0][0]; data[0][1] = from.data[0][1]; data[0][2] = from.data[0][2]; data[0][3] = from.data[0][3];
		data[1][0] = from.data[1][0]; data[1][1] = from.data[1][1]; data[1][2] = from.data[1][2]; data[1][3] = from.data[1][3];
		data[2][0] = from.data[2][0]; data[2][1] = from.data[2][1]; data[2][2] = from.data[2][2]; data[2][3] = from.data[2][3];
		data[3][0] = additionalColumn.x; data[3][1] = additionalColumn.y; data[3][2] = additionalColumn.z; data[3][3] = additionalColumn.w;
	}

	float* operator[](const int index)
	{
		return data[index];
	}

	const float* operator[](const int index) const
	{
		return data[index];
	}

	[[nodiscard]] constexpr Vector4D at(const int index) const
	{
		return Vector4D(data[0][index], data[1][index], data[2][index], data[3][index]);
	}

	constexpr ViewMatrix& operator+=(const ViewMatrix& add)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int n = 0; n < 4; n++)
				this->data[i][n] += add[i][n];
		}

		return *this;
	}

	constexpr ViewMatrix& operator-=(const ViewMatrix& subtract)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int n = 0; n < 4; n++)
				this->data[i][n] -= subtract[i][n];
		}

		return *this;
	}

	ViewMatrix operator*(const ViewMatrix& multiply) const
	{
		return ViewMatrix(
			data[0][0] * multiply.data[0][0] + data[0][1] * multiply.data[1][0] + data[0][2] * multiply.data[2][0] + data[0][3] * multiply.data[3][0],
			data[0][0] * multiply.data[0][1] + data[0][1] * multiply.data[1][1] + data[0][2] * multiply.data[2][1] + data[0][3] * multiply.data[3][1],
			data[0][0] * multiply.data[0][2] + data[0][1] * multiply.data[1][2] + data[0][2] * multiply.data[2][2] + data[0][3] * multiply.data[3][2],
			data[0][0] * multiply.data[0][3] + data[0][1] * multiply.data[1][3] + data[0][2] * multiply.data[2][3] + data[0][3] * multiply.data[3][3],

			data[1][0] * multiply.data[0][0] + data[1][1] * multiply.data[1][0] + data[1][2] * multiply.data[2][0] + data[1][3] * multiply.data[3][0],
			data[1][0] * multiply.data[0][1] + data[1][1] * multiply.data[1][1] + data[1][2] * multiply.data[2][1] + data[1][3] * multiply.data[3][1],
			data[1][0] * multiply.data[0][2] + data[1][1] * multiply.data[1][2] + data[1][2] * multiply.data[2][2] + data[1][3] * multiply.data[3][2],
			data[1][0] * multiply.data[0][3] + data[1][1] * multiply.data[1][3] + data[1][2] * multiply.data[2][3] + data[1][3] * multiply.data[3][3],

			data[2][0] * multiply.data[0][0] + data[2][1] * multiply.data[1][0] + data[2][2] * multiply.data[2][0] + data[2][3] * multiply.data[3][0],
			data[2][0] * multiply.data[0][1] + data[2][1] * multiply.data[1][1] + data[2][2] * multiply.data[2][1] + data[2][3] * multiply.data[3][1],
			data[2][0] * multiply.data[0][2] + data[2][1] * multiply.data[1][2] + data[2][2] * multiply.data[2][2] + data[2][3] * multiply.data[3][2],
			data[2][0] * multiply.data[0][3] + data[2][1] * multiply.data[1][3] + data[2][2] * multiply.data[2][3] + data[2][3] * multiply.data[3][3],

			data[3][0] * multiply.data[0][0] + data[3][1] * multiply.data[1][0] + data[3][2] * multiply.data[2][0] + data[3][3] * multiply.data[3][0],
			data[3][0] * multiply.data[0][1] + data[3][1] * multiply.data[1][1] + data[3][2] * multiply.data[2][1] + data[3][3] * multiply.data[3][1],
			data[3][0] * multiply.data[0][2] + data[3][1] * multiply.data[1][2] + data[3][2] * multiply.data[2][2] + data[3][3] * multiply.data[3][2],
			data[3][0] * multiply.data[0][3] + data[3][1] * multiply.data[1][3] + data[3][2] * multiply.data[2][3] + data[3][3] * multiply.data[3][3]);
	}

	constexpr void Identity()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int n = 0; n < 4; n++)
				this->data[i][n] = i == n ? 1.0f : 0.0f;
		}
	}

	const Matrix3x4& As3x4() const
	{
		return *reinterpret_cast<const Matrix3x4*>(this);
	}

	Matrix3x4& As3x4()
	{
		return *reinterpret_cast<Matrix3x4*>(this);
	}

	float data[4][4] = { };
};
