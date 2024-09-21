#include <iostream>

enum class ErrorCode : int {
    None             = 0,
    FileNotFound     = 1,
    PermissionDenied = 2
};

int main() {
    ErrorCode error = ErrorCode::FileNotFound;
    std::cout << "Error code: " << static_cast<int>(error) << std::endl;
    return 0;
}