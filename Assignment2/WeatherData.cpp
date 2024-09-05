#include "WeatherData.h"


WeatherData::WeatherData(int selectedYear) : year(selectedYear), dataTree(), dataFiles() {}

bool WeatherData::LoadData(const std::string& filename) {
    return dataTree.LoadData(filename);
}

// modify the CalculateAverage method to take a pointer to a member function of MonthData
double WeatherData::CalculateAverage(const std::vector<MonthData>& values, double (MonthData::*data)() const) {
    double sum = 0.0;
    for (const MonthData& value : values) {
        sum += (value.*data)(); // call the member function through the pointer
    }
    return sum / values.size();
}

double WeatherData::CalculateAverage(const std::vector<double>& data) {
    double sum = 0.0;
    int count = 0;

    for (const double& value : data) {
        sum += value;
        count++;
    }

    if (count > 0) {
        return sum / count;
    }
    else {
        return 0.0;
    }
}

// modify the CalculateTotal method to take a pointer to a member function of MonthData
double WeatherData::CalculateTotal(const std::vector<MonthData>& values, double (MonthData::*data)() const) {
    double sum = 0.0;
    for (const MonthData& value : values) {
        sum += (value.*data)(); // call the member function through the pointer
    }
    return sum;
}

// modify the CalculateStandardDeviation method to take a pointer to a member function of MonthData
double WeatherData::CalculateStandardDeviation(const std::vector<MonthData>& values, double (MonthData::*data)() const) {
    double mean = CalculateAverage(values, data);
    double variance = 0.0;
    for (const MonthData& value : values) {
        variance += pow((value.*data)() - mean, 2); // call the member function through the pointer
    }
    variance /= values.size();
    return sqrt(variance);
}

std::string WeatherData::GetMonthName(int month) {
    static const std::string monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return monthNames[month - 1];
}
void WeatherData::PrintAverageWindSpeed(int month, int selectedYear) {
    std::vector<MonthData> monthDataList = dataTree.Search(month, selectedYear);
    // pass the pointer to the getWindSpeed member function of MonthData
    double average = CalculateAverage(monthDataList, &MonthData::getWindSpeed);
    double stdev = CalculateStandardDeviation(monthDataList, &MonthData::getWindSpeed);


    if (monthDataList.empty()) {
        std::cout << GetMonthName(month) << " " << selectedYear << ": No Data" << std::endl;
    } else {
        std::cout << GetMonthName(month) << " " << selectedYear << ":" << std::endl;
        std::cout << "Average speed: " << std::fixed << std::setprecision(1) << average << " km/h" << std::endl;
        std::cout << "Sample stdev: " << std::fixed << std::setprecision(1) << stdev << std::endl;
    }
}



void WeatherData::PrintAverageTemperature(int selectedYear) {
    for (int month = 1; month <= 12; ++month) {
        std::vector<MonthData> monthDataList = dataTree.Search(month, selectedYear);
        // pass the pointer to the temperature member function of MonthData
        double average = CalculateAverage(monthDataList, &MonthData::getTemperature);
        double stdev = CalculateStandardDeviation(monthDataList, &MonthData::getTemperature);

        if (monthDataList.empty()) {
            std::cout << GetMonthName(month) << " " << selectedYear << ": No Data" << std::endl;
        } else {
            std::cout << GetMonthName(month) << " " << selectedYear << ": average: " << std::fixed << std::setprecision(1)
                      << average << " degrees C, stdev: " << std::fixed << std::setprecision(1) << stdev << std::endl;
        }
    }
}


