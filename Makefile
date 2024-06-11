all: a64fx_hpc_extension_kmod a64fx_hpc_extension_userlib

KMOD_DIR    := modules
USERLIB_DIR := lib
EXAMPLE_DIR := examples

a64fx_hpc_extension_kmod:
	make -C $(KMOD_DIR)

a64fx_hpc_extension_userlib:
	make -C $(USERLIB_DIR)

example:
	make -C $(EXAMPLE_DIR)

install_kmod: a64fx_hpc_extension_kmod
	make -C $(KMOD_DIR)    modules_install

install_userlib: a64fx_hpc_extension_userlib
	make -C $(USERLIB_DIR) install

install: install_kmod install_userlib

.PHONY: clean help

clean:
	make -C $(KMOD_DIR)    clean
	make -C $(USERLIB_DIR) clean
	make -C $(EXAMPLE_DIR) clean

help:
	make -C $(KMOD_DIR)    help
	make -C $(USERLIB_DIR) help
