#include <concepts>
#include <iostream>
#include <type_traits>

namespace
{

// Option 1: Can use an array of requries
template <typename T>
concept canCallFunction = requires(T a) {
                              {
                                  a.custom_function()
                                  } -> std::same_as<std::string>;
                          };

// Option 2: Can create a chain of type traits
template <typename T>
concept canCallFunction2 =
    std::is_same_v<std::invoke_result_t<decltype(&T::custom_function2), T>,
                   std::string>;

struct testA
{
    [[nodiscard]] std::string custom_function() const { return s; }

  private:
    std::string s{"123"};
};

struct testB
{
};

struct testC
{
    [[nodiscard]] std::string custom_function2() const { return s; }

  private:
    std::string s{"456"};
};

// Apply requirement via template
template <canCallFunction T>
void callFn(const T& t)
{
    std::cout << "Custom " << t.custom_function() << '\n';
}

// Apply requirement via auto (abbreviated function template)
void callFn(const canCallFunction2 auto& t)
{
    std::cout << "Custom2 " << t.custom_function2() << '\n';
}

template <typename T>
void callFn(const T& /*t*/)
{
    std::cout << "Not custom\n";
}

} // namespace

int main()
{
    const testA a;
    const testB b;
    const testC c;

    callFn(a);
    callFn(b);
    callFn(c);
    return 0;
}
