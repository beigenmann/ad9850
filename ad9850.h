#ifndef __CHAR_DEVICE_H__
#define __CHAR_DEVICE_H__

#define MAJOR_DEVICE_NUM 30
#define MAX_MINOR_NUM   2

#define MEMDEV_NUM 2
#define MEMDEV_SIZE 4096
#define W_CLK 11
#define FU_UD 25
#define DATA 9
#define RESET 8

#define HIGH 1
#define LOW 0
struct mem_dev {
    char *data;
    unsigned long size;
};
int send_bits(char data);
int spread(unsigned int freq);
int dds_frequency(unsigned int freq, unsigned char phase);
#endif
