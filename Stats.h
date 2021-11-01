#pragma once
#include <ctime>
#include <sstream>
#include <chrono>

enum detectedType {
    js,
    cmd,
    exe,
    err
};

class Stats {
public:
    std::chrono::duration<int64_t, std::ratio<1, 1000>> time;
    std::string Output();
    void AddScannedFile();
    void AddDetected(const detectedType&);
private:
    size_t scannedFiles = 0;
    size_t js = 0;
    size_t cmd = 0;
    size_t exe = 0;
    size_t errors = 0;
};
