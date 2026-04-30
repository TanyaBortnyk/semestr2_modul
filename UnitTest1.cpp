#include "pch.h"
#include "CppUnitTest.h"
#include "../modul 2/WeatherUtils.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(WeatherTests)
    {
    public:

       
        void createFile(const std::string& filename, const std::string& content) {
            std::ofstream file(filename);
            file << content;
            file.close();
        }

        TEST_METHOD(TestReadTSV_Normal)
        {
            createFile("test.tsv",
                "2026-05-01\tLviv\t5\n"
                "2026-05-02\tLviv\t-2\n"
                "2026-05-01\tKyiv\t3\n");

            auto data = readTSV("test.tsv");

            Assert::AreEqual((size_t)3, data.size());
            Assert::AreEqual(std::string("Lviv"), data[0].city);
            Assert::AreEqual(5.0, data[0].temperature);
        }

        TEST_METHOD(TestComputeMinMax)
        {
            std::vector<WeatherRecord> data = {
                {"2026", "Lviv", 5},
                {"2026", "Lviv", -2},
                {"2026", "Kyiv", 3},
                {"2026", "Kyiv", 10}
            };

            auto result = computeMinMax(data);

            Assert::AreEqual(-2.0, result["Lviv"].first);
            Assert::AreEqual(5.0, result["Lviv"].second);

            Assert::AreEqual(3.0, result["Kyiv"].first);
            Assert::AreEqual(10.0, result["Kyiv"].second);
        }

        TEST_METHOD(TestAnomalousTemperatureThrows)
        {
            createFile("bad.tsv",
                "2024-01-01\tLviv\t150\n");

            try {
                readTSV("bad.tsv");
                Assert::Fail(L"Expected out_of_range exception");
            }
            catch (const std::out_of_range&) {
                // OK
            }
        }

        TEST_METHOD(TestEmptyFile)
        {
            createFile("empty.tsv", "");

            auto data = readTSV("empty.tsv");

            Assert::AreEqual((size_t)0, data.size());
        }

        TEST_METHOD(TestFileNotFound)
        {
            try {
                readTSV("no_file.tsv");
                Assert::Fail(L"Expected runtime_error");
            }
            catch (const std::runtime_error&) {
                // OK
            }
        }
    };
}