#include <iostream>
#include "Scan.h"

int main(int argc, char* argv[]) {
    //const std::string path = argv[1];
    const std::string path = "I:\\Новая папка (2)";
    auto scanStat = ScanDirectory(path);
    std::cout << scanStat.Output() << std::endl;

    return 0;
}