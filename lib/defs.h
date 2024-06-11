#include <stddef.h> /* size_t */

/** Bit mask stuff **/
static const size_t BITS_PER_LONG      = 8 * sizeof(long);
static const size_t BITS_PER_LONG_LONG = 8 * sizeof(long long);

#define UL(x)      x##UL
#define ULL(x)     x##ULL

#define BIT(x)     (UL(1) << (x))
#define BIT_ULL(x) (ULL(1) << (x))

#define GENMASK(h, l)                                                                    \
    (((~UL(0)) - (UL(1) << (l)) + 1) & (~UL(0) >> (BITS_PER_LONG - 1 - (h))))

#define GENMASK_ULL(h, l)                                                                \
    (((~ULL(0)) - (ULL(1) << (l)) + 1) & (~ULL(0) >> (BITS_PER_LONG_LONG - 1 - (h))))

#define PRINT_BITS(x)                                                                    \
    do {                                                                                 \
        typeof(x) a__     = (x);                                                         \
        char     *p__     = (char *)&a__ + sizeof(x) - 1;                                \
        size_t    bytes__ = sizeof(x);                                                   \
        printf(#x ": ");                                                                 \
        while (bytes__--) {                                                              \
            char bits__ = 8;                                                             \
            while (bits__--)                                                             \
                putchar(*p__ & (1ULL << bits__) ? '1' : '0');                            \
            p__--;                                                                       \
        }                                                                                \
        putchar('\n');                                                                   \
    } while (0)

/** Read / write ARM model-specific registers **/
#define ARM_READ_MRS_X(reg_val, reg_name)                                                \
    __asm__ volatile("mrs %[" #reg_val "]," #reg_name : [reg_val] "=r"(reg_val) : :);
#define ARM_READ_MRS(reg_val, reg_name) ARM_READ_MRS_X(reg_val, reg_name)

#define ARM_WRITE_MSR_X(reg_val, reg_name)                                               \
    __asm__ volatile("msr " #reg_name ",%[" #reg_val "]" : : [reg_val] "r"(reg_val) :);
#define ARM_WRITE_MSR(reg_val, reg_name) ARM_WRITE_MSR_X(reg_val, reg_name)
