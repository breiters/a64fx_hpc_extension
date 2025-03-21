#ifndef A64FX_HPC_EXTENSIONS_HEADER_DEFINED
#define A64FX_HPC_EXTENSIONS_HEADER_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h> /* uint64_t */

extern void     a64fx_hpc_hwprefetch_set_default(void);
extern uint64_t a64fx_hpc_hwprefetch_set_control_enabled(void);
extern uint64_t a64fx_hpc_hwprefetch_set_control_disabled(void);

/**
 * @brief Sets the L1D cache hardware prefetch distance.
 * 
 * The prefetch distance for L1 is calculated as (L1_DIST * 256B).
 * When L1_DIST = 0, the hardware prefetch for L1 operates by the default distance.
 * Max. L1_DIST is 7 (= 1792B).
 * 
 * @param distance 
 * @return The old value of register IMP_PF_STREAM_DETECT_CTRL_EL0 
 */
extern uint64_t a64fx_hpc_hwprefetch_set_distance_l1(uint64_t distance);

/**
 * @brief Sets the L2 cache hardware prefetch distance.
 * 
 * The prefetch distance for L1 is calculated as (L2_DIST * 1KiB).
 * When L2_DIST = 0, the hardware prefetch for L1 operates by the default distance.
 * Max. L2_DIST is 7 (= 7KiB).
 * 
 * @param distance 
 * @return The old value of register IMP_PF_STREAM_DETECT_CTRL_EL0
 */
extern uint64_t a64fx_hpc_hwprefetch_set_distance_l2(uint64_t distance);

extern uint64_t a64fx_hpc_hwprefetch_get_distance_l1(void);
extern uint64_t a64fx_hpc_hwprefetch_get_distance_l2(void);
extern void     a64fx_hpc_hwprefetch_set_enabled_l1(void);
extern void     a64fx_hpc_hwprefetch_set_enabled_l2(void);
extern void     a64fx_hpc_hwprefetch_set_disabled_l1(void);
extern void     a64fx_hpc_hwprefetch_set_disabled_l2(void);

extern void     a64fx_hpc_sectorcache_set_default(void);
extern void     a64fx_hpc_sectorcache_set_default_l1(void);
extern void     a64fx_hpc_sectorcache_set_default_l2(void);
extern uint64_t a64fx_hpc_sectorcache_set_size_l1(uint64_t sector, uint64_t size);
extern uint64_t a64fx_hpc_sectorcache_set_size_l2(uint64_t sector, uint64_t size);

extern void *a64fx_hpc_hwprefetch_set_tag(const void *address,
                                          uint64_t    disable_pf_l1,
                                          uint64_t    disable_pf_l2,
                                          uint64_t    strong);
extern void *a64fx_hpc_sectorcache_set_sectorid_tag(const void *address,
                                                    uint64_t    sectorid);

/** TODO: strong / weak prefetch and injection mode */

#ifdef __cplusplus
}
#endif

#endif /* A64FX_HPC_EXTENSIONS_HEADER_DEFINED */
