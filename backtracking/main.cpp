#include <iostream>
#include <vector>
#include <cmath>
// #define DEBUG
#define maxN 40

using namespace std;

// Печатает содержимое Table.
void printTable(const vector<vector<int>>& Table, int N)
{
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            cout.width(3);
            cout << Table[i][j] << " ";
        }
        cout << endl;
    }
}

// Проверка на выход за пределы массива
bool isOutOfBounds(int x, int y, int width, int N)
{
    return ((width>(N-x)) || (width>(N-y)));
}

void removePart(vector<vector<int>>& Table, int N, int x, int y, int partNumber)
{
    for(int i = y; (i < N) && (Table[i][x]==partNumber); ++i)
    {
        for (int j = x; (j < N) && (Table[i][j]==partNumber); ++j)
        {
            Table[i][j]=0;
        }
    }
}

// N - размер столешницы, x,y - координаты части, width - ее размер, partNumber - номер
bool setPart(vector<vector<int>>& Table, int N, int x, int y, int width, int partNumber)
{
    if (isOutOfBounds(x, y, width, N)) return false;
    for(int i = 0; i < width; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (!Table[y+i][x+j])
                Table[y+i][x+j]=partNumber;
            else
            {
                removePart(Table, N, x, y, partNumber);
                return false;
            }
        }
    }
    return true;
}

bool findFreeCell(vector<vector<int>>& Table, int N, int& x, int& y)
{
    while (Table[y][x]!=0)
    {
        if (x==N-1)
        {
            x=0;
            ++y;
        }
        else ++x;
        if (x>=N || y>=N)
            return false;
    }
    return true;
}

//
int buildPrime(vector<vector<int>>& Table, int N, int x, int y, vector<vector<int>>& bestTable)
{
    #ifdef DEBUG
        printTable(Table, N);
        cout << endl;
    #endif

    static int partNmbr = 5; // 4 детали уже есть
    static int bestPartNmbr = 20;

    if (partNmbr>bestPartNmbr) return 0;
    if (findFreeCell(Table, N, x, y)) // Если есть свободная клетка
    {
        #ifdef DEBUG
            cout << x << " " << y << endl;
        #endif
        for (int i = N-1; i > 0; --i)
        {
            if (setPart(Table, N, x, y, i, partNmbr)) // То пробуем для нее различные размеры детали
            {
                #ifdef DEBUG
                    cout << "Part is set" << endl;
                #endif
                ++partNmbr;
                buildPrime(Table, N, x, y, bestTable); // И для каждого размера детали проходимся по остальным клеткам
                --partNmbr;
            }
            removePart(Table, N, x, y, partNmbr);
        }
    }
    else if ((partNmbr-1)<bestPartNmbr)
    {
        bestPartNmbr = partNmbr-1; // Потому что часть под номером partNmbr пристроить не удалось
        bestTable = Table;
    }
    return bestPartNmbr;
}

// Возвращает размер части
int findPart(vector<vector<int>>& Table, int N, int& x, int& y, int K)
{
    while (Table[y][x]!=K)
    {
        if (x==N-1)
        {
            x=0;
            ++y;
        }
        else ++x;
        if (x>=N || y>=N)
            return false;
    }
    int i = 0;
    while (Table[y][x+i]==K)
    {
        if ((x+i)<N)
        {
            ++i;
        }
        else return --i;
    }
    return i;
}

void printParts(vector<vector<int>>& Table, int N, int partNmbr)
{
    int x, y, size;
    for(int i = 1; i <= partNmbr; ++i)
    {
        x = 0;
        y = 0;
        size = findPart(Table, N, x, y, i);
        cout << x+1 << " " << y+1 << " " << size << endl;
    }
}

int solve(vector<vector<int>>& Table, vector<vector<int>>& BestTable, int N)
{
    if ((N%2)==0)
    {
        cout << 4 << endl;
        cout << 1       << " " << 1     << " " << N/2 << endl;
        cout << 1       << " " << N/2+1 << " " << N/2 << endl;
        cout << N/2+1   << " " << 1     << " " << N/2 << endl;
        cout << N/2+1   << " " << N/2+1 << " " << N/2 << endl;
    }
    else if ((N%3)==0)
    {
        int K = N/3;
        cout << 6 << endl;
        cout << 1       << " " << 1     << " " << 2*K << endl;
        cout << 2*K+1   << " " << 1     << " " << K << endl;
        cout << 2*K+1   << " " << K+1   << " " << K <<endl;
        cout << 2*K+1   << " " << 2*K+1 << " " << K << endl;
        cout << K+1     << " " << 2*K+1 << " " << K << endl;
        cout << 1       << " " << 2*K+1 << " " << K << endl;
    }
    else if ((N%5)==0)
    {
        int K=N/5;
        cout << 8 << endl;
        cout << 1       << " " << 1     << " " << 3*K << endl;
        cout << 1+3*K   << " " << 1     << " " << 2*K << endl;
        cout << 1+3*K   << " " << 1+2*K << " " << 2*K << endl;
        cout << 1       << " " << 1+3*K << " " << 2*K << endl;
        cout << 1+2*K   << " " << 1+3*K << " " << K   << endl;
        cout << 1+2*K   << " " << 1+4*K << " " << K   << endl;
        cout << 1+3*K   << " " << 1+4*K << " " << K   << endl;
        cout << 1+4*K   << " " << 1+4*K << " " << K   << endl;
    }
    else
    {
        // Ставим заранее известные детали, сокращая "размеры" столешницы для вычислений примерно на 75%
        setPart(Table, N, 0, 0, N/2+1, 1);
        setPart(Table, N, N/2+1, 0, N/2, 2);
        setPart(Table, N, 0, N/2+1, N/2, 3);
        setPart(Table, N, N/2+1, N/2, 1, 4);
        int K = buildPrime(Table, N, N/2+2, N/2, BestTable);
        cout << K << endl;
        printParts(BestTable, N, K);
    }
}

int main()
{
    int N;
    cin >> N;
    if (N>maxN)
    {
        cout << "Why is N>" << maxN << "?" << endl;
        return 0;
    }
    vector<vector<int>> Table(N, vector<int>(N,0)); // Инициализировали массив NxN нулями
    vector<vector<int>> Result(N, vector<int>(N));
    solve(Table, Result, N);
    return 0;
}
