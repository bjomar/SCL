/*
Copyright(c) 2017 github.com / bjomar
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

		void emit(args... arguments) {
			for (auto _slot : _slots)
				_slot(arguments...);
		}

		//emits signal and runs slots
		void emit(args... arguments, std::vector<t_return>* return_container) {
				for (auto _slot : _slots)
					return_container->push_back(_slot(arguments...));
		}

	private:
		std::vector<basic_slot<t_return, args...>> _slots;

	};//SCL::signal
}//SCL
#endif // !SCL_SIGNAL_H