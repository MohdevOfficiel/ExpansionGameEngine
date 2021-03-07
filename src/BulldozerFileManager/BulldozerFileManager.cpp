#include "pch.h"
#include "framework.h"
#include "BulldozerFileManager.h"

#ifdef _WIN32

void dispErrorMessageBox(LPCWSTR Message) {
	MessageBox(nullptr, Message, TEXT("ERROR !!!"), MB_ICONERROR | MB_OK);
	std::wcerr << "ERROR: " << Message << std::endl;
}

#else

void dispErrorMessageBox(std::wstring Message) {
	std::wcerr << Message << std::endl;
}

#endif //_WIN32

std::string getFileData(std::string filePath) {
	std::ifstream file;
	file.open(filePath);

	if (!file) {
		dispErrorMessageBox(TEXT("File cannot be opened. \"\" will be returned."));
		return "";
	}

	std::string temp;

	std::string fileData = "";

	while (!file.eof()) {
		std::getline(file, temp);
		fileData.append(temp + "\n");
	}

	file.close();
	return fileData;
}

std::string getFileExtension(std::string fileName) {
	std::string extension;

	size_t nSize = fileName.size() - 1;

	for (int i = nSize; i > 0; i--) {
		if (fileName[i] != '.') {
			extension.push_back(fileName[i]);
		}
		else {
			break;
		}
	}

	std::cout << extension << std::endl;

	return extension;
}

std::vector<char> GetFileBinData(std::string filePath) {
	std::ifstream file;
	file.open(filePath, std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::wstring file(filePath.begin(), filePath.end());
		dispErrorMessageBox(std::wstring(L"Failed to open file " + file).c_str());
		return {};
	}

	size_t fSize = file.tellg();
	file.seekg(0);
	std::vector<char> data(fSize);
	file.read(data.data(), fSize);

	return data;
}