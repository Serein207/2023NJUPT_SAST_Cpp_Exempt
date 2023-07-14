#include <iostream>
#include <type_traits>

/*-----------------------*/
/*                       */
/*   fulfill your code   */
/*                       */
/*-----------------------*/

/*以下也是提示，其实是可以用单独一个c++14扩展的constexpr函数解决欧拉函数判定的
constexpr unsigned int eulerFunction(unsigned int n)
{

}
*/

// 序列生成器可以参考链接中的编译期质数序列，夹带私货++，嘿嘿

int main() {
    constexpr int N = 30;
    for (auto i = 0; i < EulerFunctionList<N>::length; i++) {
        std::cout << EulerFunctionList<N>::value[i] << " ";
    }
    return 0;
}