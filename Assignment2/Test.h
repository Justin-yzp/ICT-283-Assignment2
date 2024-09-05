#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include <vector>
#include "WeatherData.h"

class Test {
public:
    void RunAllTests();

private:
    void TestLoadData();
    void TestSearch();
    void TestCalculateAverage();
    void TestCalculateTotal();
    void TestCalculateStandardDeviation();
    void TestWriteDataToFile();
    void TestDisplayDataForYear();
    void TestIsYearValid();
    void TestCalculateSPCC();

};

#endif // TEST_H
