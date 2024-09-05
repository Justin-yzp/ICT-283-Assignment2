#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include "DataProcessor.h"


/**
 * @brief A class that represents weather data for a given year.
 *
 * The class stores weather data such as wind speed, temperature, and solar radiation
 * in a binary search tree (BST) structure. It also provides methods to load data from files,
 * calculate various statistics, and write data to a CSV file.
 */
class WeatherData {
private:
    int year; // The year of the weather data
    DataProcessor dataTree; // The BST instance to store weather data
    std::vector<std::string> dataFiles; // The names of the files that contain weather data

public:
    /**
     * @brief Construct a new WeatherData object with a specified year.
     *
     * @param selectedYear The year of the weather data. If not specified, it defaults to 0.
     */
    WeatherData(int selectedYear = 0);

    /**
     * @brief Load data from the specified file and insert it into the BST.
     *
     * @param filename The name of the file that contains weather data.
     * @return true If the file is successfully opened and read.
     * @return false If the file cannot be opened or read.
     */
    bool LoadData(const std::string& filename);

    /**
     * @brief Calculate the average of a vector of values.
     *
     * @param values A vector of double values.
     * @return double The average of the values.
     */
    double CalculateAverage(const std::vector<double>& data);

    /**
     * @brief Calculate the average of a vector of double objects based on a specific member function.
     *
     * @param values A vector of MonthData objects.
     * @param data Pointer to a member function of MonthData to access the desired data (e.g. &MonthData::m_windSpeed).
     * @return double The average of the data specified by the member function.
     */
    double CalculateAverage(const std::vector<MonthData>& values, double (MonthData::*data)() const);

    /**
     * @brief Calculate the total of a vector of MonthData objects based on a specific member function.
     *
     * @param values A vector of MonthData objects.
     * @param data Pointer to a member function of MonthData to access the desired data (e.g. &MonthData::m_windSpeed).
     * @return double The total of the data specified by the member function.
     */
    double CalculateTotal(const std::vector<MonthData>& values, double (MonthData::*data)() const);

    /**
     * @brief Calculate the sample standard deviation of a vector of MonthData objects based on a specific member function.
     *
     * @param values A vector of MonthData objects.
     * @param data Pointer to a member function of MonthData to access the desired data (e.g. &MonthData::m_windSpeed).
     * @return double The sample standard deviation of the data specified by the member function.
     */
    double CalculateStandardDeviation(const std::vector<MonthData>& values, double (MonthData::*data)() const);

    /**
     * @brief Get the month name based on its index (1-12).
     *
     * @param month The index of the month (1-12).
     * @return std::string The name of the month (e.g. January, February, etc.).
     */
    std::string GetMonthName(int month);

    /**
     * @brief Calculate and print the Sample Pearson Correlation Coefficient (sPCC)
     * between wind speed and solar radiation for a specified month.
     *
     * @param month The index of the month (1-12).
     */
    void CalculateSPCC(int month);

    /**
     * @brief Print the average wind speed and standard deviation for a specified month
     * for a given year.
     *
     * @param month The index of the month (1-12).
     * @param selectedYear The year of the weather data.
     */
    void PrintAverageWindSpeed(int month, int selectedYear);

    /**
     * @brief Print the average temperature and standard deviation for each month
     * for a given year.
     *
     * @param selectedYear The year of the weather data.
     */
    void PrintAverageTemperature(int selectedYear);

    /**
     * @brief Print the total solar radiation for each month
     * for a given year.
     *
      *@param selectedYear The year of the weather data.
      */
    void PrintSolarRadiation(int selectedYear);

    /**
      *@brief Write wind speed, temperature, and solar radiation data to a CSV file
      *@param selectedYear The year of the weather data.
      */
    void WriteDataToFile(int selectedYear);

    /**
      *@brief Display all weather data for a given year in a table format.
      *@param selectedYear The year of the weather data.
      */
    void DisplayDataForYear(int selectedYear) const;

    /**
      *@brief Check if a given year is valid (i.e. within the range of available data).
      *@param selectedYear The year to be checked.
      *@return true If the year is valid.
      *@return false If the year is invalid.
      */
    bool IsYearValid(int selectedYear) const;

    /**
      *@brief Get the current year from the system time.
      *@return int The current year.
      */
    static int GetCurrentYear();

};

#endif // WEATHERDATA_H
