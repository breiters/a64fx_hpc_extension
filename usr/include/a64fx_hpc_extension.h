#ifndef A64FX_HPC_EXTENSIONS_HEADER_DEFINED
#define A64FX_HPC_EXTENSIONS_HEADER_DEFINED

#ifdef __cplusplus
#include <cstdint>
extern "C" {
#else
#include <stdint.h>
#endif

extern void     a64fx_hpc_set_default_hwprefetch(void);
extern uint64_t a64fx_hpc_set_hwprefetch_distance_l1(uint64_t distance);
extern uint64_t a64fx_hpc_set_hwprefetch_distance_l2(uint64_t distance);
extern uint64_t a64fx_hpc_get_hwprefetch_distance_l1(void);
extern uint64_t a64fx_hpc_get_hwprefetch_distance_l2(void);
extern void     a64fx_hpc_enable_hwprefetch_l1(void);
extern void     a64fx_hpc_enable_hwprefetch_l2(void);
extern void     a64fx_hpc_disable_hwprefetch_l1(void);
extern void     a64fx_hpc_disable_hwprefetch_l2(void);

extern uint64_t a64fx_hpc_set_sector_size_l1(unsigned sector, uint64_t size);
extern uint64_t a64fx_hpc_set_sector_size_l2(unsigned sector, uint64_t size);
extern void     a64fx_hpc_default_sector_cache_l1(void);
extern void     a64fx_hpc_default_sector_cache_l2(void);
extern void     a64fx_hpc_default_sector_cache(void);

extern void *a64fx_hpc_set_hwprefetch_tag(void    *address,
                                          unsigned disable_pf_l1,
                                          unsigned disable_pf_l2,
                                          unsigned strong);
extern void *a64fx_hpc_set_sectorid_tag(void *address, uint64_t sectorid);

/** TODO: strong / weak prefetch and injection mode */

#ifdef __cplusplus
}
#endif

#endif /* A64FX_HPC_EXTENSIONS_HEADER_DEFINED */
