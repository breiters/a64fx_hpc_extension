# A64FX HPC Extensions Kernel Module and User Library

This repository contains a kernel module which makes the A64FX HPC Extensions setting registers for the sector cache and hardware prefetch assistance accessible in EL0 (user-level).

A user-level shared library providing functionality for usage of the sector cache and hardware prefetch assistance is also part of this repository.

Please see the official Fujitsu documentation for details on those features: https://github.com/fujitsu/A64FX

## Building

```sh
make
```

This builds the kernel module `a64fx_hpc_extension.ko` in `lib/modules` and the user-level library `liba64fx_hpc_extension.so` in `usr/lib64`.

## Usage

First load the kernel module:

```sh
insmod a64fx_hpc_extension
```

Link the library to your application with `-la64fx_hpc_extension` and include the header `a64fx_hpc_extension.h` which is located in `usr/include`. Please see the header file and Fujitsu documentation for details.

## Acronyms

SC: Sector Cache

PF: Prefetch

PFD: Prefetch Distance

HW: Hardware

PE: Processing Element

CMG: Core Memory Group

## List of Registers

This is the list of model-specific registers for the A64FX Fujitsu HPC Extensions.

| Purpose                             | Register Name                      | Register          | Bits | Domain |
| ----------------------------------- | ---------------------------------- | ----------------- | ---- | ------ |
| HPC tag address override control    | IMP_FJ_TAG_ADDRESS_CTRL_EL1        | S3_0_C11_C2_0     | 32   | PE     |
| SC Access control                   | IMP_SCCR_CTRL_EL1                  | S3_0_C11_C8_0     | 64   | PE     |
| SC Allocation and operation control | IMP_SCCR_ASSIGN_EL1                | S3_0_C11_C8_1     | 64   | PE     |
| SC L1D capacity setting             | IMP_SCCR_L1_EL0                    | S3_3_C11_C8_2     | 64   | PE     |
| SC L2 maximum capacity setting      | IMP_SCCR_SET0_L2_EL1               | S3_0_C15_C8_2     | 64   | CMG    |
| SC L2 maximum capacity setting      | IMP_SCCR_SET1_L2_EL1               | S3_0_C15_C8_3     | 64   | CMG    |
| SC L2 capacity setting              | IMP_SCCR_VSCCR_L2_EL0              | S3_3_C15_C8_2     | 64   | PE*    |
| PF assistance control               | IMP_PF_CTRL_EL1                    | S3_0_C11_C4_0     | 64   | PE     |
| HW PF control for PF_STREAM_DETECT  | IMP_PF_STREAM_DETECT_CTRL_EL0      | S3_3_C15_C8_2     | 64   | PE     |
| HW PF control for PF_INJECTION      | IMP_PF_INJECTION_CTRL[0-7]_EL0     | S3_3_C11_C6_[0-7] | 64   | PE     |
| HW PFD setting for PF_INJECTION     | IMP_PF_INJECTION_DISTANCE[0-7]_EL0 | S3_3_C11_C7_[0-7] | 64   | PE     |
