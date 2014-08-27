obj-m += ad9850.o
COPS = -Wall -O2  -std=gnu99 -lc -lm -lg -lgcc
PWD := $(shell pwd)
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all:ad9859.ko


	
ad9859.ko:${OBJS}
	$(MAKE) -C $(KERNELDIR)  M=$(PWD) modules

modules_install:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) INSTALL_MOD_PATH=$(sysr) INSTALL_MOD_DIR=$(mdir) modules_install
	

clean:
	$(MAKE)  -C $(KERNELDIR) M=$(PWD) clean