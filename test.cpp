#include <iostream>
#include <cstring>

int main()
{
				const char * a = "1234";
				const char * b = "1234";
				if (std::strcmp(a,b)){
					std::cout << a << " == " << b << std::endl;
				}else
				{
					std::cout << a << " != " << b << std::endl;
				}
				return 0;
}
