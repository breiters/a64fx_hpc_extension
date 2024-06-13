#ifndef A64FX_HPC_EXTENSIONS_HEADER_DEFINED
#define A64FX_HPC_EXTENSIONS_HEADER_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h> /* uint64_t */

extern void     a64fx_hpc_hwprefetch_set_default(void);
extern uint64_t a64fx_hpc_hwprefetch_set_distance_l1(uint64_t distance);
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
extern uint64_t a64fx_hpc_sectorcache_set_size_l1(unsigned sector, uint64_t size);
extern uint64_t a64fx_hpc_sectorcache_set_size_l2(unsigned sector, uint64_t size);

extern void *a64fx_hpc_hwprefetch_set_tag(const void *address,
                                          unsigned    disable_pf_l1,
                                          unsigned    disable_pf_l2,
                                          unsigned    strong);
extern void *a64fx_hpc_sectorcache_set_sectorid_tag(const void *address,
                                                    uint64_t    sectorid);

/** TODO: strong / weak prefetch and injection mode */

#ifdef __cplusplus
}
#endif

#endif /* A64FX_HPC_EXTENSIONS_HEADER_DEFINED */
