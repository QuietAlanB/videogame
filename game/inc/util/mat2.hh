#ifndef MAT2_HH__
#define MAT2_HH__

#include <string>
#include <sstream>

#include "util/vec2.hh"

class mat2 {
public:
#ifdef COLUMN_MAJOR
	float m11, m21, m21, m22;
#else
	float m11, m12, m21, m22;
#endif

	mat2();
	mat2(float all);
	mat2(float m11, float m12, float m21, float m22);

	operator std::string() const {
		std::ostringstream oss;
		oss << '[' << m11 << ' ' << m12 << "]\n";
		oss << '[' << m21 << ' ' << m22 << ']';
		return oss.str();
	}

	// tirimid: the `+=`, `-=`, `*=`, etc. operations are not defined because it
	// makes matrix operations harder to understand in code.
	// the `*` operator for two matrices is standard matrix multiplication, for
	// per-element multiplicaton, use `hadamard()`.
	mat2 operator+(float rhs) const;
	mat2 operator-(float rhs) const;
	mat2 operator*(float rhs) const;
	mat2 operator/(float rhs) const;
	mat2 operator+(mat2 const &rhs) const;
	mat2 operator-(mat2 const &rhs) const;
	mat2 operator*(mat2 const &rhs) const;
	vec2 operator*(vec2 const &rhs) const;

	mat2 hadamard(mat2 const &other) const;
	float determinant() const;
};

#endif
