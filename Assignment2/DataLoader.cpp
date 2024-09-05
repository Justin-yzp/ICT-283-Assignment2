#include "DataLoader.h"


DataLoader::DataLoader() : data() {}

// Load data from the specified file
// In the DataLoader.cpp file
bool DataLoader::LoadData(const std::string& filename) {
    //std::cout << "Loading data from file: " << filename << std::endl;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line);

    std::cout << "The header line is: " << line << std::endl;

    std::istringstream headerStream(line);
    std::string columnName;
    std::vector<std::string> columnNames;
    while (std::getline(headerStream, columnName, ',')) {
        columnNames.push_back(columnName);
    }

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string dataValue; // Rename the local variable
        int index = 0;
        MonthData monthData;

        while (std::getline(iss, dataValue, ',')) {
            if (index >= columnNames.size()) {
                break;
            }


            if (columnNames[index] == "WAST") {
                std::istringstream dateIss(dataValue);
                std::string day, month, year;
                std::getline(dateIss, day, '/');
                std::getline(dateIss, month, '/');
                std::getline(dateIss, year, ' ');

                try {
                    monthData.m_day = std::stoi(day);
                    monthData.m_month = std::stoi(month);
                    monthData.m_year = std::stoi(year);
                } catch (const std::invalid_argument&) {
                    monthData.m_day = 0;
                    monthData.m_month = 0;
                    monthData.m_year = 0;
                }
            } else if (columnNames[index] == "S") {
                try {
                    if (!dataValue.empty()) {
                        monthData.m_windSpeed = std::stod(dataValue);
                    } else {
                        monthData.m_windSpeed = 0.0;
                    }
                } catch (const std::invalid_argument&) {
                    monthData.m_windSpeed = 0.0;
                }
            } else if (columnNames[index] == "T") {
                try {
                    if (!dataValue.empty()) {
                        monthData.m_temperature = std::stod(dataValue);
                    } else {
                        monthData.m_temperature = 0.0;
                    }
                } catch (const std::invalid_argument&) {
                    monthData.m_temperature = 0.0;
                }
            } else if (columnNames[index] == "SR") {
                try {
                    if (!dataValue.empty()) {
                        monthData.m_solarRadiation = std::stod(dataValue);
                    } else {
                        monthData.m_solarRadiation = 0.0;
                    }
                } catch (const std::invalid_argument&) {
                    monthData.m_solarRadiation = 0.0;
                }
            }

            index++;
        }
        if (index >= columnNames.size() && monthData.m_year != 0 && monthData.m_month != 0) {
            int year = monthData.m_year;
            this->data[year].push_back(monthData);

        }
    }

    file.close();
    return true;
}

