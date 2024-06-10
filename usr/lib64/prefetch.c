#include "defs.h"

#include <assert.h>
#include <stdint.h>

#define IMP_PF_STREAM_DETECT_CTRL_EL0 S3_3_C11_C4_0

// IMP_PF_STREAM_DETECT_CTRL_EL0: S3_3_C11_C4_0
//
// [63] V RW
// 1: A value of IMP_PF_STREAM_DETECT_CTRL_EL0 is valid
// 0: It operates by a set value of Default.
//
// [59] L1PF_DISRW
// The hardware prefetch to L1 cache is disabled. When set, the
// value of pf_func[2] is ignored in stream detect mode.
// 0: Enable (Default)
// 1: Disable
//
// [58] L2PF_DISRW
// The hardware prefetch to L2 cache is disabled. When invalidly set,
// the value of pf_func[1] is ignored in stream detect mode.
// 0: Enable (Default)
// 1: Disable
//
// [27:24] L1_DISTRW
// The distance of the hardware prefetch to L1 cache is specified.
// The prefetch distance for L1 is calculated as (L1_DIST * 256B).
// When L1_DIST = 0, the hardware prefetch for L1 operates by the
// default distance.
//
// [19:16] L2_DISTRW
// The distance of the hardware prefetch to L2 cache is specified.
// The prefetch distance for L2 is calculated as (L2_DIST * 1KB).
// When L2_DIST = 0, the hardware prefetch for L2 operates by the
// default distance.

void a64fx_hpc_set_default_hwprefetch(void)
{
    uint64_t val = 0x0;
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
}

uint64_t a64fx_hpc_set_hwprefetch_distance_l1(uint64_t distance)
{
    assert(distance < 16);
    uint64_t val_old;
    ARM_READ_MRS(val_old, IMP_PF_STREAM_DETECT_CTRL_EL0);
    uint64_t val  = val_old;
    uint64_t mask = ~GENMASK_ULL(27, 24);
    val           = val & mask;
    val           = val | (distance << 24) | (1ULL << 63);
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    return val_old;
}

uint64_t a64fx_hpc_set_hwprefetch_distance_l2(uint64_t distance)
{
    assert(distance < 16);
    uint64_t val_old;
    ARM_READ_MRS(val_old, IMP_PF_STREAM_DETECT_CTRL_EL0);
    uint64_t val  = val_old;
    uint64_t mask = ~GENMASK_ULL(19, 16);
    val           = val & mask;
    val           = val | (distance << 16) | (1ULL << 63);
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    return val_old;
}

uint64_t a64fx_hpc_get_hwprefetch_distance_l1(void)
{
    uint64_t val;
    ARM_READ_MRS(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    return (val & GENMASK_ULL(27, 24)) >> 24;
}

uint64_t a64fx_hpc_get_hwprefetch_distance_l2(void)
{
    uint64_t val;
    ARM_READ_MRS(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    return (val & GENMASK_ULL(19, 16)) >> 16;
}

void a64fx_hpc_enable_hwprefetch_l1(void)
{
    uint64_t val;
    ARM_READ_MRS(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    val &= ~BIT_ULL(59);
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
}

void a64fx_hpc_enable_hwprefetch_l2(void)
{
    uint64_t val;
    ARM_READ_MRS(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    val &= ~BIT_ULL(58);
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
}

void a64fx_hpc_disable_hwprefetch_l1(void)
{
    uint64_t val;
    ARM_READ_MRS(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    val |= BIT_ULL(59);
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
}

void a64fx_hpc_disable_hwprefetch_l2(void)
{
    uint64_t val;
    ARM_READ_MRS(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
    val |= BIT_ULL(58);
    ARM_WRITE_MSR(val, IMP_PF_STREAM_DETECT_CTRL_EL0);
}

/** TODO: strong / weak prefetch and injection mode */
