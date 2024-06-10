all: a64fx_hpc_extension_kmod a64fx_hpc_extension_userlib

a64fx_hpc_extension_kmod:
	make -C lib/modules

a64fx_hpc_extension_userlib:
	make -C usr/lib64
