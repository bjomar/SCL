#ifndef SCL_H
#define SCL_H

#include "signal.h"
#include "slot.h"


namespace SCL {

	//convert __thiscall method to _declcall method for signal usage
	template<class obj, class t_return, class... args>
	std::function<t_return(args...)> mem_fun(obj* _obj, t_return(obj::*memfun)(args...)) {
		return std::function<t_return(args...)>([=](args... arguments)->t_return {(_obj->*memfun)(arguments...); });
	}
}

#endif // !SCL_H