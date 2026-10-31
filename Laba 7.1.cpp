#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** a, const int rowCount, const int colCount);
void Sort(int** a, const int rowCount, const int colCount);
void Change(int** a, const int col1, const int col2, const int rowCount);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k);

int main()
{
    srand((unsigned)time(NULL));    // ініціалізація генератора випадкових чисел

    int Low = -6;                   // нижня межа діапазону значень елементів матриці
    int High = 31;                  // верхня межа діапазону значень елементів матриці
    int rowCount = 7;               // кількість рядків матриці
    int colCount = 5;               // кількість стовпчиків матриці

    int** a = new int* [rowCount];   // створили динамічну матрицю: масив вказівників на рядки
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    cout << "Matrix:" << endl;
    Print(a, rowCount, colCount);

    Sort(a, rowCount, colCount);
    cout << "Sorted matrix:" << endl;
    Print(a, rowCount, colCount);

    int S = 0;                      // сума елементів, які задовольняють критерію
    int k = 0;                      // кількість елементів, які задовольняють критерію
    Calc(a, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:" << endl;
    Print(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];              // знищили рядки матриці
    delete[] a;                     // знищили масив вказівників на рядки

    return 0;
}

// формування матриці випадковими числами з [Low; High]
void Create(int** a, const int rowCount, const int colCount, const int Low, const int High)
{
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

// виведення матриці у вигляді таблиці
void Print(int** a, const int rowCount, const int colCount)
{
    cout << endl;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

// впорядкування стовпчиків матриці методом обміну ("бульбашки"):
// елементи 1-го рядка - за зростанням;
// при однакових елементах 1-го рядка - елементи 2-го рядка за зростанням;
// при однакових елементах 1-го і 2-го рядків - елементи 3-го рядка за спаданням
void Sort(int** a, const int rowCount, const int colCount)
{
    for (int j0 = 0; j0 < colCount - 1; j0++)
        for (int j1 = 0; j1 < colCount - j0 - 1; j1++)
            if ((a[0][j1] > a[0][j1 + 1])
                ||
                (a[0][j1] == a[0][j1 + 1] &&
                    a[1][j1] > a[1][j1 + 1])
                ||
                (a[0][j1] == a[0][j1 + 1] &&
                    a[1][j1] == a[1][j1 + 1] &&
                    a[2][j1] < a[2][j1 + 1]))
                Change(a, j1, j1 + 1, rowCount);
}

// обмін місцями двох стовпчиків матриці з номерами col1 та col2
void Change(int** a, const int col1, const int col2, const int rowCount)
{
    int tmp;
    for (int i = 0; i < rowCount; i++)
    {
        tmp = a[i][col1];
        a[i][col1] = a[i][col2];
        a[i][col2] = tmp;
    }
}

// обчислення суми S та кількості k елементів, які задовольняють критерію
// (додатні, крім тих, хоча б один індекс яких кратний 3), та заміна цих елементів нулями
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k)
{
    S = 0;
    k = 0;
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            if (a[i][j] > 0 && !(i % 3 == 0 || j % 3 == 0))
            {
                S += a[i][j];
                k++;
                a[i][j] = 0;
            }
}