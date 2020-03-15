#include <string>
#include <sstream>
#include <iostream>
#include <pthread.h>

extern "C"
{
#include "libavformat/avformat.h"
}

using namespace std;

int main()
{
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

    cout << "时长为：" << durTime << endl;

    cout << "流数：" << stream_number << endl;

    for (int i = 0; i < stream_number; i++)
    {
        // AVCodecContext *acc = afc->streams[i]->codec;
        AVCodecParameters *acc = afc->streams[i]->codecpar;
        if (acc->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);
            if (!codec)
            {
                cout << "没有该类型解码器" << endl;
            }
            AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
            avcodec_parameters_to_context(codec_ctx, acc);
            int result = avcodec_open2(codec_ctx, codec, nullptr);
            if (result != 0)
            {
                char buf[1024] = {0};
                av_strerror(result, buf, sizeof(buf));
            }
            cout << "解码器打开成功" << endl;
        }
    }

    return 0;
}
