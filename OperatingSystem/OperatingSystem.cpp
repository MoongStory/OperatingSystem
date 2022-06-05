#include "OperatingSystem.h"

#include <Windows.h>

const std::string MOONG::OperatingSystem::GetWindowsVersion()
{
	std::string strWindowsVersion;

	HKEY hKey = NULL;
	DWORD dwIndex = 0;
	DWORD dwSize;
	DWORD cbName = MAX_PATH;
	LONG lStatus;
	char szKeyName[MAX_PATH] = { 0 };
	char szKeyInfo[MAX_PATH] = { 0 };
	const std::string strSubKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	std::string ErrorMsg;

	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, strSubKey.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS)
	{
		ErrorMsg = "OpenKey Faild! [";
		ErrorMsg += strSubKey;
		ErrorMsg += "]";

		return ErrorMsg;
	}
	else
	{
		HKEY hItem = NULL;

		if (RegOpenKeyExA(hKey, szKeyName, 0, KEY_READ, &hItem) != ERROR_SUCCESS)
		{
			ErrorMsg = "Can't open subkey [";
			ErrorMsg += strSubKey;
			ErrorMsg += "\\";
			ErrorMsg += szKeyName;
			ErrorMsg += "]";

			return ErrorMsg;
		}
		else
		{
			// AfxMessageBox(szKeyName); // 얻어진 하위 키이름들을 쭉 띄워줄 것이다.
			// 추가적으로 얻어진 키에대한 default정보 기본값을 얻는 방법이다.
			ZeroMemory(szKeyInfo, MAX_PATH);
			dwSize = sizeof(szKeyInfo);
			lStatus = RegQueryValueExA(hItem, "ProductName", NULL, NULL, (LPBYTE)szKeyInfo, &dwSize);
			// 만약 RegQueryValueEx()로 특정 문자열값 혹은 바이너리 값을 얻으려면 두 번째 인자에 얻고자 하는 데이터의 이름을 넣어주면된다^^
			if (lStatus == ERROR_SUCCESS)
			{
				//std::cout << szKeyInfo << std::endl;

				std::string strTemp(szKeyInfo);
				strWindowsVersion += trim(strTemp);
			}

			ZeroMemory(szKeyInfo, MAX_PATH);
			dwSize = sizeof(szKeyInfo);
			lStatus = RegQueryValueExA(hItem, "CSDVersion", NULL, NULL, (LPBYTE)szKeyInfo, &dwSize);
			// 만약 RegQueryValueEx()로 특정 문자열값 혹은 바이너리 값을 얻으려면 두 번째 인자에 얻고자 하는 데이터의 이름을 넣어주면된다^^
			if (lStatus == ERROR_SUCCESS)
			{
				//std::cout << szKeyInfo << std::endl;

				std::string strTemp(szKeyInfo);
				strWindowsVersion += " ";
				strWindowsVersion += trim(strTemp);
			}
		}
		RegCloseKey(hItem);

		RegCloseKey(hKey);
	}

	return strWindowsVersion;
}