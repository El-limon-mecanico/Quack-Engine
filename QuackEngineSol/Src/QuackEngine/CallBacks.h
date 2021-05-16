#pragma once

#ifdef _MSC_VER
#  ifdef QUACK_ENGINE_PRO_EXPORT
#    define QUACK_ENGINE_PRO_API __declspec(dllexport)
#  else
#    define QUACK_ENGINE_PRO_API __declspec(dllimport)
#  endif
#endif

#include <cassert>
#include <functional>
#include <map>
#include <memory>
#include <string>

class QUACK_ENGINE_PRO_API CallBacks {

public:
	~CallBacks(){};
	
	static  CallBacks* Init();

	static CallBacks* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	void addMethod(std::string name, void (*func)());

	std::function<void()> getMethod(std::string name);

private:
	std::map<std::string, std::function<void()>> methods_;

	CallBacks();

protected:
	static std::unique_ptr<CallBacks> instance_;
};
