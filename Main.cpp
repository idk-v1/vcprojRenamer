#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main()
{
	std::string newName, oldPath, oldName;


	std::getline(std::cin, oldPath);
	std::getline(std::cin, newName);

	oldName = fs::path(oldPath).filename().string();

	std::ifstream sln(oldPath + '/' + oldName + ".sln");
	std::ofstream slnOut(oldPath + '/' + newName + ".sln");
	if (sln.is_open())
	{
		std::string data;
		size_t pos;
		while (std::getline(sln, data))
		{
			while (data.find(oldName) != std::string::npos)
			{
				pos = data.find(oldName);
				data = data.replace(pos, oldName.size(), newName);
			}
			slnOut.write((data + '\n').data(), data.size() + 1);
		}
		sln.close();
		slnOut.close();
	}
	std::ifstream vcxproj(oldPath + '/' + oldName + ".vcxproj");
	std::ofstream vcxprojOut(oldPath + '/' + newName + ".vcxproj");
	if (vcxproj.is_open())
	{
		std::string data;
		size_t pos;
		while (std::getline(vcxproj, data))
		{
			while (data.find(oldName) != std::string::npos)
			{
				pos = data.find(oldName);
				data = data.replace(pos, oldName.size(), newName);
			}
			vcxprojOut.write((data + '\n').data(), data.size() + 1);
		}
		vcxproj.close();
		vcxprojOut.close();
	}


	fs::remove(oldPath + '/' + oldName + ".sln");
	fs::remove(oldPath + '/' + oldName + ".vcxproj");
	fs::rename(oldPath + '/' + oldName + ".vcxproj.filters", oldPath + '/' + newName + ".vcxproj.filters");
	fs::rename(oldPath + '/' + oldName + ".vcxproj.user", oldPath + '/' + newName + ".vcxproj.user");
	fs::rename(oldPath, fs::path(oldPath).parent_path().string() + '/' + newName);

	return 0;
}