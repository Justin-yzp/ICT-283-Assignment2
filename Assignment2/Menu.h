// Menu.h
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "WeatherData.h"

/**
 * @brief A class that represents the user interface of the program.
 *
 * The class displays a menu of options to the user and allows them to interact with
 * a WeatherData object that contains weather data for a given year.
 */
class Menu {
private:
    WeatherData& wd; // A reference to a WeatherData object
    int year; // A variable to store the user's input year
public:
    bool running; // A boolean variable that controls the loop condition
    /**
     * @brief Construct a new Menu object with a reference to a WeatherData object.
     *
     * @param wd A reference to a WeatherData object that contains weather data.
     */
    Menu(WeatherData& wd);

    /**
     * @brief Display the menu options to the user and ask for their choice.
     *
     * The menu options are:
     * 1. Average wind speed and standard deviation for a specified month and year
     * 2. Average ambient air temperature and standard deviation for each month of a specified year
     * 3. Sample Pearson Correlation Coefficient (sPCC) for specified month
     * 4. Average wind speed, average ambient air temperature, and total solar radiation for each month of a specified year (write to file)
     * 6. Exit program
     */
    void DisplayMenu();


    /**
     * @brief Execute the user's choice and call the corresponding method from the WeatherData object.
     *
     * @param choice The user's choice as an integer (1-7).
     */
    void ExecuteChoice(int choice);

    /**
     * @brief Run the main loop of the program, asking for the year and the menu choice until the user exits.
     */
    void Run();

    /**
     * @brief Check if a given month is valid (i.e. within the range of 1-12).
     *
     * @param month The month to be checked as an integer.
     * @return true If the month is valid.
     * @return false If the month is invalid.
     */
    bool IsValidMonth(int month);

    /**
     * @brief Check if a given year is valid (i.e. within the range of available data and not in the future).
     *
     * @param year The year to be checked as an integer.
     * @param currentYear The current year as an integer.
     * @return true If the year is valid.
     * @return false If the year is invalid.
     */
    bool IsValidYear(int year, int currentYear);

};


#endif
