#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // відкриваємо файл для запису
    char ch;
    int number;

    do {
        cout << "Enter an integer: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // записуємо число у файл
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // відкриваємо файл для читання

    if (!fin) { // перевіряємо, чи файл відкрився
        cout << "Error opening file: " << fname << endl;
        return;
    }

    cout << "Contents of " << fname << ":\n";

    // Визначаємо тип даних у файлі
    fin.seekg(0, ios::end);
    size_t fileSize = fin.tellg();
    fin.seekg(0, ios::beg);

    if (fileSize % sizeof(double) == 0) { // Якщо файл містить double
        double number;
        while (fin.read((char*)&number, sizeof(number))) {
            cout << number << " ";
        }
    }
    else if (fileSize % sizeof(int) == 0) { // Якщо файл містить int
        int number;
        while (fin.read((char*)&number, sizeof(number))) {
            cout << number << " ";
        }
    }
    else {
        cout << "Unknown data format in file!" << endl;
    }

    cout << endl;
}

void ProcessBIN(char* fname, char* gname) {
    ifstream fin(fname, ios::binary); // відкриваємо вхідний файл
    ofstream fout(gname, ios::binary); // відкриваємо вихідний файл

    if (!fin) { // перевіряємо, чи файл відкрився
        cout << "Error opening input file: " << fname << endl;
        return;
    }

    int number;
    int sumOdd = 0, sumEven = 0;
    int countOdd = 0, countEven = 0;

    // Підраховуємо суми і кількості парних та непарних чисел
    while (fin.read((char*)&number, sizeof(number))) {
        if (number % 2 == 0) { // парне число
            sumEven += number;
            countEven++;
        }
        else { // непарне число
            sumOdd += number;
            countOdd++;
        }
    }

    // Обчислюємо середнє арифметичне за допомогою if-else
    double avgOdd = 0, avgEven = 0;

    if (countOdd > 0) {
        avgOdd = (double)sumOdd / countOdd;
    }
    else {
        avgOdd = 0;
    }

    if (countEven > 0) {
        avgEven = (double)sumEven / countEven;
    }
    else {
        avgEven = 0;
    }

    // Записуємо результати у вихідний файл
    fout.write((char*)&avgOdd, sizeof(avgOdd));
    fout.write((char*)&avgEven, sizeof(avgEven));
}

int main() {
    char fname[100]; // ім'я вхідного файлу
    char gname[100]; // ім'я вихідного файлу

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // створюємо вхідний бінарний файл

    PrintBIN(fname); // виводимо вміст вхідного файлу

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // обробляємо файл

    PrintBIN(gname); // виводимо вміст вихідного файлу

    return 0;
}
// 5 3 10