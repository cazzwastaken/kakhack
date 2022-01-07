#pragma once
#include <cmath>
#include <limits>
#include <numbers>

class Vector2D
{
public:
	constexpr Vector2D(float x = 0.f, float y = 0.f) :
		x(x), y(y) { }

	[[nodiscard]] bool IsZero() const
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO);
	}

public:
	float x, y;
};

class Vector
{
public:
	constexpr Vector(float x = 0.f, float y = 0.f, float z = 0.f) :
		x(x), y(y), z(z) { }

	constexpr Vector(const float* vec) :
		x(vec[0]), y(vec[1]), z(vec[2]) { }

	constexpr Vector(const Vector2D& vec) :
		x(vec.x), y(vec.y), z(0.0f) { }

	[[nodiscard]] bool IsValid() const
	{
		return std::isfinite(this->x) && std::isfinite(this->y) && std::isfinite(this->z);
	}

	constexpr void Invalidate()
	{
		this->x = this->y = this->z = std::numeric_limits<float>::infinity();
	}

	[[nodiscard]] float* data()
	{
		return reinterpret_cast<float*>(this);
	}

	[[nodiscard]] const float* data() const
	{
		return reinterpret_cast<float*>(const_cast<Vector*>(this));
	}

	float& operator[](const std::size_t i)
	{
		return this->data()[i];
	}

	const float& operator[](const std::size_t i) const
	{
		return this->data()[i];
	}

	bool operator==(const Vector& vec) const
	{
		return this->IsEqual(vec);
	}

	bool operator!=(const Vector& vec) const
	{
		return !this->IsEqual(vec);
	}

	constexpr Vector& operator=(const Vector& vec)
	{
		this->x = vec.x; this->y = vec.y; this->z = vec.z;
		return *this;
	}

	constexpr Vector& operator=(const Vector2D& vec2D)
	{
		this->x = vec2D.x; this->y = vec2D.y; this->z = 0.0f;
		return *this;
	}

	constexpr Vector& operator+=(const Vector& vec)
	{
		this->x += vec.x; this->y += vec.y; this->z += vec.z;
		return *this;
	}

	constexpr Vector& operator-=(const Vector& vec)
	{
		this->x -= vec.x; this->y -= vec.y; this->z -= vec.z;
		return *this;
	}

	constexpr Vector& operator*=(const Vector& vec)
	{
		this->x *= vec.x; this->y *= vec.y; this->z *= vec.z;
		return *this;
	}

	constexpr Vector& operator/=(const Vector& vec)
	{
		this->x /= vec.x; this->y /= vec.y; this->z /= vec.z;
		return *this;
	}

	constexpr Vector& operator+=(const float add)
	{
		this->x += add; this->y += add; this->z += add;
		return *this;
	}

	constexpr Vector& operator-=(const float subtract)
	{
		this->x -= subtract; this->y -= subtract; this->z -= subtract;
		return *this;
	}

	constexpr Vector& operator*=(const float multiply)
	{
		this->x *= multiply; this->y *= multiply; this->z *= multiply;
		return *this;
	}

	constexpr Vector& operator/=(const float divide)
	{
		this->x /= divide; this->y /= divide; this->z /= divide;
		return *this;
	}

	Vector operator+(const Vector& add) const
	{
		return Vector(this->x + add.x, this->y + add.y, this->z + add.z);
	}

	Vector operator-(const Vector& subtract) const
	{
		return Vector(this->x - subtract.x, this->y - subtract.y, this->z - subtract.z);
	}

	Vector operator*(const Vector& multiply) const
	{
		return Vector(this->x * multiply.x, this->y * multiply.y, this->z * multiply.z);
	}

	Vector operator/(const Vector& divide) const
	{
		return Vector(this->x / divide.x, this->y / divide.y, this->z / divide.z);
	}

	Vector operator+(const float add) const
	{
		return Vector(this->x + add, this->y + add, this->z + add);
	}

	Vector operator-(const float subtract) const
	{
		return Vector(this->x - subtract, this->y - subtract, this->z - subtract);
	}

	Vector operator*(const float multiply) const
	{
		return Vector(this->x * multiply, this->y * multiply, this->z * multiply);
	}

