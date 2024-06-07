#include "ffmpeg.h"

#include <filesystem>

int main()
{
	AVFormatContext* fmt_ctx = avformat_alloc_context();
	int ret = 0;
	char* fileName = "../../resource/lenna-500X500.mp4";//文件地址

	do {
		if ((ret = avformat_open_input(&fmt_ctx, fileName, NULL, NULL)) < 0)
			break;

		//查找流信息（音频流和视频流）
		if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
			printf("Cannot find stream information\n");
			break;
		}

		av_dump_format(fmt_ctx, 0, fileName, 0);//输出视频信息
	} while (0);

	avformat_close_input(&fmt_ctx);//关闭文件
	return ret;
}