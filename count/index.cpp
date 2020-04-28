#include <stdio.h>
#include <string>
#include <emscripten.h>

using namespace std;

int countplus()
{
    return 6666;
}


int main()
{
    return 0;
}

extern "C"
{
    EMSCRIPTEN_KEEPALIVE
    int count()
    {
        return countplus();
    }
}