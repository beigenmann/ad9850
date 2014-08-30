#ifndef __AD9850_H__
#define __AD9850_H__

#define W_CLK 11
#define FU_UD 25
#define DATA 9
#define RESET 8

#define HIGH 1
#define LOW 0

// Store and Show functions.....
static ssize_t set_frequence(struct class *cls, struct class_attribute *attr,
		const char *buf, size_t count);
static ssize_t get_frequence(struct class *cls, struct class_attribute *attr,
		char *buf);
int send_bits(char data);
int spread(unsigned int freq);
int dds_frequency(unsigned int freq, unsigned char phase);
#endif
