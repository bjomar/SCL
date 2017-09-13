// Copyright 2017 Björn Marx
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SCL_H
#define SCL_H

#define SCL_FUNCTION()

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