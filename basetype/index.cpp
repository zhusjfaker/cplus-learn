#include <iostream>
#include <string>
#include <array>
#include <vector>

using namespace std;

void print(int i)
{
    cout << "整数为: " << i << endl;
}

void print(string c)
{
    cout << "字符串为: " << c << endl;
}

void print(char c)
{
    cout << "字符串为: " << c << endl;
}

int main()
{
    string name = "tome";
    const int a = 123;
    string x = to_string(a);
    int z = stoi(x);
    print(z);
    print(x);
    char xyz[] = "asdajskdahsd";
    print(xyz);
    stpcpy(xyz, "666666666");
    print(xyz);
    vector<int> vlist;
    vlist.push_back(1);
    vlist.push_back(2);
    for (int i = 0; i < vlist.size(); i++)
    {
        cout << vlist[i] << ",";
    }
    array<int, 10> list = {10, 20};
    return 0;
}
