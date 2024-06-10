#include "defs.h"

#include <assert.h>
#include <stdint.h>

// [63:60] pf_func
// When PFE=1:
// the operation of the hardware prefetch assistance is specified.
// Refer to details to the hardware prefetch assistance.
// When PFE=0:
// this field is ignored, and the hardware prefetch assistance operates as Default.
//
// Stream detect mode
//
// bit[2] DIS_L1HWPF0:
// The L1 hardware prefetch is enabled.
// 1: The L1 hardware prefetch is disabled
// However, when
// IMP_PF_STREAM_DETECT_CTRL_EL0.L1PF_DIS
// = 1, the L1 hardware prefetch is disabled regardless
// of this bit.
// Also, this bit is ignored in the Prefetch instruction.
//
// bit[1] DIS_L2HWPF0:
// The L2 hardware prefetch is enabled.
// 1: The L2 hardware prefetch is disabled
// However, when
// IMP_PF_STREAM_DETECT_CTRL_EL0.L2PF_DIS
// = 1, the L2 hardware prefetch is disabled regardless
// of this bit.
// Also, this bit is ignored in the Prefetch instruction.
//
// bit[0] SWPF_STRONG0:
// The Prefetch instruction is generated with Strong
// prefetch hint.
// 1: The Prefetch instruction is generated with Weak
// prefetch hint.
// This bit is ignored except for the Prefetch
// instruction.

void *a64fx_hpc_set_hwprefetch_tag(void    *address,
                                   unsigned disable_pf_l1,
                                   unsigned disable_pf_l2,
                                   unsigned strong)
{
    uintptr_t tagged_address = (uintptr_t)address;

    if (strong)
        tagged_address |= BIT_ULL(60);
    if (disable_pf_l2)
        tagged_address |= BIT_ULL(61);
    if (disable_pf_l1)
        tagged_address |= BIT_ULL(62);

    /** TODO: better implementation w/o conditionals */
    return (void *)tagged_address;
}

// [57:56] sector_id
// When SCE=1:
// sector ID of the sector cache is specified.
// Refer to details to the sector cache.
// When SCE=0:
// this field is ignored, and sector ID operates as Default.

void *a64fx_hpc_set_sectorid_tag(void *address, uint64_t sectorid)
{
    assert(sectorid < 4);
    uintptr_t tagged_address = (uintptr_t)address;
    tagged_address |= sectorid << 56;
    return (void *)tagged_address;
}
