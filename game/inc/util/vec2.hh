#ifndef VEC2_HH__
#define VEC2_HH__

#include <sstream>
#include <string>

class vec2 {
public:
	float x, y;
	
	vec2();
	vec2(float all);
	vec2(float x, float y);

	operator std::string() const {
		std::ostringstream oss;
		oss << '[' << x << ' ' << y << ']';
		return oss.str();
	}

	vec2 operator+(float rhs) const;
	vec2 operator-(float rhs) const;
	vec2 operator*(float rhs) const;
	vec2 operator/(float rhs) const;
	void operator+=(float rhs);
	void operator-=(float rhs);
	void operator*=(float rhs);
	void operator/=(float rhs);

	// tirimid: lengthwise operations.
	// `lhs * rhs` is NOT dot product - use `lhs.dot(rhs)` instead.
	vec2 operator+(vec2 const &rhs) const;
	vec2 operator-(vec2 const &rhs) const;
	vec2 operator*(vec2 const &rhs) const;
	vec2 operator/(vec2 const &rhs) const;
	void operator+=(vec2 const &rhs);
	void operator-=(vec2 const &rhs);
	void operator*=(vec2 const &rhs);
	void operator/=(vec2 const &rhs);

	bool operator==(vec2 const &rhs) const;
	bool operator!=(vec2 const &rhs) const;

	float magnitude() const;
	vec2 normalized() const;
	float dot(vec2 const &other) const;
};

#endif
