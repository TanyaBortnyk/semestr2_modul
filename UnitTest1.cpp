#include "pch.h"
#include "CppUnitTest.h"
#include "../modul/VectorUtils.h"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTestCpp1
{
    TEST_CLASS(VectorUtilsTests)
    {
    public:

        TEST_METHOD(TestNormalCase)
        {
            vector<int> vec = { 5, 2, 9, 1, 7 };

            auto result = findMinMax(vec);

            Assert::AreEqual(1, result.first);  // min
            Assert::AreEqual(9, result.second); // max
        }

        TEST_METHOD(TestSingleElement)
        {
            vector<int> vec = { 42 };

            auto result = findMinMax(vec);

            Assert::AreEqual(42, result.first);
            Assert::AreEqual(42, result.second);
        }

        TEST_METHOD(TestNegativeNumbers)
        {
            vector<int> vec = { -5, -10, -3 };

            auto result = findMinMax(vec);

            Assert::AreEqual(-10, result.first);
            Assert::AreEqual(-3, result.second);
        }

        TEST_METHOD(TestMixedNumbers)
        {
            vector<int> vec = { -2, 0, 3, -1 };

            auto result = findMinMax(vec);

            Assert::AreEqual(-2, result.first);
            Assert::AreEqual(3, result.second);
        }

        TEST_METHOD(TestEmptyVectorThrows)
        {
            vector<int> vec;

            try
            {
                findMinMax(vec);
                Assert::Fail(L"Expected EmptyContainer exception");
            }
            catch (const EmptyContainer&)
            {
                // ок Ч оч≥кувана помилка
            }
        }
    };
}