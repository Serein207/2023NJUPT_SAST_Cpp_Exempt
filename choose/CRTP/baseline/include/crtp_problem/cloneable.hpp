#pragma once

namespace crtp_problem
{
class cloneable
{
  public:
    virtual void *clone() const = 0;
};
} // namespace crtp_problem
