#ifndef SCL_H
#define SCL_H

#define SCL_STRINGYFY(x) #x
#define SCL_FUN(_function) &_function, SCL_STRINGYFY(_function)

#include "signal.h"
#include "slot.h"

namespace SCL {

	//convert member function to slot
	//don't touch unless you know what you are doing
	template<class obj, class t_return, class... args>
	slot<t_return, args...> mem_fun(obj* _obj, t_return(obj::*memfun)(args...), char* name) {
		return slot<t_return, args...>([=](args... arguments)->t_return { return (_obj->*memfun)(arguments...); }, name);
	}

	//convert global function to slot
	template<class t_return, class... args>
	slot<t_return, args...> fun(t_return(*fun)(args...), char* name) {
		return slot<t_return, args...>(fun, name);
	}
}

#endif // !SCL_H