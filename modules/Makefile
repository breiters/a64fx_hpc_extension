obj-m += a64fx_hpc_extension.o

PWD := $(CURDIR)

all: modules

modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

modules_install: modules
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

help:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) help
