#ifndef PROCUTIL_H
#define PROCUTIL_H

#include <fstream>
#include <string>

class ProcUtil
{
public:

    static std::wstring ProcGetNextValue(std::wifstream& file);
    static std::wstring ProcGetNextString(std::wifstream& file);
    static float ProcGetNextFloat(std::wifstream& file);
    static int ProcGetNextInt(std::wifstream& file);
};

#endif // PROCUTIL_H
