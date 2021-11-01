#include "Stats.h"

std::string Stats::Output() {
    std::ostringstream result;
    auto ms = time;
    auto h = std::chrono::duration_cast<std::chrono::hours>(ms);
    ms -= h;
    auto m = std::chrono::duration_cast<std::chrono::minutes>(ms);
    ms -= m;
    auto s = std::chrono::duration_cast<std::chrono::seconds>(ms);
    ms -= s;
    result << "====== Scan result ======\n"
        << "Processed files: " << scannedFiles << "\n"
        << "JS: " << js << "\n"
        << "CMD: " << cmd << "\n"
        << "EXE: " << exe << "\n"
        << "Errors: " << errors << "\n"
        << "Exection time: " << std::setw(2) << std::setfill('0') << h.count() << ":" <<
        std::setw(2) << std::setfill('0') << m.count() << ":" <<
        std::setw(2) << std::setfill('0') << s.count() << "\n"
        << "=========================\n";
    return result.str();
}
void Stats::AddScannedFile() {
    scannedFiles++;
}
void Stats::AddDetected(const detectedType& detected) {
    switch (detected) {
    case detectedType::js:
        js++;
        break;
    case detectedType::cmd:
        cmd++;
        break;
    case detectedType::exe:
        exe++;
        break;
    case detectedType::err:
        errors++;
        break;
    }
}
