#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/major.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include "ad9850.h"

#define MAJOR_NUM 200
#define DEVICE_NAME "c"



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Benno Eigenmann");
MODULE_DESCRIPTION("AD9859 Driver for Raspberry Pi");


// Store and Show functions.....
static ssize_t set_frequence(struct class *cls, struct class_attribute *attr,
		const char *buf, size_t count);
static ssize_t get_frequence(struct class *cls, struct class_attribute *attr,
		char *buf);
static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static int ad9850_open(struct inode *i, struct file *f) {
	printk(KERN_INFO "Driver: open()\n");
	return 0;
}
static int ad9850_close(struct inode *i, struct file *f) {
	printk(KERN_INFO "Driver: close()\n");
	return 0;
}
static ssize_t ad9850_read(struct file *f, char __user *buf, size_t
		len, loff_t *off) {
	printk(KERN_INFO "Driver: read()\n");
	return 0;
}
static ssize_t ad9850_write(struct file *f, const char __user *buf,
		size_t len, loff_t *off) {
	printk(KERN_INFO "Driver: write()\n");
	return len;
}
static struct file_operations fops = { .owner = THIS_MODULE,
		.open = ad9850_open, .release = ad9850_close, .read = ad9850_read,
		.write = ad9850_write };

long int freq;

static struct class_attribute class_attr[] = { __ATTR(frequence, 0666,
		get_frequence, set_frequence), __ATTR_NULL };

static struct class ad9850_drv = { .name = "ad9850", .owner = THIS_MODULE,
		.class_attrs = (struct class_attribute *) &class_attr, };

// Show function definition.....
static ssize_t get_frequence(struct class *cls, struct class_attribute *attr,
		char *buf) {
	return sprintf(buf, "%li\n", freq);
}

// Store function definition ....
static ssize_t set_frequence(struct class *cls, struct class_attribute *attr,
		const char *buf, size_t count) {
	long int myLong = 0;
	if (kstrtol(buf, 10, &myLong) == 0) {
		freq = myLong;
		dds_frequency(freq, 0);
	}
	printk("lo = %li\n", myLong);
	return count;
}

static int __init ad9850_init(void) /* Constructor */
{	int status;
	printk(KERN_INFO "AD9850:  registered");
	if (alloc_chrdev_region(&first, 0, 1, "AD9850") < 0) {
		return -1;
	}
	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL) {
		unregister_chrdev_region(first, 1);
		return -1;
	}
	if (device_create(cl, NULL, first, NULL, "ad9850") == NULL) {
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	cdev_init(&c_dev, &fops);
	if (cdev_add(&c_dev, first, 1) == -1) {
		device_destroy(cl, first);
		class_destroy(cl);
		unregister_chrdev_region(first, 1);
		return -1;
	}
	status = class_register(&ad9850_drv);
	if (status < 0) {
		printk(KERN_INFO "Registering Class Failed\n");
	}
	status = gpio_request_one(W_CLK, GPIOF_OUT_INIT_LOW, "W_CLK");

	if (status) {
		printk(KERN_ERR "Unable to request GPIOs W_CLK: %d\n", status);
		return status;
	}
	status = gpio_request_one(FU_UD, GPIOF_OUT_INIT_LOW, "W_CLK");

	if (status) {
		printk(KERN_ERR "Unable to request GPIOs FU_UD: %d\n", status);
		return status;
	}
	status = gpio_request_one(DATA, GPIOF_OUT_INIT_LOW, "W_CLK");

	if (status) {
		printk(KERN_ERR "Unable to request GPIOs DATA: %d\n", status);
		return status;
	}
	status = gpio_request_one(RESET, GPIOF_OUT_INIT_LOW, "W_CLK");

	if (status) {
		printk(KERN_ERR "Unable to request GPIOs RESET: %d\n", status);
		return status;
	}
	return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit ad9850_cleanup(void)
{
	cdev_del(&c_dev);
	device_destroy(cl, first);
	class_destroy(cl);
	class_unregister(&ad9850_drv);
	unregister_chrdev_region(first, 1);
	gpio_free(W_CLK);
	gpio_free(FU_UD);
	gpio_free(DATA);
	gpio_free(RESET);
	printk(KERN_INFO "ad9850: unregistered\n");
}

int gpio_pulse(unsigned int gp) {

	gpio_set_value(gp, HIGH);
	gpio_set_value(gp, LOW);
	return 0;
}

int dds_frequency(unsigned int freq, unsigned char phase) {

	int bytes = 4;
	int tuning_word = freq * (4294967296 / 125000000);

	while (bytes) {

		send_bits(tuning_word & 0xff);
		tuning_word = tuning_word >> 8;
		bytes--;
	}
	send_bits(phase); // 8 bits restantes, 5 para phase, 1 power-down, 3 de testes do fabricante
	gpio_pulse(FU_UD);
	return 0;

}

int send_bits(char data) {

	int bits = 8;

	while (bits) {

		if (data & 1) {
			gpio_set_value( DATA, HIGH);
		} else {
			gpio_set_value( DATA, LOW);
		}
		gpio_pulse(W_CLK);
		data = data >> 1;
		bits--;
	}
	return 0;
}



int spread(unsigned int freq) {
	int range = 500000; // in khz
	int v_range = 0;

	while (1) {

		dds_frequency(freq + v_range, 0);


		udelay(1000);
		if (v_range > range)
			v_range = 0;
		v_range += 80000;
	}

	return 0;
}

module_init( ad9850_init);
module_exit( ad9850_cleanup);
