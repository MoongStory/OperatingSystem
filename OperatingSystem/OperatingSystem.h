#pragma once
// https://github.com/MoongStory/OperatingSystem

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _OPERATINGSYSTEM_H_
#define _OPERATINGSYSTEM_H_

#include <iostream>
#include <functional>

namespace MOONG
{
	class OperatingSystem
	{
	public:
	protected:
	private:

	public:
		static const std::string GetWindowsVersion();
	protected:
	private:
		//�տ� �ִ� ���� ���� ����
		static inline std::string& ltrim(std::string& s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
		}

		//�ڿ� �ִ� ���� ���� ����
		static inline std::string& rtrim(std::string& s) {
			s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
		}

		//���� ���� ���� ���� ����
		static inline std::string& trim(std::string& s) {
			return ltrim(rtrim(s));
		}
	};
}
#endif	// _OPERATINGSYSTEM_H_