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
	class slot
	{
	public: //usings and stuff
		using reference = slot&;
		using const_reference = const slot&;
		using raw_function_ptr = t_return(*)(args...);
		using function = std::function<t_return(args...)>;

	public:
		slot() {
			this->_slot = 0;
		}

		slot(raw_function_ptr function) {
			this->_slot = function;
		}

		slot(function function) {
			this->_slot = function;
		}

		void set_slot(raw_function_ptr function) {
			this->_slot = function;
		}

		void set_slot(reference other) {
			*this = other;
		}

		//executes saved function
		t_return operator()(args... arguments) {
			if(this->is_set())
				return this->_slot(arguments...);
		}

		operator reference() {
			return *this;
		}

		operator const_reference() {
			return const_cast<slot>(this);
		}

		bool is_set() {
			return (_slot != 0);
		}

	private:
		function _slot;

	};//slot
}//namespace SCL
#endif // !SCL_SLOT_H