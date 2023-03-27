#include "util/mat2.hh"

mat2::mat2() {
	this->m11 = this->m22 = 1.0f;
	this->m12 = this->m21 = 0.0f;
}

mat2::mat2(float all) {
	this->m11 = this->m12 = this->m21 = this->m22 = all;
}

mat2::mat2(float m11, float m12, float m21, float m22) {
	this->m11 = m11;
	this->m12 = m12;
	this->m21 = m21;
	this->m22 = m22;
}

mat2 mat2::operator+(float rhs) const {
	return mat2(m11 + rhs, m12 + rhs, m21 + rhs, m22 + rhs);
}

mat2 mat2::operator-(float rhs) const {
	return mat2(m11 - rhs, m12 - rhs, m21 - rhs, m22 - rhs);
}

mat2 mat2::operator*(float rhs) const {
	return mat2(m11 * rhs, m12 * rhs, m21 * rhs, m22 * rhs);
}

mat2 mat2::operator/(float rhs) const {
	return mat2(m11 / rhs, m12 / rhs, m21 / rhs, m22 / rhs);
}

mat2 mat2::operator+(mat2 const &rhs) const {
	return mat2(m11 + rhs.m11, m12 + rhs.m12, m21 + rhs.m21, m22 + rhs.m22);
}

mat2 mat2::operator-(mat2 const &rhs) const {
	return mat2(m11 - rhs.m11, m12 - rhs.m12, m21 - rhs.m21, m22 - rhs.m22);
}

mat2 mat2::operator*(mat2 const &rhs) const {
	float p_m11 = m11 * rhs.m11 + m12 * rhs.m21;
	float p_m12 = m11 * rhs.m12 + m12 * rhs.m22;
	float p_m21 = m21 * rhs.m11 + m22 * rhs.m21;
	float p_m22 = m21 * rhs.m12 + m22 * rhs.m22;
	return mat2(p_m11, p_m12, p_m21, p_m22);
}

vec2 mat2::operator*(vec2 const &rhs) const {
	return vec2(rhs.x * m11 + rhs.y * m12, rhs.x * m21 + rhs.y * m22);
}

mat2 mat2::hadamard(mat2 const &other) const {
	return mat2(m11 * other.m11, m12 * other.m12, m21 * other.m21,
	            m22 * other.m22);
}

float mat2::determinant() const {
	return m11 * m22 - m12 * m21;
}
