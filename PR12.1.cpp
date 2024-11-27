#include <iostream>
#include <fstream>
using namespace std;

void CreateBIN(char* fname) {
    ofstream fout(fname, ios::binary); // ��������� ���� ��� ������
    char ch;
    int number;

    do {
        cout << "Enter an integer: ";
        cin >> number;
        fout.write((char*)&number, sizeof(number)); // �������� ����� � ����
        cout << "Continue? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

void PrintBIN(char* fname) {
    ifstream fin(fname, ios::binary); // ��������� ���� ��� �������

    if (!fin) { // ����������, �� ���� ��������
        cout << "Error opening file: " << fname << endl;
        return;
    }

    cout << "Contents of " << fname << ":\n";

    // ��������� ��� ����� � ����
    fin.seekg(0, ios::end);
    size_t fileSize = fin.tellg();
    fin.seekg(0, ios::beg);

    if (fileSize % sizeof(double) == 0) { // ���� ���� ������ double
        double number;
        while (fin.read((char*)&number, sizeof(number))) {
            cout << number << " ";
        }
    }
    else if (fileSize % sizeof(int) == 0) { // ���� ���� ������ int
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
    ifstream fin(fname, ios::binary); // ��������� ������� ����
    ofstream fout(gname, ios::binary); // ��������� �������� ����

    if (!fin) { // ����������, �� ���� ��������
        cout << "Error opening input file: " << fname << endl;
        return;
    }

    int number;
    int sumOdd = 0, sumEven = 0;
    int countOdd = 0, countEven = 0;

    // ϳ��������� ���� � ������� ������ �� �������� �����
    while (fin.read((char*)&number, sizeof(number))) {
        if (number % 2 == 0) { // ����� �����
            sumEven += number;
            countEven++;
        }
        else { // ������� �����
            sumOdd += number;
            countOdd++;
        }
    }

    // ���������� ������ ����������� �� ��������� if-else
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

    // �������� ���������� � �������� ����
    fout.write((char*)&avgOdd, sizeof(avgOdd));
    fout.write((char*)&avgEven, sizeof(avgEven));
}

int main() {
    char fname[100]; // ��'� �������� �����
    char gname[100]; // ��'� ��������� �����

    cout << "Enter input file name: ";
    cin >> fname;
    CreateBIN(fname); // ��������� ������� ������� ����

    PrintBIN(fname); // �������� ���� �������� �����

    cout << "Enter output file name: ";
    cin >> gname;
    ProcessBIN(fname, gname); // ���������� ����

    PrintBIN(gname); // �������� ���� ��������� �����

    return 0;
}
// 5 3 10