#include <coroutine>
#include <iostream>
#include <random>

struct generator {
    struct promise_type {
        int _value;

        generator get_return_object() {
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
        // TODO: finish your code here
    };

    std::coroutine_handle<promise_type> _h;
    operator std::coroutine_handle<promise_type>() const { return _h; }
};

generator getRandomNum() {
    std::srand((unsigned)time(NULL));
    for (int i = 0; i < 10; ++i) {
        /*TODO: finish your code here*/ std::rand() % 100;
    }
}

int main() {
    auto h = getRandomNum()._h;
    auto& promise = h.promise();
    for (int i = 0; i < 10; ++i) {
        int input;
        std::cout << "please input a number less than 100: ";
        std::cin >> input;
        std::cout << (input > promise._value
                          ? "too more"
                          : (input < promise._value ? "too less"
                                                    : "you are right!"))
                  << std::endl;
        // TODO:  break the loop
    }
    h.destroy();
}