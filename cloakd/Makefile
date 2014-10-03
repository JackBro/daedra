ifneq ($(KERNELRELEASE),)
	obj-m := c1oakd.o # <---- Mind the `1' (the `one', not the character `el') in the name of the module
	c1oakd-y := crypto.o cloakd.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

endif
