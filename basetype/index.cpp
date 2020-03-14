#include <iostream>
#include <string>

using namespace std;

void print(int i)
{
    cout << "整数为: " << i << endl;
}

void print(string c)
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
    return 0;
}
