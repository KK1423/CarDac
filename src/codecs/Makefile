PWD := $(shell pwd)

ORIGDIR = sound/soc/codecs
INSTALLDIR = cardac
MODULENAME = snd-soc-tas6424.ko

snd-soc-tas6424-objs := tas6424.o
obj-m += snd-soc-tas6424.o

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS_tas6424.o := -DDEBUG
endif

all:
	$(MAKE) -C $(KERNELDIR)/build M=$(PWD) modules

install: all
	$(MAKE) INSTALL_MOD_DIR=$(INSTALLDIR) \
		-C $(KERNELDIR)/build M=$(PWD) modules_install
		@depmod -a $(kernelver)

release: all
	@install -m 644 -vD -t $(RELEASEDIR)/kernel/$(ORIGDIR) $(MODULENAME)

clean:
	$(MAKE) -C $(KERNELDIR)/build M=$(PWD) clean

.PHONY: uninstall
uninstall:
	@rm -f $(KERNELDIR)/$(INSTALLDIR)/$(MODULENAME)
	@depmod -a $(kernelver)
