#include <stdio.h>
#include <string>
#define emcc false

#if emcc == true
#include <emscripten.h>
#endif

using namespace std;

int countplus()
{
  return 6666;
}

int main()
{
  return 0;
}

#if emcc == true
extern "C"
{
  EMSCRIPTEN_KEEPALIVE
  int count()
  {
    return countplus();
  }
}
#endif