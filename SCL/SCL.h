#ifndef SCL_H
#define SCL_H

#include "signal.h"
#include "slot.h"


namespace SCL {

	//convert member function to lambda wich is usable by std::function for signals
	//currently only works with 0 arguments (class... args)
	//args template argument pack is WIP; just ignore that is is there
	//TODO:
	//	fix so it works with x args
	template<class obj, class t_return, class... args>
	std::function<t_return(args...)> mem_fun(obj* _obj, t_return(obj::*memfun)(args...)) {
		return std::function<t_return(args...)>([=]()->t_return {(_obj->*memfun)(args...); });
	}
}

#endif // !SCL_H