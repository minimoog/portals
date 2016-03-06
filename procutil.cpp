/*
* Copyright (c) 2008 Antonie Jovanoski <minimoog77_at_gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

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

