#include "array.h"
#include "dummy.h"
#include "tests.h"

template <typename ...Callable>
inline void call(Callable... callable)  { (callable(), ...); }

int main()
{
    call( test1, test2, test3 );
	return 0;
}

