#include "CallBacks.h"

std::unique_ptr<CallBacks> CallBacks::instance_;

CallBacks::CallBacks()
{

}

CallBacks* CallBacks::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new CallBacks());
	return instance_.get();
}

void CallBacks::addMethod(std::string name, void(*func)())
{
	methods_.insert({ name, func });
}

std::function<void()> CallBacks::getMethod(std::string name)
{
	auto m = methods_.find(name);
	if (m != methods_.end())
		return (*m).second;
	else
		return []() {
		printf("La funci�n que ha guardado este bot�n no existe, comprueba el nombre de la funci�n, o si has guardado el m�todo");
	};

}
