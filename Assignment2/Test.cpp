#include "test.h"

void Test::RunAllTests() {
    TestLoadData();
    TestSearch();
    TestCalculateAverage();
    TestCalculateTotal();
    TestCalculateStandardDeviation();
    TestWriteDataToFile();
    TestDisplayDataForYear();
    TestIsYearValid();
    TestCalculateSPCC();
}

void Test::TestLoadData() {
    // Test valid data file
    WeatherData weatherData1;
    bool result1 = weatherData1.LoadData("data/test_data1.csv");
    std::cout << "TestLoadData - Test 1: " << (result1 ? "Pass" : "Fail") << std::endl;

    // Test invalid data file
    WeatherData weatherData2;
    bool result2 = weatherData2.LoadData("data/non_existent_file.csv");
    std::cout << "TestLoadData - Test 2: " << (!result2 ? "Pass" : "Fail") << std::endl;

    // Test empty data file
    WeatherData weatherData3;
    bool result3 = weatherData3.LoadData("data/empty_file.csv");
    std::cout << "TestLoadData - Test 3: " << (!result3 ? "Pass" : "Fail") << std::endl;
}

void Test::TestSearch() {
    // Test valid month and year combination
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    std::vector<MonthData> result1 = weatherData.Search(1, 2023);
    std::cout << "TestSearch - Test 1: " << (result1.size() == 3 ? "Pass" : "Fail") << std::endl;

    // Test invalid month
    std::vector<MonthData> result2 = weatherData.Search(13, 2023);
    std::cout << "TestSearch - Test 2: " << (result2.empty() ? "Pass" : "Fail") << std::endl;

    // Test invalid year
    std::vector<MonthData> result3 = weatherData.Search(1, 2020);
    std::cout << "TestSearch - Test 3: " << (result3.empty() ? "Pass" : "Fail") << std::endl;
}

void Test::TestCalculateAverage() {
    // Test CalculateAverage() with wind speed for January
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    double averageWindSpeed = weatherData.CalculateAverage(1, &MonthData::getWindSpeed);
    std::cout << "TestCalculateAverage - Test 1: " << (IsApproximatelyEqual(averageWindSpeed, 3.0) ? "Pass" : "Fail") << std::endl;

    // Test CalculateAverage() with temperature for February
    double averageTemperature = weatherData.CalculateAverage(2, &MonthData::getTemperature);
    std::cout << "TestCalculateAverage - Test 2: " << (IsApproximatelyEqual(averageTemperature, 15.5) ? "Pass" : "Fail") << std::endl;
}

void Test::TestCalculateTotal() {
    // Test CalculateTotal() with wind speed for January
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    double totalWindSpeed = weatherData.CalculateTotal(1, &MonthData::getWindSpeed);
    std::cout << "TestCalculateTotal - Test 1: " << (IsApproximatelyEqual(totalWindSpeed, 9.0) ? "Pass" : "Fail") << std::endl;

    // Test CalculateTotal() with temperature for February
    double totalTemperature = weatherData.CalculateTotal(2, &MonthData::getTemperature);
    std::cout << "TestCalculateTotal - Test 2: " << (IsApproximatelyEqual(totalTemperature, 31.0) ? "Pass" : "Fail") << std::endl;
}

void Test::TestCalculateStandardDeviation() {
    // Test CalculateStandardDeviation() with wind speed for January
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    double stdevWindSpeed = weatherData.CalculateStandardDeviation(1, &MonthData::getWindSpeed);
    std::cout << "TestCalculateStandardDeviation - Test 1: " << (IsApproximatelyEqual(stdevWindSpeed, 0.5) ? "Pass" : "Fail") << std::endl;

    // Test CalculateStandardDeviation() with temperature for February
    double stdevTemperature = weatherData.CalculateStandardDeviation(2, &MonthData::getTemperature);
    std::cout << "TestCalculateStandardDeviation - Test 2: " << (IsApproximatelyEqual(stdevTemperature, 2.5) ? "Pass" : "Fail") << std::endl;
}

void Test::TestWriteDataToFile() {
    // Test WriteDataToFile() for year 2023
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    weatherData.WriteDataToFile(2023);
    // Manual verification required for the generated CSV file
    std::cout << "TestWriteDataToFile - Test 1: Manual verification required" << std::endl;
}

void Test::TestDisplayDataForYear() {
    // Test DisplayDataForYear() for year 2023
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    weatherData.DisplayDataForYear(2023);
    // Manual verification required for the displayed data
    std::cout << "TestDisplayDataForYear - Test 1: Manual verification required" << std::endl;
}

void Test::TestIsYearValid() {
    // Test valid year
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    bool result1 = weatherData.IsYearValid(2023);
    std::cout << "TestIsYearValid - Test 1: " << (result1 ? "Pass" : "Fail") << std::endl;

    // Test invalid year
    bool result2 = weatherData.IsYearValid(2020);
    std::cout << "TestIsYearValid - Test 2: " << (!result2 ? "Pass" : "Fail") << std::endl;
}

void Test::TestCalculateSPCC() {
    // Test CalculateSPCC() for January
    WeatherData weatherData;
    weatherData.LoadData("data/test_data1.csv");
    weatherData.CalculateSPCC(1);
    // Manual verification required for the displayed sPCC
    std::cout << "TestCalculateSPCC - Test 1: Manual verification required" << std::endl;
}


