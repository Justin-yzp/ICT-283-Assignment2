#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Test.h"
#include "WeatherData.h" // Include the header file for WeatherData class
#include "Menu.h" // Include the header file for Menu class

int main() {

    // Create a WeatherData object for handling data and BST
    WeatherData weatherData;

    // Read the CSV data file names from data_source.txt
    std::ifstream dataFile("data/data_source.txt");
    if (!dataFile.is_open()) {
        std::cout << "Error opening data_source.txt\n";
        return 1;
    }

    std::string dataFilename;
    while (getline(dataFile, dataFilename)) {
        std::cout << "Load file: " << dataFilename << "\n";
        if (!weatherData.LoadData("data/" + dataFilename)) {
            std::cout << "Error loading file: " << dataFilename << "\n";
            return 1;
        }
    }

    dataFile.close();


    // Create a Menu object for handling user input and menu options
    Menu menu(weatherData);

    // Run the menu loop
    menu.Run();

    return 0;
}
