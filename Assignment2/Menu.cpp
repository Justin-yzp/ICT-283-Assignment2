#include "Menu.h"


Menu::Menu(WeatherData& wdInput) : wd(wdInput), year(0), running(true) {}
void Menu::DisplayMenu() {
    std::cout << "\nMenu options:\n";
    std::cout << "1. Average wind speed and standard deviation for a specified month and year\n";
    std::cout << "2. Average ambient air temperature and standard deviation for each month of a specified year\n";
    std::cout << "3. Sample Pearson Correlation Coefficient (sPCC) for specified month\n";
    std::cout << "4. Average wind speed, average ambient air temperature, and total solar radiation for each month of a specified year (write to file)\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}
const int MIN_MONTH = 1;
const int MAX_MONTH = 12;
const int MIN_YEAR = 0;

bool Menu::IsValidMonth(int month) {
    return month >= MIN_MONTH && month <= MAX_MONTH;
}
bool Menu::IsValidYear(int selectedYear, int currentYear) {
    return selectedYear >= MIN_YEAR && selectedYear <= currentYear;
}
void Menu::ExecuteChoice(int choice) {
    bool validInput;
    switch (choice) {
        case 1: {
            int month, yearInput;
            do {
                validInput = true; // Assume the input is valid until proven otherwise
                std::cout << "Enter the month (" << MIN_MONTH << "-" << MAX_MONTH << "): ";
                std::cin >> month;
                if (!IsValidMonth(month)) { // Use the isValidMonth function
                    std::cout << "Invalid month. Please enter a number between " << MIN_MONTH << " and " << MAX_MONTH << "." << std::endl;
                    validInput = false; // Set the input validity to false
                }
                std::cout << "Enter the year: ";
                std::cin >> yearInput;
                if (!IsValidYear(yearInput, wd.GetCurrentYear())) {
                    std::cout << "Invalid year. Please enter a positive number up to " << wd.GetCurrentYear() << "." << std::endl;
                    validInput = false;
                }
            } while (!validInput);
            wd.PrintAverageWindSpeed(month, yearInput);
            break;
        }
        case 2:
            int yearInput;
            do {
                validInput = true;
                std::cout << "Enter the year: ";
                std::cin >> yearInput;
                if (!IsValidYear(yearInput, wd.GetCurrentYear())) {
                    std::cout << "Invalid year. Please enter a positive number up to " << wd.GetCurrentYear() << "." << std::endl;
                    validInput = false;
                }
            } while (!validInput);
            wd.PrintAverageTemperature(yearInput);
            break;
        case 3:
            int month;
            do {
                validInput = true;
                std::cout << "Enter the month (" << MIN_MONTH << "-" << MAX_MONTH << "): ";
                std::cin >> month;
                if (!IsValidMonth(month)) {
                    std::cout << "Invalid month. Please enter a number between " << MIN_MONTH << " and " << MAX_MONTH << "." << std::endl;
                    validInput = false;
                }
            } while (!validInput);
            wd.CalculateSPCC(month);
            break;
        case 4:
            do {
                validInput = true;
                std::cout << "Enter the year: ";
                std::cin >> yearInput;
                if (!IsValidYear(yearInput, wd.GetCurrentYear())) { // Use the isValidYear function
                    std::cout << "Invalid year. Please enter a positive number up to " << wd.GetCurrentYear() << "." << std::endl;
                    validInput = false;
                }
            } while (!validInput);
            wd.WriteDataToFile(yearInput);
            break;
        case 5:
            // Write code for bonus feature here
            break;
        case 6:
            running = false;
            std::cout << "Thank You. Goodbye! ";
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

void Menu::Run() {
    int choice;

    while (running) {
        DisplayMenu();
        std::cin >> choice;
        ExecuteChoice(choice);
    }
}
