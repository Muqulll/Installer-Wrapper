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

int show_menu() {
  int choice = 0;
  while (true) {
    std::cout << "\n"
              << Color::YELLOW << "Select Action / Backend:" << Color::RESET << "\n";
    std::cout << "  " << Color::CYAN << "1)" << Color::RESET << " pacman Install\n";
    std::cout << "  " << Color::CYAN << "2)" << Color::RESET << " paru Install\n";
    std::cout << "  " << Color::CYAN << "3)" << Color::RESET << " paru Search : D\n";
    std::cout << "  " << Color::CYAN << "4)" << Color::RESET << " Exit\n";
    std::cout << Color::BOLD << "Choice [1-4]: " << Color::RESET;

    if (std::cin >> choice && choice >= 1 && choice <= 4) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return choice;
    }

    std::cout << Color::RED << "Invalid selection. Please enter 1, 2, 3, or 4."
              << Color::RESET << "\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int main() {
  print_header();

  while (true) {
    int choice = show_menu();

    // Choice 4: Exit program
    if (choice == 4) {
      std::cout << Color::YELLOW << "Exiting...\n" << Color::RESET;
      break;
    }

    // Choice 3: Search mode (press 'q' to return to menu)
    if (choice == 3) {
      std::cout << "\n"
                << Color::GREEN << "[Active Mode: paru Search]" << Color::RESET << "\n";
      std::cout << "Type search terms, or " << Color::YELLOW << "'q'"
                << Color::RESET << " to return to the menu.\n";

      while (true) {
        std::cout << "\n"
                  << Color::BOLD << Color::CYAN << "search > " << Color::RESET;
        std::string query;
        std::getline(std::cin, query);

        if (query.empty())
          continue;
        if (query == "q" || query == "exit") {
          std::cout << Color::YELLOW << "Returning to menu...\n" << Color::RESET;
          break; // Breaks out of search loop and loops back to main menu
        }

        std::string command = "paru -Ss " + query;
        std::cout << Color::YELLOW << "Running: " << command << Color::RESET
                  << "\n\n";

        std::system(command.c_str());
      }
      continue; // Jump back to the top of the menu loop
    }

    // Choice 1 or 2: Install mode
    std::string manager = (choice == 1) ? "sudo pacman -S" : "paru -S";
    std::string mode_label = (choice == 1) ? "pacman" : "paru";

    std::cout << "\n"
              << Color::GREEN
              << "[Active Backend: " << mode_label
              << "]" << Color::RESET << "\n";
    std::cout << "Type package names to install, or " << Color::YELLOW << "'q'"
              << Color::RESET << " to return to the menu.\n";

    while (true) {
      std::cout << "\n"
                << Color::BOLD << Color::CYAN << "package > " << Color::RESET;
      std::string package_name;
      std::getline(std::cin, package_name);

      if (package_name.empty())
        continue;
      if (package_name == "q" || package_name == "exit") {
        std::cout << Color::YELLOW << "Returning to menu...\n" << Color::RESET;
        break; // Breaks out of install loop and returns to main menu
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
  }

  return 0;
}