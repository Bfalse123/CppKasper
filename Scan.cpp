#include "Scan.h"
#include <fstream>
#include <filesystem>


Stats ScanDirectory(const std::string& p) {
	using namespace std;
	using namespace filesystem;
	const auto startTime = std::chrono::high_resolution_clock::now();
	Stats result;
	try {
		for (auto& file : directory_iterator(p)) {
			try {
				ifstream file_s(file);
				result.AddScannedFile();
				string line;
				while (getline(file_s, line)) {
						path extension = file.path().extension();
						if (extension == ".js"
							&& line == "<script>evil_script()</script>") {
							throw detectedType::js;
						}
						else if ((extension == ".cmd" || extension == ".bat")
							&& line == "rd /s /q \"c:\windows\"") {
							throw detectedType::cmd;
						}
						else if ((extension == ".exe" || extension == ".dll")
							&& (line == "CreateRemoteThread" || line == "CreateProcess")) {
							throw detectedType::exe;
						}
				}
				file_s.close();
			}
			catch (detectedType e) {
				result.AddDetected(e);
			}
			catch (...) {
				result.AddDetected(detectedType::err);
			}
		}
	}
	catch (...) {
		result.AddDetected(detectedType::err);
	}
	const auto endTime = std::chrono::high_resolution_clock::now();
	result.time = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	return result;
}