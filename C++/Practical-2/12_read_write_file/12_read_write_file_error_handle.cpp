#include <iostream>

/******************************1************************* */
if (outFile.fail()) {
    outFile.close();
    // 进一步的错误处理...
}
/******************************2************************* */

if (outFile.fail()) { throw std::runtime_error("Failed to write to file."); }
/*******************************3************************ */

bool writeFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename);
    if (outFile.fail()) { return false; }
    outFile << content;
    if (outFile.fail()) {
        outFile.close();
        return false;
    }
    outFile.close();
    return true;
}

/*****************************4************************** */

enum class FileError { None, OpenFailed, WriteFailed, CloseFailed };

FileError writeFile(const std::string &filename, const std::string &content) {
    std::ofstream outFile(filename);
    if (outFile.fail()) { return FileError::OpenFailed; }
    outFile << content;
    if (outFile.fail()) {
        outFile.close();
        return FileError::WriteFailed;
    }
    if (!outFile.close()) { return FileError::CloseFailed; }
    return FileError::None;
}

/*****************************5************************** */

if (outFile.fail()) {
    logError("File writing failed.");
    // 进一步的错误处理...
}