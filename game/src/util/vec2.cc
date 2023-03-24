#include "util/vec2.hh"

#include <cmath>

vec2::vec2() {
	x = y = 0.0f;
}

vec2::vec2(float all) {
	x = y = all;
}

vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

vec2 vec2::operator+(float rhs) {
	return vec2(x + rhs, y + rhs);
}

vec2 vec2::operator-(float rhs) {
	return vec2(x - rhs, y - rhs);
}

vec2 vec2::operator*(float rhs) {
	return vec2(x * rhs, y * rhs);
}

vec2 vec2::operator/(float rhs) {
	return vec2(x / rhs, y / rhs);
}

void vec2::operator+=(float rhs) {
	x += rhs;
	y += rhs;
}

void vec2::operator-=(float rhs) {
	x -= rhs;
	y -= rhs;
}

void vec2::operator*=(float rhs) {
	x *= rhs;
	y *= rhs;
}

void vec2::operator/=(float rhs) {
	x /= rhs;
	y /= rhs;
}

vec2 vec2::operator+(vec2 const &rhs) {
	return vec2(x + rhs.x, y + rhs.y);
}

vec2 vec2::operator-(vec2 const &rhs) {
	return vec2(x - rhs.x, y - rhs.y);
}

vec2 vec2::operator*(vec2 const &rhs) {
	return vec2(x * rhs.x, y * rhs.y);
}

vec2 vec2::operator/(vec2 const &rhs) {
	return vec2(x / rhs.x, y / rhs.y);
}

void vec2::operator+=(vec2 const &rhs) {
	x += rhs.x;
	y += rhs.y;
}

void vec2::operator-=(vec2 const &rhs) {
	x -= rhs.x;
	y -= rhs.y;
}

void vec2::operator*=(vec2 const &rhs) {
	x *= rhs.x;
	y *= rhs.y;
}

void vec2::operator/=(vec2 const &rhs) {
	x /= rhs.x;
	y /= rhs.y;
}

bool vec2::operator==(vec2 const &rhs) {
	return x == rhs.x && y == rhs.y;
}

bool vec2::operator!=(vec2 const &rhs) {
	return x != rhs.x || y != rhs.y;
}

float vec2::magnitude() {
	return sqrt(x * x + y * y);
}

vec2 vec2::normalized() {
#ifdef FAST_INVERSE_SQRT
	float num = x * x + y * y, x2 = num * 0.5f;
	long i = *(long *)&num;
	i = 0x5f3759df - (i >> 1);
	num = *(float *)&i;
	num = num * (1.5f - (x2 * num * num));
#else
	float num = 1.0f / sqrt(x * x + y * y);
#endif

	return vec2(x / num, y / num);
}

float vec2::dot(vec2 const &other) {
	return x * other.x + y * other.y;
}
