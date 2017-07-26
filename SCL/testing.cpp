#include "SCL.h"
#include <iostream>

class foo;

void foobar();

class foo
{
public:
	foo() {
		_signal.connect(SCL::slot<void>(SCL::mem_fun<foo, void>(this, &foo::bar)));
		_signal.connect(&foobar);
	}

	void bar() {
		std::cout << "this is foo::bar()!\n";
	}

	SCL::signal<void> _signal;

private:
};

void foobar() {
	std::cout << "this is global foobar()!";
}

int main(int argc, char** argv) {

	foo f;

	f._signal.emit();

	system("pause");
}