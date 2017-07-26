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

#ifndef SCL_SIGNAL_H
#define SCL_SIGNAL_H

#include <vector>
#include "slot.h"

#include <functional>

namespace SCL {

	template <class t_return, class... args>
	class signal
	{
	public:
		using reference = signal&;
		using const_reference = const signal&;
		using function_ptr = t_return(*)(args...);

	public:

		void connect(slot<t_return, args...> _slot) {
			_slots.push_back(_slot);
		}

		void connect(function_ptr _slot) {
			_slots.push_back(_slot);
		}

		void emit(args... arguments) {
			for (auto slot : _slots)
				slot(arguments...);
		}

	private:
		std::vector<std::function<t_return(args...)>> _slots;

	};//SCL::signal
}//SCL
#endif // !SCL_SIGNAL_H