#pragma once

// SFINAE test
template <typename T>
class HasGetName
{
	typedef char one;
	struct two { char x[2]; };

	template <typename C> static one test(decltype(&C::GetName));
	template <typename C> static two test(...);

public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

#define PRINT_ERROR_GETNAME std::cout << "ERROR: Component doesn't implement Component::GetName() public static method.\nEvery Component must implement this method."