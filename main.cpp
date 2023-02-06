#include <iostream>
#include <fstream>
#include <list>
#include <random>
#include <time.h>

using namespace std;

class Hash

{
    int BUCKET;

    list<int> *table;

public:
    Hash(int b);

    void insertItem(int x);

    void deleteItem(int key);

    int hashFunction(int x)
    {
        float f;

        f = x * (rand() * 1.0) / (RAND_MAX * 1.0);
        f = f - int(f);
        return BUCKET * f;
    }

    void displayHash();
    float displayCollisions();
    float displayFindIndex();
};

Hash::Hash(int b)

{

    this->BUCKET = b;

    table = new list<int>[BUCKET];
}

void Hash::insertItem(int key)

{

    int index = hashFunction(key);

    table[index].push_back(key);
}

void Hash::deleteItem(int key)

{
    list<int>::iterator i;
    for (int index = 0; index < BUCKET; index++)
    {
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            if (*i == key)
            {
                table[index].erase(i);
                index = BUCKET;
                break;
            }
        }
    }
}

void Hash::displayHash()
{

    for (int i = 0; i < BUCKET; i++)
    {
        cout << i;

        for (auto x : table[i])
        {
            cout << " --> " << x;
        }
        cout << endl;
    }
}

float Hash::displayCollisions()
{
    list<int>::iterator i;
    int count = -1;
    int summ = 0;
    for (int index = 0; index < BUCKET; index++)
    {
        count = -1;
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            count++;
        }

        summ += count * (count + 1) / 2;
    }
    return summ * 1.0 / BUCKET;
}

float Hash::displayFindIndex()
{
    int count = 0;
    int key = 0;
    list<int>::iterator i;
    list<int>::iterator j;
    for (int index = 0; index < BUCKET; index++)
    {
        for (i = table[index].begin(); i != table[index].end(); i++)
        {
            key = *i;
        }
        for (int index2 = 0; index2 < BUCKET; index2++)
        {
            for (j = table[index2].begin(); j != table[index2].end(); j++)
            {

                if (*j == key)
                {
                    count++;
                    index2 = BUCKET;
                    break;
                }
                else
                    count++;
            }
        }
    }

    return count * 1.0 / BUCKET;
}

int main()

{
    int lengthP = 0, number = 0;
    list<int> p;
    srand(time(0));

    ifstream fin("1.txt");
    while (!fin.eof())
    {
        lengthP++;
        fin >> number;
        p.push_back(number);
    }
    fin.close();

    cout << "\nElements in file:\n"
         << endl;
    for (auto x : p)
    {
        cout << x << endl;
    }
    cout << endl;

    Hash h(lengthP);

    for (auto x : p)
        h.insertItem(x);

    h.displayHash();
    cout << "\nAverage of kolizii: " << h.displayCollisions() << endl;
    cout << "Average of comparisons: " << h.displayFindIndex() << endl;

    int a = 0;
    cout << endl
         << "Delete element: " << endl;
    cin >> a;
    cout << endl;
    h.deleteItem(a);

    h.displayHash();
    cout << "\nAverage of kolizii: " << h.displayCollisions() << endl;
    cout << "Average of comparisons: " << h.displayFindIndex() << endl;

    return 0;
}
