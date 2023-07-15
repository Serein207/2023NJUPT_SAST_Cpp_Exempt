#pragma once
#include <crtp_problem/cloneable.hpp>
#include <tuple>

namespace crtp_problem
{
/**
 * vec_2d represents a 2d vector $ \vec{v} = x \hat{i} + y \hat{j} $
 */
class vec_2d : cloneable
{
  private:
    double x;
    double y;

  public:
    vec_2d(double x, double y);
    vec_2d &operator+=(const vec_2d &right);
    vec_2d &operator-=(const vec_2d &right);
    vec_2d &operator*=(double scale);
    vec_2d &operator/=(double scale);
    /**
     * @return 2-order norm of the vector
     */
    double norm() const;
    /**
     * dot product
     */
    double dot(const vec_2d &right) const;
    std::tuple<double, double> get_coordinate() const;
    virtual void *clone() const override;
};
} // namespace crtp_problem
