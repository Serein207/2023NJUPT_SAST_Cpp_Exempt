#include <crtp_problem/vec_2d.hpp>
#include <crtp_problem/vec_3d.hpp>
#include <iostream>

using crtp_problem::vec_2d;
using crtp_problem::vec_3d;

int main()
{
    vec_2d v2d(3.0, 4.0);
    vec_3d v3d(3.0, 4.0, 5.0);
    std::cout << v2d.norm() << std::endl;
    v2d += v2d;
    std::cout << v2d.norm() << std::endl;
    v2d /= 2;
    std::cout << v2d.norm() << std::endl;
    std::cout << v3d.norm() << std::endl;

    vec_2d r(0, 0);
    vec_2d t1('a', 'l');
    vec_2d t2('a', 'm');
    vec_2d t3('p', 'y');
    r += t1;
    r += t2;
    r += t3;
    std::cout << r.norm() << std::endl;

    return 0;
}
