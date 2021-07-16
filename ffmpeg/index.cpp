#include <string>
#include <sstream>
#include <iostream>
#include <pthread.h>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
}

using namespace std;

int test()
{
  char out_name[] = "/Users/zhushijie/Desktop/m3u8-demo/testpic.jpg";
  AVFormatContext *pFormatCtx = avformat_alloc_context();
  pFormatCtx->oformat = av_guess_format("mjpeg", NULL, NULL);
  AVCodecContext *pCodeCtx = NULL;
  if (avio_open(&pFormatCtx->pb, out_name, AVIO_FLAG_READ_WRITE) < 0)
  {
    printf("Couldn't open output file.");
    return -1;
  }

  AVCodec *pCodec = avcodec_find_encoder(pFormatCtx->oformat->video_codec);

  AVStream *pAVStream = avformat_new_stream(pFormatCtx, pCodec);
  if (pAVStream == NULL)
  {
    return -1;
  }

  if (!pCodec)
  {
    printf("Could not find encoder\n");
    return -1;
  }

  pCodeCtx = avcodec_alloc_context3(pCodec);
  if (!pCodeCtx)
  {
    fprintf(stderr, "Could not allocate video codec context\n");
    exit(1);
  }

  if (avcodec_open2(pCodeCtx, pCodec, NULL) < 0)
  {
    printf("Could not open codec.");
    return -1;
  }
}

int main()
{
  AVFormatContext *afc = NULL;
  AVFrame *pFrame, *pFrameRGB;
  AVPacket packet; //存储压缩编码数据相关信息的结构体
  uint8_t *out_buffer;

  test();

  static struct SwsContext *img_convert_ctx;

  // 打开视频文件
  char path[] = "/Users/zhushijie/Desktop/m3u8-demo/test.mp4";
  int open_result = avformat_open_input(&afc, path, 0, 0);
  if (open_result < 0)
  {
    cout << "找不到视频文件" << endl;
    return 1;
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
      pFrame = av_frame_alloc();
      pFrameRGB = av_frame_alloc();

      while (av_read_frame(afc, &packet) > 0)
      {
        /* code */
      }
    }
  }

  return 0;
}
