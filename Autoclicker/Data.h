#pragma once

#include <vector>

typedef unsigned int UINT;

namespace Data {
	struct SimpleMacro {
		char name[20];
		UINT id;
		int key;
		int delay;
	};

	static std::vector<Data::SimpleMacro> simpleMacros;
}
