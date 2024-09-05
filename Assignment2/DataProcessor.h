#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H
#include "DataLoader.h"

#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>

/**
 * @brief A class that extends the DataLoader functionality to process and analyze weather data.
 *
 * The DataProcessor class inherits from the DataLoader class and provides additional methods to process, analyze, and display weather data.
 * It stores weather data in a map structure, where each year is associated with a vector of MonthData objects.
 * The class enables searching for data by month and year efficiently using the map structure.
 * DataProcessor offers various statistical calculations, such as calculating average, total, and sample standard deviation of wind speed, temperature, and solar radiation.
 * It can write selected weather data to a CSV file and display weather data for a given year in a table format.
 * The DataProcessor class acts as a powerful tool for working with weather data, providing essential analysis and visualization capabilities.
 *
 * @note The class also includes function pointers for CalculateAverage, CalculateTotal, and CalculateStandardDeviation,
 *       allowing the user to choose different statistical functions at runtime.
 */

class DataProcessor : public DataLoader {
public:
    /**
     * @brief Construct a new DataProcessor object with no parameters.
     */
    DataProcessor();

    /**
     * @brief Search for data by month and year.
     *
     * @param month The month to be searched as an integer (1-12).
     * @param year The year to be searched as an integer.
     * @return std::vector<MonthData> A vector of MonthData objects that match the month and year criteria.
     */
    std::vector<MonthData> Search(int month, int year) const;

    /**
     * @brief Calculate the average of a vector of values.
     *
     * @param values A vector of double values.
     * @return double The average of the values.
     */
    double CalculateAverage(const std::vector<double>& values) const;

    /**
     * @brief Calculate the total of a vector of values.
     *
     * @param values A vector of double values.
     * @return double The total of the values.
     */
    double CalculateTotal(const std::vector<double>& values) const;

    /**
     * @brief Calculate the sample standard deviation of a vector of values.
     *
     * @param values A vector of double values.
     * @return double The sample standard deviation of the values.
     */
    double CalculateStandardDeviation(const std::vector<double>& values) const;

    /**
     * @brief Print the average wind speed and standard deviation for a specified month and year to the console.
     *
     * @param month The month to be printed as an integer (1-12).
     * @param year The year to be printed as an integer.
     */
    void PrintAverageWindSpeed(int month, int year);

    /**
     * @brief Print the average temperature and standard deviation for each month of a specified year to the console.
     *
     * @param year The year to be printed as an integer.
     */
    void PrintAverageTemperature(int year);

    /**
     * @brief Print the total solar radiation for each month of a specified year to the console.
     *
     * @param year The year to be printed as an integer.
     */
    void PrintSolarRadiation(int year);

    /**
     * @brief Write wind speed, temperature, and solar radiation data for each month of a specified year to a CSV file.
     * @param year The year to be written as an integer.
     */
    void WriteDataToFile(int year);

    /**
     * @brief Display all weather data for a given year in a table format.
     * @param year The year to be displayed as an integer.
     */
    void DisplayDataForYear(int year) const;

    /**
     * @brief Get the month name based on its index (1-12).
     * @param month The index of the month (1-12).
     * @return std::string The name of the month (e.g., January, February, etc.).
     */
    std::string GetMonthName(int month);

    /**
     * @brief Get the map that contains all weather data.
     * @return std::map<int, std::vector<MonthData>> The map that has keys as years and values as vectors of MonthData objects.
     */
    std::map<int, std::vector<MonthData>> GetData() const;
};

#endif // DATA_PROCESSOR_H
