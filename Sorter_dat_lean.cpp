#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <direct.h>
#include <cstdio>
#include <locale>
#include <codecvt>

namespace fs = std::filesystem;

void copy_delete (std::string& old_path, std::string& new_path){
	//copying
	std::error_code ec;
    fs::copy(fs::u8path(old_path), fs::u8path(new_path), fs::copy_options::overwrite_existing , ec);
    if (ec) {
        std::cerr << "Error: " << ec.message();
		//upit ako datoteka postoji
		if (ec == std::make_error_code(std::errc::file_exists)){
			std::cout <<", " << old_path <<std::endl;
			std::cout <<"Would you like me to overwrite it(y/n)?";
			std::string ans;
			std::cin >> ans;
			if (ans=="Y" || ans=="y"){
				std::cout << "Overwriting "<<old_path <<std::endl;
				fs::copy(fs::u8path(old_path), fs::u8path(new_path), fs::copy_options::overwrite_existing, ec);
                if (ec) {
                    fs::remove(fs::u8path(old_path));
				}
			}
		}
		else std::cout << std::endl;
    } 
	else {
        std::cout << "File copied successfully, deleting: " << old_path << std::endl;
        //deleting old
        fs::remove(fs::u8path(old_path));
	}
}

void handle_file(const fs::directory_entry& entry, const std::string& target_dir) {
    std::string old_path = entry.path().string();
    std::string new_path = target_dir + "\\" + entry.path().filename().string();
    copy_delete(old_path, new_path);
}

int sorting(const std::string& tempp, const fs::path& path) {
    std::cout << "Sorting in path: " << path << std::endl;
    bool sorted = false;

    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry.path())) {
            std::string target_dir;
            auto extension = entry.path().extension().string();

            if (extension == ".txt" || extension == ".docx" || extension == ".pdf" || extension == ".rtf" || extension == ".odt" || extension == ".doc") {
                target_dir = tempp + "\\Dokumenti";
            } else if (extension == ".mp4" || extension == ".avi" || extension == ".mov" || extension == ".wmv") {
                target_dir = tempp + "\\Videi";
            } else if (extension == ".jpg" || extension == ".jpeg" || extension == ".png" || extension == ".gif") {
                target_dir = tempp + "\\Slike";
            } else if (extension == ".zip" || extension == ".rar" || extension == ".7z" || extension == ".tar") {
                target_dir = tempp + "\\Arhivirano";
            } else if (extension == ".pptx" || extension == ".ppt" || extension == ".pptm") {
                target_dir = tempp + "\\Prezentacije";
            } else if (extension == ".stl" || extension == ".gcode" || extension == ".fbx") {
                target_dir = tempp + "\\3D_Modeli";
            } else if (extension == ".cpp" || extension == ".c" || extension == ".h" || extension == ".py" || extension == ".js" || extension == ".css" || extension == ".java" || extension == ".html") {
                target_dir = tempp + "\\Kodovi";
            } else if (extension == ".exe" || extension == ".torrent" || extension == ".msi") {
                target_dir = tempp + "\\Aplikacije i torrenti";
            } else {
                target_dir = tempp + "\\Ostalo";
            }

            if (!target_dir.empty()) {
                if (!fs::exists(target_dir)) {
                    fs::create_directories(target_dir);
                }
                handle_file(entry, target_dir);
                sorted = true;
            }
        }
    }
    return sorted ? 0 : 1;
}

int main()
{
    std::string tempp;
    fs::path path;

    std::cout << "Please enter the path to the folder you want to sort: ";
    std::getline(std::cin, tempp);

    path = fs::u8path(tempp);

    // Check if the provided path exists
    if (fs::exists(path)) {
        std::cout << "The path exists: " << path << std::endl;
        // Sorting
        int noSort = sorting(tempp, path);
        if (noSort == 1) {
            std::cout << "\nNothing is found to sort. Press Enter to continue.";
        } else {
            std::cout << "\nAll done, press Enter to continue.";
        }
    } else {
        std::cout << "Path not found. Please enter a valid path." << std::endl;
    }

    std::cin.ignore(); // Wait for user input before closing
    return 0;
}

