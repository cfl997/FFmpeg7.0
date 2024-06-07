#include <stdio.h>
#include <stdlib.h>
#include "ffmpeg.h"

int main() {
    char filePath[] = "../../resource/lenna-500X500.mp4";
    int  videoStreamIndex = -1;//��Ƶ�������������е�����
    int ret = 0;

    AVFormatContext* fmtCtx = NULL;
    AVPacket* pkt = NULL;
    AVCodecContext* codecCtx = NULL;
    AVCodecParameters* avCodecPara = NULL;
    const AVCodec* codec = NULL;

    do {
        //����һ��AVFormatContext��FFMPEG���еĲ�����Ҫͨ�����AVFormatContext������
        fmtCtx = avformat_alloc_context();


        if ((ret = avformat_open_input(&fmtCtx, filePath, NULL, NULL)) != 0) {
            printf("cannot open video file\n");
            break;
        }

        if ((ret = avformat_find_stream_info(fmtCtx, NULL)) < 0) {
            printf("cannot retrive video info\n");
            break;
        }

        //ѭ��������Ƶ�а���������Ϣ��ֱ���ҵ���Ƶ���͵���
        //�㽫���¼���� ���浽videoStreamIndex������
        for (unsigned int i = 0; i < fmtCtx->nb_streams; i++) {
            if (fmtCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoStreamIndex = i;
                break;
            }
        }

        if (videoStreamIndex == -1) {
            printf("cannot find video stream\n");
            break;
        }

        //��ӡ����������Ϣ������ ������ ����ʽ��
        av_dump_format(fmtCtx, 0, filePath, 0);

        //=================================  ���ҽ����� ===================================//
        avCodecPara = fmtCtx->streams[videoStreamIndex]->codecpar;
        codec = avcodec_find_decoder(avCodecPara->codec_id);
        if (codec == NULL) {
            printf("cannot find decoder\n");
            break;
        }
        //���ݽ�������������������������
        codecCtx = avcodec_alloc_context3(codec);
        avcodec_parameters_to_context(codecCtx, avCodecPara);
        if (codecCtx == NULL) {
            printf("Cannot alloc context.");
            break;
        }

        //================================  �򿪽����� ===================================//
        if ((ret = avcodec_open2(codecCtx, codec, NULL)) < 0) { 
            printf("cannot open decoder\n");
            break;
        }

        //=========================== ����AVPacket�ṹ�� ===============================//
        int       i = 0;//����֡����
        pkt = av_packet_alloc();                      //����һ��packet
        av_new_packet(pkt, codecCtx->width * codecCtx->height); //����packet������

        //===========================  ��ȡ��Ƶ��Ϣ ===============================//
        while (av_read_frame(fmtCtx, pkt) >= 0) { //��ȡ����һ֡��Ƶ  ���ݴ���һ��AVPacket�Ľṹ��
            if (pkt->stream_index == videoStreamIndex) {
                i++;//ֻ������Ƶ֡
            }
            av_packet_unref(pkt);//����pkt������
        }
        printf("There are %d frames int total.\n", i);
    } while (0);
    //===========================�ͷ�����ָ��===============================//
    av_packet_free(&pkt);
    avcodec_close(codecCtx);
    avformat_close_input(&fmtCtx);
    avformat_free_context(fmtCtx);

    return ret;
}
