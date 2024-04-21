#include "Common.h"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::filesystem::current_path;

void Compile()
{
	system(".\\compiler.bat");
}