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
			// AfxMessageBox(szKeyName); // ����� ���� Ű�̸����� �� ����� ���̴�.
			// �߰������� ����� Ű������ default���� �⺻���� ��� ����̴�.
			ZeroMemory(szKeyInfo, MAX_PATH);
			dwSize = sizeof(szKeyInfo);
			lStatus = RegQueryValueExA(hItem, "ProductName", NULL, NULL, (LPBYTE)szKeyInfo, &dwSize);
			// ���� RegQueryValueEx()�� Ư�� ���ڿ��� Ȥ�� ���̳ʸ� ���� �������� �� ��° ���ڿ� ����� �ϴ� �������� �̸��� �־��ָ�ȴ�^^
			if (lStatus == ERROR_SUCCESS)
			{
				//std::cout << szKeyInfo << std::endl;

				std::string strTemp(szKeyInfo);
				strWindowsVersion += trim(strTemp);
			}

			ZeroMemory(szKeyInfo, MAX_PATH);
			dwSize = sizeof(szKeyInfo);
			lStatus = RegQueryValueExA(hItem, "CSDVersion", NULL, NULL, (LPBYTE)szKeyInfo, &dwSize);
			// ���� RegQueryValueEx()�� Ư�� ���ڿ��� Ȥ�� ���̳ʸ� ���� �������� �� ��° ���ڿ� ����� �ϴ� �������� �̸��� �־��ָ�ȴ�^^
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