void WeatherData::PrintSolarRadiation(int selectedYear) {
    for (int month = 1; month <= 12; ++month) {
        std::vector<MonthData> monthDataList = dataTree.Search(month, selectedYear);
        // pass the pointer to the solarRadiation member function of MonthData
        double total = CalculateTotal(monthDataList, &MonthData::getSolarRadiation);

        if (monthDataList.empty()) {
            std::cout << GetMonthName(month) << " " << selectedYear << ": No Data" << std::endl;
        } else {
            std::cout << GetMonthName(month) << " " << selectedYear << ": " << std::fixed << std::setprecision(1) << total
                      << " kWh/m2" << std::endl;
        }
    }
}
void WeatherData::CalculateSPCC(int month) {
    // Get the data from BST
    const std::map<int, std::vector<MonthData>>& allData = dataTree.GetData();

    std::vector<double> s_t_values;
    std::vector<double> s_r_values;
    std::vector<double> t_r_values;

    for (const auto& yearDataPair : allData) {
        // Rename the local variable to avoid shadowing
        //int yearData = yearDataPair.first;
        const std::vector<MonthData>& monthData = yearDataPair.second;

        double sum_s = 0.0;
        double sum_t = 0.0;
        double sum_r = 0.0;
        double sum_s_t = 0.0;
        double sum_s_r = 0.0;
        double sum_t_r = 0.0;
        int count = 0;

        for (const MonthData& data : monthData) {
            if (data.m_month == month) {
                sum_s += data.m_windSpeed;
                sum_t += data.m_temperature;
                sum_r += data.m_solarRadiation;
                sum_s_t += data.m_windSpeed * data.m_temperature;
                sum_s_r += data.m_windSpeed * data.m_solarRadiation;
                sum_t_r += data.m_temperature * data.m_solarRadiation;
                count++;
            }
        }

        if (count > 0) {
            double mean_s = sum_s / count;
            double mean_t = sum_t / count;
            double mean_r = sum_r / count;
            double mean_s_t = sum_s_t / count;
            double mean_s_r = sum_s_r / count;
            double mean_t_r = sum_t_r / count;

            double covariance_s_t = mean_s_t - (mean_s * mean_t);
            double covariance_s_r = mean_s_r - (mean_s * mean_r);
            double covariance_t_r = mean_t_r - (mean_t * mean_r);

            double variance_s = 0.0;
            double variance_t = 0.0;
            double variance_r = 0.0;

            for (const MonthData& data : monthData) {
                if (data.m_month == month) {
                    variance_s += pow(data.m_windSpeed - mean_s, 2);
                    variance_t += pow(data.m_temperature - mean_t, 2);
                    variance_r += pow(data.m_solarRadiation - mean_r, 2);
                }
            }

            variance_s /= count;
            variance_t /= count;
            variance_r /= count;

            double s_t_spcc = covariance_s_t / sqrt(variance_s * variance_t);
            double s_r_spcc = covariance_s_r / sqrt(variance_s * variance_r);
            double t_r_spcc = covariance_t_r / sqrt(variance_t * variance_r);

            s_t_values.push_back(s_t_spcc);
            s_r_values.push_back(s_r_spcc);
            t_r_values.push_back(t_r_spcc);
        }
    }

   // Calculate overall average SPCC values for each combination
double overall_s_t_spcc = CalculateAverage(s_t_values);
double overall_s_r_spcc = CalculateAverage(s_r_values);
double overall_t_r_spcc = CalculateAverage(t_r_values);



    // Display the results
    std::cout << "Sample Pearson Correlation Coefficient for " << GetMonthName(month) << std::endl;
    std::cout << "S_T: " << std::fixed << std::setprecision(2) << overall_s_t_spcc << std::endl;
    std::cout << "S_R: " << std::fixed << std::setprecision(2) << overall_s_r_spcc << std::endl;
    std::cout << "T_R: " << std::fixed << std::setprecision(2) << overall_t_r_spcc << std::endl;
}


int WeatherData::GetCurrentYear() {
    // Get the current time
    std::time_t t = std::time(nullptr);
    // Convert it to a tm struct
    std::tm* tm = std::localtime(&t);
    // Return the year field (note that it is offset by 1900)
    return tm->tm_year + 1900;
}

void WeatherData::WriteDataToFile(int selectedYear) {
    // Check if the selectedYear is valid
    if (selectedYear < 0 || selectedYear > GetCurrentYear()) {
        std::cout << "Invalid year: " << selectedYear << std::endl;
        return;
    }

    std::ofstream file("data/WindTempSolar.csv");
    if (!file.is_open()) {
        std::cout << "Error opening file: WindTempSolar.csv" << std::endl;
        return;
    }

    file << selectedYear << std::endl;

    bool yearDataAvailable = false;

    // Define a small positive number for floating point comparison
    //const double EPSILON = 1e-6;

    for (int month = 1; month <= 12; ++month) {
        std::vector<MonthData> monthDataList = dataTree.Search(month, selectedYear);
        // pass the pointers to the member functions of MonthData
        double windSpeedAverage = CalculateAverage(monthDataList, &MonthData::getWindSpeed);
        double windSpeedStdev = CalculateStandardDeviation(monthDataList, &MonthData::getWindSpeed);
        double temperatureAverage = CalculateAverage(monthDataList, &MonthData::getTemperature);
        double temperatureStdev = CalculateStandardDeviation(monthDataList, &MonthData::getTemperature);
        double solarRadiationSum = CalculateTotal(monthDataList, &MonthData::getSolarRadiation);

        // Write the data to the file if there is any
        if (!monthDataList.empty()) {
            file << GetMonthName(month) << ","
                 << std::fixed << std::setprecision(1) << windSpeedAverage << "(" << windSpeedStdev << "),"
                 << std::fixed << std::setprecision(1) << temperatureAverage << "(" << temperatureStdev << "),"
                 << std::fixed << std::setprecision(1) << solarRadiationSum << std::endl;

            yearDataAvailable = true;
        }
    }

    // Write no data if there is none for the year
    if (!yearDataAvailable) {
        file << "No data for that year" << std::endl; // Changed this line
    }

    file.close();
    std::cout << "Data written to WindTempSolar.csv" << std::endl;
}

// Check if the entered year exists in the loaded data
bool WeatherData::IsYearValid(int selectedYear) const {
    // Check if selectedYear exists in the loaded data
    return dataTree.GetData().find(selectedYear) != dataTree.GetData().end();
}

