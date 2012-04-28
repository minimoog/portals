#include "procutil.h"
#include <sstream>

std::wstring ProcUtil::ProcGetNextValue(std::wifstream& file)
{
    std::wstring s;

    while (file >> s) {
        if (s == L"/*") {				//skip comments
            while (s != L"*/") {
                file >> s;
            }
        } else if (s == L"{" || s == L"}") {
        } else if (s == L"(" || s == L")") {
        } else {
            return s;
        }
    }
    return s;
}

std::wstring ProcUtil::ProcGetNextString(std::wifstream& file)
{
    std::wstring s = ProcGetNextValue(file);

    return s.substr(1, s.size() - 2);
}

float ProcUtil::ProcGetNextFloat(std::wifstream& file)
{
    float result;
    std::wstringstream(ProcGetNextValue(file)) >> result;

    return result;
}

int ProcUtil::ProcGetNextInt(std::wifstream& file)
{
    int result;

    std::wstringstream(ProcGetNextValue(file)) >> result;

    return result;
}