	Vector operator/(const float divide) const
	{
		return Vector(this->x / divide, this->y / divide, this->z / divide);
	}

	[[nodiscard]] bool IsEqual(const Vector& equal, const float errorMargin = std::numeric_limits<float>::epsilon()) const
	{
		return (std::fabsf(this->x - equal.x) < errorMargin &&
			std::fabsf(this->y - equal.y) < errorMargin &&
			std::fabsf(this->z - equal.z) < errorMargin);
	}

	[[nodiscard]] bool IsZero() const
	{
		return (std::fpclassify(this->x) == FP_ZERO &&
			std::fpclassify(this->y) == FP_ZERO &&
			std::fpclassify(this->z) == FP_ZERO);
	}

	[[nodiscard]] Vector2D ToVector2D() const
	{
		return Vector2D(this->x, this->y);
	}

	[[nodiscard]] float Length() const
	{
		return std::sqrtf(this->LengthSqr());
	}

	[[nodiscard]] constexpr float LengthSqr() const
	{
		return DotProduct(*this);
	}

	[[nodiscard]] float Length2D() const
	{
		return std::sqrtf(this->Length2DSqr());
	}

	[[nodiscard]] constexpr float Length2DSqr() const
	{
		return (this->x * this->x + this->y * this->y);
	}

	[[nodiscard]] float DistTo(const Vector& end) const
	{
		return (*this - end).Length();
	}

	[[nodiscard]] constexpr float DistToSqr(const Vector& end) const
	{
		return (*this - end).LengthSqr();
	}

	[[nodiscard]] Vector Normalized() const
	{
		Vector vecOut = *this;
		vecOut.NormalizeInPlace();
		return vecOut;
	}

	float NormalizeInPlace()
	{
		const float flLength = this->Length();
		const float flRadius = 1.0f / (flLength + std::numeric_limits<float>::epsilon());

		this->x *= flRadius;
		this->y *= flRadius;
		this->z *= flRadius;

		return flLength;
	}

	[[nodiscard]] constexpr float DotProduct(const Vector& dot) const
	{
		return (this->x * dot.x + this->y * dot.y + this->z * dot.z);
	}

	[[nodiscard]] constexpr Vector CrossProduct(const Vector& cross) const
	{
		return Vector(this->y * cross.z - this->z * cross.y, this->z * cross.x - this->x * cross.z, this->x * cross.y - this->y * cross.x);
	}

	static constexpr auto Deg2Rad(float degrees) noexcept
	{
		return degrees * (std::numbers::pi_v<float> / 180.0f);
	}

	static constexpr auto Rad2Deg(float radians) noexcept
	{
		return radians * (180.0f / std::numbers::pi_v<float>);
	}

	Vector constexpr ToAngle() const noexcept
	{
		return Vector{ Rad2Deg(std::atan2(-z, std::hypot(x, y))),
					   Rad2Deg(std::atan2(y, x)),
					   0.0f };
	}

	static Vector FromAngle(const Vector& angle) noexcept
	{
		return Vector{ std::cos(Deg2Rad(angle.x)) * std::cos(Deg2Rad(angle.y)),
					   std::cos(Deg2Rad(angle.x)) * std::sin(Deg2Rad(angle.y)),
					  -std::sin(Deg2Rad(angle.x)) };
	}

	static inline Vector RelativeAngle(const Vector& source, const Vector& destination, const Vector& viewAngles)
	{
		return ((destination - source).ToAngle() - viewAngles);
	}

public:
	float x, y, z;
};

class Vector4D
{
public:
	constexpr Vector4D(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) :
		x(x), y(y), z(z), w(w) { }

public:
	float x, y, z, w;
};

class __declspec(align(16)) VectorAligned : public Vector
{
public:
	VectorAligned() = default;

	explicit VectorAligned(const Vector& base)
	{
		this->x = base.x; this->y = base.y; this->z = base.z; this->w = 0.f;
	}

	constexpr VectorAligned& operator=(const Vector& base)
	{
		this->x = base.x; this->y = base.y; this->z = base.z; this->w = 0.f;
		return *this;
	}

public:
	float w;
};
