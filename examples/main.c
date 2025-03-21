#include "a64fx_hpc_extension.h"

#include <inttypes.h>
#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    printf("========================================================\n");
    printf("Setting prefetch distance on L1 to 1 and on L2 to 2 ...\n");
    printf("========================================================\n");

#pragma omp parallel
    {
        /* Enable the hardware prefetch control on each core */
        a64fx_hpc_hwprefetch_set_control_enabled();
    }
    
#pragma omp parallel
    {
        /* L1 and L2 setting is per PE */
        a64fx_hpc_hwprefetch_set_distance_l1(1);
        a64fx_hpc_hwprefetch_set_distance_l2(2);
    }

    printf("========================================================\n");
    printf("Reading L1 prefetch distance ...\n");
    printf("========================================================\n");

#pragma omp parallel
    {
        uint64_t val_l1 = a64fx_hpc_hwprefetch_get_distance_l1();
        printf("[tid=%2d] hardware prefetch distance L1: %" PRIu64 "\n",
               omp_get_thread_num(),
               val_l1);
    }

    printf("========================================================\n");
    printf("Reading L2 prefetch distance ...\n");
    printf("========================================================\n");

#pragma omp parallel
    {
        uint64_t val_l2 = a64fx_hpc_hwprefetch_get_distance_l2();
        printf("[tid=%2d] hardware prefetch distance L2: %" PRIu64 "\n",
               omp_get_thread_num(),
               val_l2);
    }

    printf("========================================================\n");
    printf("Restoring default distances ...\n");
    printf("========================================================\n");

#pragma omp parallel
    {
        /* Disabling the hardware prefetch control on each core */
        /* Also done in 'a64fx_hpc_hwprefetch_set_default' */
        // a64fx_hpc_hwprefetch_set_control_disabled();

        /* Set default values on each core */
        a64fx_hpc_hwprefetch_set_default();
    }
}
