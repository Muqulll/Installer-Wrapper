#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

// ANSI Color Macros
namespace Color {
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string CYAN = "\033[36m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
} // namespace Color

void print_header() {
  std::cout << Color::CYAN << Color::BOLD
            << "====================================\n"
            << "   Arch Package Manager Wrapper     \n"
            << "====================================\n"
            << Color::RESET;
}

int select_backend() {
  int choice = 0;
  while (true) {
    std::cout << "\n"
              << Color::YELLOW
              << "Select Package Manager Backend:" << Color::RESET << "\n";
    std::cout << "  " << Color::CYAN << "1)" << Color::RESET
              << " pacman (Official Repositories)\n";
    std::cout << "  " << Color::CYAN << "2)" << Color::RESET
              << " paru    (AUR + Official Repositories)\n";
    std::cout << "  " << Color::CYAN << "3)" << Color::RESET << " Exit\n";
    std::cout << Color::BOLD << "Choice [1-3]: " << Color::RESET;

    if (std::cin >> choice && choice >= 1 && choice <= 3) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return choice;
    }

    std::cout << Color::RED << "Invalid selection. Please enter 1, 2, or 3."
              << Color::RESET << "\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int main() {
  print_header();
  int backend_choice = select_backend();

  if (backend_choice == 3) {
    std::cout << Color::YELLOW << "Exiting...\n" << Color::RESET;
    return 0;
  }

  std::string manager = (backend_choice == 1) ? "sudo pacman -S" : "paru -S";
  std::string package_name;

  std::cout << "\n"
            << Color::GREEN
            << "[Active Backend: " << (backend_choice == 1 ? "pacman" : "paru")
            << "]" << Color::RESET << "\n";
  std::cout << "Type package names to install, or " << Color::YELLOW << "'q'"
            << Color::RESET << " to quit.\n";

  while (true) {
    std::cout << "\n"
              << Color::BOLD << Color::CYAN << "package > " << Color::RESET;
    std::getline(std::cin, package_name);

    if (package_name.empty())
      continue;
    if (package_name == "q" || package_name == "exit") {
      std::cout << Color::YELLOW << "Session ended.\n" << Color::RESET;
      break;
    }

    std::string command = manager + " " + package_name;
    std::cout << Color::YELLOW << "Running: " << command << Color::RESET
              << "\n\n";

    int result = std::system(command.c_str());

    if (result != 0) {
      std::cout << "\n"
                << Color::RED
                << "[!] Process exited with status code: " << result
                << Color::RESET << "\n";
    } else {
      std::cout << "\n"
                << Color::GREEN << "[✓] Installation completed successfully."
                << Color::RESET << "\n";
    }
  }

  return 0;
}