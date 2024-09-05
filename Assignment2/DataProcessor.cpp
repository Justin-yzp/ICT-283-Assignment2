#include "DataProcessor.h"


DataProcessor::DataProcessor() : DataLoader() {}

std::string DataProcessor::GetMonthName(int month) { // Define the function
    switch (month) {
        case 1: return "January";
        case 2: return "February";
        case 3: return "March";
        case 4: return "April";
        case 5: return "May";
        case 6: return "June";
        case 7: return "July";
        case 8: return "August";
        case 9: return "September";
        case 10: return "October";
        case 11: return "November";
        case 12: return "December";
        default: return "";
    }
}
// Search data for a specified month and year
std::vector<MonthData> DataProcessor::Search(int month, int year) const {
    if (data.find(year) != data.end()) {
        std::vector<MonthData> monthDataList;
        for (const auto& dataEntry : data.at(year)) {
            if (dataEntry.m_month == month) {
                monthDataList.push_back(dataEntry);
            }
        }
        return monthDataList;
    }

}

// Calculate average
double DataProcessor::CalculateAverage(const std::vector<double>& values) const {
    double sum = 0.0;
    for (const auto& value : values) {
        sum += value;
    }
    return sum / values.size();
}

// Calculate total
double DataProcessor::CalculateTotal(const std::vector<double>& values) const {
    double sum = 0.0;
    for (const auto& value : values) {
        sum += value;
    }
    return sum;
}

// Calculate sample standard deviation
double DataProcessor::CalculateStandardDeviation(const std::vector<double>& values) const {
    double mean = CalculateAverage(values);
    double variance = 0.0;
    for (const auto& value : values) {
        variance += pow(value - mean, 2);
    }
    variance /= values.size() - 1;
    return sqrt(variance);
}

// Write wind speed, temperature, and solar radiation data to a CSV file
void DataProcessor::WriteDataToFile(int year) {
    std::string filename = "output_" + std::to_string(year) + ".csv";
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "Month,Wind Speed,Temperature,Solar Radiation\n";

    for (int month = 1; month <= 12; month++) {
        std::vector<MonthData> monthDataList = Search(month, year);

        if (!monthDataList.empty()) {
            std::vector<double> windSpeeds;
            std::vector<double> temperatures;
            std::vector<double> solarRadiations;

            for (const auto& monthData : monthDataList) {
                windSpeeds.push_back(monthData.m_windSpeed);
                temperatures.push_back(monthData.m_temperature);
                solarRadiations.push_back(monthData.m_solarRadiation);
            }

            double averageWindSpeed = CalculateAverage(windSpeeds);
            double averageTemperature = CalculateAverage(temperatures);
            double totalSolarRadiation = CalculateTotal(solarRadiations);

            file << GetMonthName(month) << "," << averageWindSpeed << "," << averageTemperature << "," << totalSolarRadiation << "\n";
        }

    }

    file.close();
}
// Print average wind speed and standard deviation for a specified month
void DataProcessor::PrintAverageWindSpeed(int month, int year) {
    std::vector<MonthData> monthDataList = Search(month, year);

    if (!monthDataList.empty()) {
        std::vector<double> windSpeeds;

        for (const auto& monthData : monthDataList) {
            windSpeeds.push_back(monthData.m_windSpeed);
        }

        double averageWindSpeed = CalculateAverage(windSpeeds);
        double standardDeviationWindSpeed = CalculateStandardDeviation(windSpeeds);

        std::cout << "Average wind speed for " << GetMonthName(month) << " " << year << ": " << averageWindSpeed << " m/s\n";
        std::cout << "Standard deviation of wind speed for " << GetMonthName(month) << " " << year << ": " << standardDeviationWindSpeed << " m/s\n";
    } else {
        std::cout << "No data available for " << GetMonthName(month) << " " << year << "\n";
    }
}

// Print average temperature and standard deviation for each month
void DataProcessor::PrintAverageTemperature(int year) {
    for (int month = 1; month <= 12; month++) {
        std::vector<MonthData> monthDataList = Search(month, year);

        if (!monthDataList.empty()) {
            std::vector<double> temperatures;

            for (const auto& monthData : monthDataList) {
                temperatures.push_back(monthData.m_temperature);
            }

            double averageTemperature = CalculateAverage(temperatures);
            double standardDeviationTemperature = CalculateStandardDeviation(temperatures);

            std::cout << "Average temperature for " << GetMonthName(month) << " " << year << ": " << averageTemperature << " °C\n";
            std::cout << "Standard deviation of temperature for " << GetMonthName(month) << " " << year << ": " << standardDeviationTemperature << " °C\n";
        } else {
            std::cout << "No data available for " << GetMonthName(month) << " " << year << "\n";
        }
    }
}

// Print solar radiation for each month
void DataProcessor::PrintSolarRadiation(int year) {
    for (int month = 1; month <= 12; month++) {
        std::vector<MonthData> monthDataList = Search(month, year);

        if (!monthDataList.empty()) {
            std::vector<double> solarRadiations;

            for (const auto& monthData : monthDataList) {
                solarRadiations.push_back(monthData.m_solarRadiation);
            }

            double totalSolarRadiation = CalculateTotal(solarRadiations);

            std::cout << "Total solar radiation for " << GetMonthName(month) << " " << year << ": " << totalSolarRadiation / 1000.0  <<" kWh/m2\n";
        } else {
            std::cout << "No data available for " << GetMonthName(month) << " " << year << "\n";
        }
    }
}

// Display data for a given year
void DataProcessor::DisplayDataForYear(int year) const {
    if (data.find(year) != data.end()) {
        std::cout<<std::setw(10)<<std::left<<"Date"<<std::setw(15)<<std::left<<"Wind Speed"<<std::setw(15)<<std::left<<"Temperature"<<std::setw(15)<<std::left<<"Solar Radiation"<<std::endl;
        for (const auto& dataEntry : data.at(year)) {
            std::cout<<std::setw(10)<<std::left<<dataEntry.m_day<<"/"<<dataEntry.m_month<<"/"<<dataEntry.m_year<<std::setw(15)<<std::left<<dataEntry.m_windSpeed<<std::setw(15)<<std::left<<dataEntry.m_temperature<<std::setw(15)<<std::left<<dataEntry.m_solarRadiation<<std::endl;
        }
    } else {
        std::cout<<"No data available for "<<year<<"\n";
    }
}
std::map<int, std::vector<MonthData>> DataProcessor::GetData() const { // Define the function
    return data; // Return the data member from the DataLoader class
}
