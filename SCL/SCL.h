/*
Copyright(c) 2017 Bj�rn Marx
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SCL_H
#define SCL_H

#define SCL_STRINGYFY(x) #x
#define SCL_FUN(_function) &_function, SCL_STRINGYFY(_function)

#include "signal.h"
#include "slot.h"

namespace SCL {

	//convert member function to slot
	template<class obj, class t_return, class... args>
	basic_slot<t_return, args...> mem_fun(obj* _obj, t_return(obj::*memfun)(args...), char* name) {
		return basic_slot<t_return, args...>([=](args... arguments)->t_return { 
			return (_obj->*memfun)(arguments...); 
		}, name);
	}

	//convert global function to slot
	template<class t_return, class... args>
	basic_slot<t_return, args...> fun(t_return(*fun)(args...), char* name) {
		return basic_slot<t_return, args...>(fun, name);
	}
}

#endif // !SCL_H