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
	class basic_signal
	{
	public:
		using reference = basic_signal&;
		using const_reference = const basic_signal&;
		using function_ptr = t_return(*)(args...);

	public:
		void connect(basic_slot<t_return, args...> _slot) {
			_slots.push_back(_slot);
		}

		void connect(function_ptr _slot, char* fun_name) {
			_slots.push_back(basic_slot<t_return, args...>(_slot, fun_name));
		}

		// disconenct first function whos name equals function_name
		// returns true on success
		bool disconnect(const char* function_name) {
			for (size_t i = 0; i < _slots.size(); i++)
				if (_slots.at(i).name() == function_name)
				{
					_slots.erase(_slots.begin() + i);

					return true;
				}
			return false;
		}

		bool disconnect() {
			this->_slots.clear();

			return _slots.empty();
		}

		//emits signal and runs slots
		//
		void emit(args... arguments, std::vector<t_return>* return_container) {
			if (!return_container)
				for (auto _slot : _slots)
					_slot(arguments...);
			else
				for (auto _slot : _slots)
					return_container->push_back(_slot(arguments...));
		}

	private:
		std::vector<basic_slot<t_return, args...>> _slots;

	};//SCL::signal
}//SCL
#endif // !SCL_SIGNAL_H