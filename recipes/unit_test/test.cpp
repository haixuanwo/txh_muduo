#include <iostream>

void show()
{
	std::cout << "global show" << std::endl;
}

class Test
{
	public:
		Test()
		{
			show();
			::show();
		}
	
	void show()
	{
		std::cout << "Test show" << std::endl;
	}
};

int main()
{
	Test T;
	return 0;
}
