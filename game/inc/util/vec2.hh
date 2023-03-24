#ifndef VEC2_HH__
#define VEC2_HH__

#include <string>

class vec2 {
public:
	float x, y;
	
	vec2();
	vec2(float all);
	vec2(float x, float y);

	operator std::string() {
		return "[" + std::to_string(x) + " " + std::to_string(y) + "]";
	}

	vec2 operator+(float rhs);
	vec2 operator-(float rhs);
	vec2 operator*(float rhs);
	vec2 operator/(float rhs);
	void operator+=(float rhs);
	void operator-=(float rhs);
	void operator*=(float rhs);
	void operator/=(float rhs);

	// tirimid: lengthwise operations.
	// `lhs * rhs` is NOT dot product - use `lhs.dot(rhs)` instead.
	vec2 operator+(vec2 const &rhs);
	vec2 operator-(vec2 const &rhs);
	vec2 operator*(vec2 const &rhs);
	vec2 operator/(vec2 const &rhs);
	void operator+=(vec2 const &rhs);
	void operator-=(vec2 const &rhs);
	void operator*=(vec2 const &rhs);
	void operator/=(vec2 const &rhs);

	bool operator==(vec2 const &rhs);
	bool operator!=(vec2 const &rhs);

	float magnitude();
	vec2 normalized();
	float dot(vec2 const &other);
};

#endif
