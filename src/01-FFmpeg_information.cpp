#include "ffmpeg.h"


int main()
{
	unsigned codecVer = avcodec_version();
	printf("FFmpeg version is: %s, avcodec version is: %d\n.", FFMPEG_VERSION, codecVer);



	int ver_major, ver_minor, ver_micro;
	ver_major = (codecVer >> 16) & 0xff;
	ver_minor = (codecVer >> 8) & 0xff;
	ver_micro = (codecVer) & 0xff;
	printf("Current ffmpeg version is: %s ,avcodec version is: %d=%d.%d.%d\n", FFMPEG_VERSION, codecVer, ver_major, ver_minor, ver_micro);

	return 0;
}