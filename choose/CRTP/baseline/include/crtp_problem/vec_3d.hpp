#pragma once
#include <crtp_problem/cloneable.hpp>
#include <crtp_problem/vec_2d.hpp>
#include <tuple>

namespace crtp_problem
{
/**
 * vec_3d represents a 3d vector $ \vec{v} = x \hat{i} + y \hat{j} + z \hat{k} $
 */
class vec_3d : cloneable
{
  private:
    double x;
    double y;
    double z;

  public:
    vec_3d(double x, double y, double z);
    vec_3d(const vec_2d &v);
    vec_3d &operator+=(const vec_3d &right);
    vec_3d &operator-=(const vec_3d &right);
    vec_3d &operator*=(double scale);
    vec_3d &operator/=(double scale);
    /**
     * @return 2-order norm of the vector
     */
    double norm() const;
    /**
     * dot product
     */
    double dot(const vec_3d &right) const;
    /**
     * cross product
     */
    vec_3d outer(const vec_3d &right) const;
    std::tuple<double, double, double> get_coordinate() const;
    virtual void *clone() const override;
};
} // namespace crtp_problem
