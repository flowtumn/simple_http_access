#include <iostream>

int main() {
	[]{
		std::cout << __FUNCTION__ << std::endl;
	}();
}
