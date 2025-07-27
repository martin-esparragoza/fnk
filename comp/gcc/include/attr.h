/**
 * @brief Compiler-specific attributes
 * Another do-it-yourself file. Its expected that
 * - COMP_ATTR__USED__
 * - COMP_ATTR__ALIGNED__(n)
 * - COMP_ATTR__PACKED__
 * - COMP_ATTR__SECTION__(s)
 * - COMP_ATTR__NORETURN__
 * - COMP_ATTR__WEAK__
 * all be defined
 */

#ifndef COMP_INCLUDE_ATTR_H_
#define COMP_INCLUDE_ATTR_H_

// Do it yourself file
#define COMP_ATTR__USED__       __attribute__((__used__))
#define COMP_ATTR__ALIGNED__(n) __attribute__((aligned(n)))
#define COMP_ATTR__PACKED__     __attribute__((packed))
#define COMP_ATTR__SECTION__(s) __attribute__((section(s)))
#define COMP_ATTR__NORETURN__   __attribute__((noreturn))
#define COMP_ATTR__WEAK__       __attribute__((weak))

#endif