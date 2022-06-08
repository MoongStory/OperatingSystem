#include "OperatingSystem.h"
#include "../../Registry/Registry/Registry.h" // https://github.com/MoongStory/Registry

#include <Windows.h>

const std::string MOONG::OperatingSystem::GetWindowsProductName()
{
	std::string windows_version;

	std::string output;
	MOONG::Registry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName", output);

	windows_version = output;

	output.erase();
	MOONG::Registry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CSDVersion", output);
	if(output.empty() == false)
	{
		windows_version += " ";
		windows_version += output;
	}

	return windows_version;
}