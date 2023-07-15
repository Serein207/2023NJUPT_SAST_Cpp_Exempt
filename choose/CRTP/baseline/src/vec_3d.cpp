#include <cmath>
#include <crtp_problem/vec_3d.hpp>

using crtp_problem::vec_2d;
using crtp_problem::vec_3d;

vec_3d::vec_3d(double x, double y, double z) : x(x), y(y), z(z)
{
}

vec_3d::vec_3d(const vec_2d &v) : x(0), y(0), z(0)
{
    auto [x_2d, y_2d] = v.get_coordinate();
    this->x = x_2d;
    this->y = y_2d;
}

vec_3d &vec_3d::operator+=(const vec_3d &right)
{
    this->x += right.x;
    this->y += right.y;
    this->z += right.z;
    return *this;
}

vec_3d &vec_3d::operator-=(const vec_3d &right)
{
    this->x -= right.x;
    this->y -= right.y;
    this->z -= right.z;
    return *this;
}

vec_3d &vec_3d::operator*=(double scale)
{
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;
    return *this;
}

vec_3d &vec_3d::operator/=(double scale)
{
    this->x /= scale;
    this->y /= scale;
    this->z /= scale;
    return *this;
}

double vec_3d::norm() const
{
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

double vec_3d::dot(const vec_3d &right) const
{
    return this->x * right.x + this->y * right.y + this->z * right.z;
}

vec_3d vec_3d::outer(const vec_3d &right) const
{
    auto result_x = this->y * right.z - this->z * right.y;
    auto result_y = this->z * right.x - this->x * right.z;
    auto result_z = this->x * right.y - this->y * right.x;
    return vec_3d(result_x, result_y, result_z);
}

std::tuple<double, double, double> vec_3d::get_coordinate() const
{
    return std::make_tuple(this->x, this->y, this->z);
}

void *vec_3d::clone() const
{
    return new vec_3d(*this);
}
