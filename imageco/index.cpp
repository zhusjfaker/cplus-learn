#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <emscripten.h>

using namespace std;

char *drawpic()
{
    fstream file("/Users/zhushijie/Desktop/ssh.txt", ios::in|ios::binary|ios::ate);
    file.seekg(0, ios::end);
    size_t srcSize = file.tellg();
    cout << "文件大小" << srcSize << endl;
    char *memo = new char[srcSize]; //存储读取字符串
    file.read(memo, srcSize);
    cout << "数据数组" << memo << endl;
    file.close();
    return memo;
}

int main()
{
    drawpic();
    return 0;
}

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    char *pic()
    {
        return drawpic();
    }
}