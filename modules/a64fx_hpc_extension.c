/**
 * @file a64fx_hpc_extension.c
 * @author Sergej Breiter (breiter@nm.ifi.lmu.de)
 * @brief Linux kernel module providing user-level access to A64FX Fujitsu HPC Extensions
 * @version 0.1
 * @date 2024-06-10
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <linux/module.h>

/** Read / write ARM model-specific registers **/
#define ARM_READ_MRS_X(reg_val, reg_name)                                                \
    __asm__ volatile("mrs %[" #reg_val "]," #reg_name : [reg_val] "=r"(reg_val) : :);
#define ARM_READ_MRS(reg_val, reg_name) ARM_READ_MRS_X(reg_val, reg_name)

#define ARM_WRITE_MSR_X(reg_val, reg_name)                                               \
    __asm__ volatile("msr " #reg_name ",%[" #reg_val "]" : : [reg_val] "r"(reg_val) :);
#define ARM_WRITE_MSR(reg_val, reg_name) ARM_WRITE_MSR_X(reg_val, reg_name)

#define IMP_FJ_TAG_ADDRESS_CTRL_EL1      S3_0_C11_C2_0
#define IMP_SCCR_CTRL_EL1                S3_0_C11_C8_0
#define IMP_SCCR_ASSIGN_EL1              S3_0_C11_C8_1 /* unused yet */
#define IMP_SCCR_SET0_L2_EL1             S3_0_C15_C8_2 /* unused yet */
#define IMP_SCCR_SET1_L2_EL1             S3_0_C15_C8_3 /* unused yet */
#define IMP_PF_CTRL_EL1                  S3_0_C11_C4_0

// In order to use HPC tag address override function, both Tagged addressing of ARMv8-A
// and HPC tag address override must be enabled for each region. 
// (TBI and TBO bit must be set)
//
// On Linux, TBI for userspace is set by default.
//
// Quote:
// The kernel configures the translation tables so that translations made
// via TTBR0 (i.e. userspace mappings) have the top byte (bits 63:56) of
// the virtual address ignored by the translation hardware. This frees up
// this byte for application use.
//
// Source: https://www.kernel.org/doc/Documentation/arm64/tagged-pointers.txt

static void _enable_a64fx_hpc_extensions(void *args)
{
    u32 val32;
    u64 val64;

    (void)args;

    // enable sector cache control, prefetch assist, top byte override
    val32 = GENMASK(13, 12)  // SCE1, PFE1
            | GENMASK(9, 8)  // SCE0, PFE0
            | GENMASK(1, 0); // TBO0, TBO1

    ARM_WRITE_MSR(val32, IMP_FJ_TAG_ADDRESS_CTRL_EL1);

    // read/write enable from EL0 to:
    // IMP_SCCR_L1_EL0
    // IMP_SCCR_VSCCR_L2_EL0
    val64 = GENMASK_ULL(63, 62); // el0ae, el1ae
    ARM_WRITE_MSR(val64, IMP_SCCR_CTRL_EL1);

    // read/write enable from EL0 to:
    // IMP_PF_STREAM_DETECT_CTRL_EL0
    // IMP_PF_INJECTION_CTRL[0-7]_EL0
    // IMP_PF_INJECTION_DISTANCE[0-7]_EL0
    val64 = GENMASK_ULL(63, 62); // el0ae, el1ae
    ARM_WRITE_MSR(val64, IMP_PF_CTRL_EL1);
}

static void _disable_a64fx_hpc_extensions(void *args)
{
    u32 val32;
    u64 val64;

    (void)args;

    // disable sector cache control, prefetch assist, top byte override
    val32 = 0x0;
    ARM_WRITE_MSR(val32, IMP_FJ_TAG_ADDRESS_CTRL_EL1);

    // read/write disable from EL0 to:
    // IMP_SCCR_L1_EL0
    // IMP_SCCR_VSCCR_L2_EL0
    val64 = 0x0;
    ARM_WRITE_MSR(val64, IMP_SCCR_CTRL_EL1);

    // read/write disable from EL0 to:
    // IMP_PF_STREAM_DETECT_CTRL_EL0
    // IMP_PF_INJECTION_CTRL[0-7]_EL0
    // IMP_PF_INJECTION_DISTANCE[0-7]_EL0
    val64 = 0x0;
    ARM_WRITE_MSR(val64, IMP_PF_CTRL_EL1);
}

static int __init m_init(void)
{
    on_each_cpu(_enable_a64fx_hpc_extensions, NULL, 1);
    printk(KERN_INFO "A64FX Fujitsu HPC Extensions Enabled\n");
    return 0;
}

static void __exit m_exit(void)
{
    on_each_cpu(_disable_a64fx_hpc_extensions, NULL, 1);
    printk(KERN_INFO "A64FX Fujitsu HPC Extensions Disabled\n");
}

module_init(m_init);
module_exit(m_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sergej Breiter");
MODULE_DESCRIPTION(
    "Module controlling user-level access to A64FX Fujitsu HPC Extensions");
MODULE_VERSION("0.1");
