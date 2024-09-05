#ifndef DATALOADER_H
#define DATALOADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

/**
 * @brief A struct that represents a single record of weather data for a given day, month, and year.
 *
 * The struct contains fields for the day, month, and year as integers, and the wind speed, temperature, and solar radiation as doubles.
 * using Struct instead of a class because its easier as there is no complecated methods
 */
struct MonthData {
    int m_day; // The day of the record as an integer (1-31)
    int m_month; // The month of the record as an integer (1-12)
    int m_year; // The year of the record as an integer
    double m_windSpeed; // The wind speed of the record in km/h as a double
    double m_temperature; // The temperature of the record in °C as a double
    double m_solarRadiation; // The solar radiation of the record in MJ/m2 as a double

    // getter functions
    double getWindSpeed() const { return m_windSpeed; }
    double getTemperature() const { return m_temperature; }
    double getSolarRadiation() const { return m_solarRadiation; }
};


/**
 * @brief A class that represents a data loader that reads weather data from files and stores them in a map structure.
 *
 * The class contains a protected map field that has keys as years and values as vectors of MonthData objects. It also provides a public method to load data from a file and insert it into the map.
 */
class DataLoader {
protected:
    std::map<int, std::vector<MonthData>> data; // A map that contains weather data for different years

public:
    /**
     * @brief Construct a new DataLoader object with no parameters.
     */
    DataLoader();

    /**
     * @brief Load data from a file and insert it into the map.
     *
     * @param filename The name of the file that contains weather data.
     * @return true If the file is successfully opened and read.
     * @return false If the file cannot be opened or read.
     */
    bool LoadData(const std::string& filename);
};


#endif // DATALOADER_H

