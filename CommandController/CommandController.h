#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <unordered_map>
#include <functional>
#include <sstream>

template<typename T>
T convert2(std::string s)
{
	T t;
	std::stringstream ss(s);
	ss >> t;
	return t;
}

class CommandController
{
	template<typename... Args, std::size_t... I>
	auto convert(void(*f)(Args...), std::index_sequence<I...>)
	{
		return [f](std::vector<std::string> option) {
			if (option.size() != sizeof...(Args))
				throw std::exception("parameter not match.");
			f(convert2<Args>(option[I])...);
		};
	}

public:
	template<typename... Args>
	void regist(const std::string &key, void(*f)(Args...))
	{
		container[key] = convert(f, std::make_index_sequence<sizeof...(Args)>());
	}

	void call(std::vector<std::string> command)
	{
		auto it = container.find(command.front());
		if (it != container.end())
		{
			std::vector<std::string> option(command.begin() + 1, command.end());
			it->second(option);
		}
	}

private:
	std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> container;
};