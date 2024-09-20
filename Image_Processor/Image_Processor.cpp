// Image_Processor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ImageIOFactory.hpp"
#include "UserInterface.h"

int main()
{
	UserInterface::getInstance().run();	
}

