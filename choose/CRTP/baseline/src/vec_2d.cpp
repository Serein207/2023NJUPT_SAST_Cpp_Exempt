#include <cmath>
#include <crtp_problem/vec_2d.hpp>

using crtp_problem::vec_2d;

vec_2d::vec_2d(double x, double y) : x(x), y(y)
{
}

vec_2d &vec_2d::operator+=(const vec_2d &right)
{
    this->x += right.x;
    this->y += right.y;
    return *this;
}

vec_2d &vec_2d::operator-=(const vec_2d &right)
{
    this->x -= right.x;
    this->y -= right.y;
    return *this;
}

vec_2d &vec_2d::operator*=(double scale)
{
    this->x *= scale;
    this->y *= scale;
    return *this;
}

vec_2d &vec_2d::operator/=(double scale)
{
    this->x /= scale;
    this->y /= scale;
    return *this;
}

double vec_2d::norm() const
{
    return std::sqrt(this->x * this->x + this->y * this->y);
}

double vec_2d::dot(const vec_2d &right) const
{
    return this->x * right.x + this->y * right.y;
}

std::tuple<double, double> vec_2d::get_coordinate() const
{
    return std::make_tuple(this->x, this->y);
}

void *vec_2d::clone() const
{
    return new vec_2d(*this);
}
