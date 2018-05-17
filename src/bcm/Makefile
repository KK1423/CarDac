PWD := $(shell pwd)

ORIGDIR = sound/soc/bcm
INSTALLDIR = cardac
MODULENAME = snd-soc-cardac.ko

snd-soc-cardac-objs := cardac.o
obj-m += snd-soc-cardac.o

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS_cardac.o := -DDEBUG
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
