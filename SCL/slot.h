/*
Copyright(c) 2017 Björn Marx
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SCL_SLOT_H
#define SCL_SLOT_H

#include <functional>

namespace SCL {

	template<class t_return, class... args>
	class basic_slot {

	public: //usings and stuff
		using reference = basic_slot&;
		using const_reference = const basic_slot&;
		using raw_function_ptr = t_return(*)(args...);
		using function = std::function<t_return(args...)>;

	public:
		basic_slot() {
			this->_slot = 0;
			this->_name = 0;
		}

		basic_slot(raw_function_ptr function, char* name) {
			this->_slot = function;
			_name = name;
		}

		basic_slot(function function, char* name) {
			this->_slot = function;
			_name = name;
		}

		void set_slot(raw_function_ptr function, char* name) {
			this->_slot = function;
			_name = name;
		}

		//executes saved function
		t_return operator()(args... arguments) {
			if(*this) {
				return this->_slot(arguments...);
			}
		}

		operator reference() {
			return *this;
		}

		operator const_reference() {
			return const_cast<slot>(this);
		}

		operator bool() {
			return this->is_set();
		}

		bool is_set() {
			return ((_slot != 0) && (_name != 0));
		}

		const char* name() const {
			return _name;
		}

	private:
		function _slot;
		char* _name;

	};//slot
}//namespace SCL
#endif // !SCL_SLOT_H