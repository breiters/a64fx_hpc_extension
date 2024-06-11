#include "a64fx_hpc_extension.h"
#include "defs.h"

#include <assert.h>
#include <stdint.h>

#define IMP_SCCR_L1_EL0       S3_3_C11_C8_2
#define IMP_SCCR_VSCCR_L2_EL0 S3_3_C15_C8_2

// IMP_SCCR_L1_EL0 : S3_3_C11_C8_2
//
// [14:12] l1_sec3_max
// The number of L1 Sector ID=3 of maximum sectors is set.
//
// [10:8] l1_sec2_max
// The number of L1 Sector ID=2 of maximum sectors is set.
//
// [6:4] l1_sec1_max
// The number of L1 Sector ID=1 of maximum sectors is set.
//
// [2:0] l1_sec0_max
// The number of L1 Sector ID=0 of maximum sectors is set.

uint64_t a64fx_hpc_sectorcache_set_size_l1(unsigned sector, uint64_t size)
{
    assert(size < 5);
    assert(sector < 4);

    uint64_t val_old;
    ARM_READ_MRS(val_old, IMP_SCCR_L1_EL0);

    uint64_t val = val_old;
    switch (sector) {
    case 0:
        val &= ~GENMASK_ULL(2, 0);
        val |= size << 0;
        break;
    case 1:
        val &= ~GENMASK_ULL(6, 4);
        val |= size << 4;
        break;
    case 2:
        val &= ~GENMASK_ULL(10, 8);
        val |= size << 8;
        break;
    case 3:
        val &= ~GENMASK_ULL(14, 12);
        val |= size << 12;
        break;
    default:
        assert(0);
    }

    ARM_WRITE_MSR(val, IMP_SCCR_L1_EL0);
    return val_old;
}

// IMP_SCCR_VSCCR_L2_EL0 : S3_3_C15_C8_2
//
// [12:8] l2_sec1_max
// The number of L2 Sector ID=1 of maximum sectors is set.
//
// [4:0] l2_sec0_max
// The number of L2 Sector ID=0 of maximum sectors is set.
//
// note: we only use l2 sector set0 
// because selecting sector set1 (sector 2/3) requires EL1

uint64_t a64fx_hpc_sectorcache_set_size_l2(unsigned sector, uint64_t size)
{
    assert(size < 17);
    assert(sector < 2);

    uint64_t val_old;
    ARM_READ_MRS(val_old, IMP_SCCR_VSCCR_L2_EL0);

    uint64_t val = val_old;
    switch (sector) {
    case 0:
        val &= ~GENMASK_ULL(4, 0);
        val |= size << 0;
        break;
    case 1:
        val &= ~GENMASK_ULL(12, 8);
        val |= size << 8;
        break;
    // case 2:
    // case 3:
    default:
        assert(0);
        break;
    }

    ARM_WRITE_MSR(val, IMP_SCCR_VSCCR_L2_EL0);
    return val_old;
}

void a64fx_hpc_sectorcache_set_default_l1(void)
{
    a64fx_hpc_sectorcache_set_size_l1(0, 4);
    a64fx_hpc_sectorcache_set_size_l1(1, 0);
    a64fx_hpc_sectorcache_set_size_l1(2, 0);
    a64fx_hpc_sectorcache_set_size_l1(3, 0);
}

void a64fx_hpc_sectorcache_set_default_l2(void)
{
    a64fx_hpc_sectorcache_set_size_l2(0, 16);
    a64fx_hpc_sectorcache_set_size_l2(1, 0);
}

void a64fx_hpc_sectorcache_set_default(void)
{
    a64fx_hpc_sectorcache_set_default_l1();
    a64fx_hpc_sectorcache_set_default_l2();
}
