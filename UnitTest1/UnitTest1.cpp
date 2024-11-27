#include "pch.h"
#include "CppUnitTest.h"
#include "..\PR12.1.cpp"
#include <fstream>
#include <vector>
#include <cmath>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

void ProcessBIN(char* fname, char* gname);

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest)
    {
    public:

        TEST_METHOD(TestCreateBIN)
        {
            // Тестування функції CreateBIN
            char inputFile[] = "test_create.bin";

            // Створюємо файл для тесту
            std::ofstream fout(inputFile, std::ios::binary);
            std::vector<int> inputNumbers = { 6, 7, 8 }; // тестові числа
            for (int number : inputNumbers) {
                fout.write((char*)&number, sizeof(number));
            }
            fout.close();

            // Перевіряємо, чи числа записані правильно
            std::ifstream fin(inputFile, std::ios::binary);
            Assert::IsTrue(fin.is_open(), L"Input file did not open.");

            std::vector<int> readNumbers;
            int number;
            while (fin.read((char*)&number, sizeof(number))) {
                readNumbers.push_back(number);
            }
            fin.close();

            Assert::AreEqual((size_t)3, readNumbers.size(), L"Incorrect number of integers read.");
            Assert::AreEqual(6, readNumbers[0], L"First number is incorrect.");
            Assert::AreEqual(7, readNumbers[1], L"Second number is incorrect.");
            Assert::AreEqual(8, readNumbers[2], L"Third number is incorrect.");
        }
    };
};