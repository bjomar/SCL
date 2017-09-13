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

#ifndef SCL_SLOT_H
#define SCL_SLOT_H

#include <functional>

namespace SCL {

	template<class t_return, class... args>
	class basic_slot
	{
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
			if(*this)
				return this->_slot(arguments...);
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