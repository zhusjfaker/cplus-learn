#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <emscripten.h>

using namespace std;

unsigned char *drawpic()
{
    fstream file;
    file.open("/Users/zhushijie/Desktop/abc.jpeg", ios_base::binary);
    file.seekg(0, ios::end);
    size_t srcSize = file.tellg();
    cout << "文件大小" << srcSize << endl;
    unsigned char *memo = new unsigned char[srcSize]; //存储读取字符串
    file.read(memo, srcSize);
    cout << "数据数组" << memo << endl;
    file.close();
    file.clear();
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