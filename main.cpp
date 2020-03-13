#include <string>
#include <sstream>
#include <iostream>
#include <pthread.h>

extern "C"
{
#include "libavformat/avformat.h"
}
using namespace std;

string intTostring(int num)
{
    int a = num;
    stringstream ssTemp;
    ssTemp << a;
    string strDst = ssTemp.str();
    return strDst;
}

int main()
{
    av_register_all();

    AVFormatContext *afc = NULL;

    // 打开视频文件
    char path[] = "/Users/zhushijie/Downloads/m3u8-demo/a.mp4";
    int open_result = avformat_open_input(&afc, path, 0, 0);
    if (open_result < 0)
    {
        cout << "找不到视频文件" << endl;
    }
    else
    {
        cout << "视频打开成功" << endl;
    }
    int durTime = afc->duration / AV_TIME_BASE;

    unsigned int stream_number = afc->nb_streams;

    printf("%s\n", intTostring(stream_number).c_str());

    printf("%s\n", intTostring(durTime).c_str());

    for (int i = 0; i < stream_number; i++)
    {
        AVCodecContext *acc = afc->streams[i]->codec;
        if (acc->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);
            if (!codec)
            {
                cout << "没有该类型解码器" << endl;
            }
            int ret = avcodec_open2(acc, codec, NULL);
            if (ret != 0)
			{
				char buf[1024] = { 0 };
				av_strerror(ret, buf, sizeof(buf));
			}
			cout << "解码器打开成功" << endl;
        }
    }

    return 0;
}
