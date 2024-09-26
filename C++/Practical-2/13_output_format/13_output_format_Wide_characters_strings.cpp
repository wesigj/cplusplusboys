#include <iostream>
#include <string>

int main() {
    wchar_t      wideChar = L'A';
    std::wstring wstr     = L"Wide String";

    std::wcout << "Wide character: " << wideChar << std::endl;
    std::wcout << "Wide string: " << wstr << std::endl;

    return 0;
}