#ifndef BOOT_INCLUDE_COMP_ATTR_H_
#define BOOT_INCLUDE_COMP_ATTR_H_

// Do it yourself file
#define COMP_ATTR__USED__       __attribute__((__used__))
#define COMP_ATTR__ALIGNED__(n) __attribute__((aligned(n)))
#define COMP_ATTR__PACKED__     __attribute__((packed))
#define COMP_ATTR__SECTION__(s) __attribute__((section(s)))
#define COMP_ATTR__NORETURN__   __attribute__((noreturn))
#define COMP_ATTR__WEAK__       __attribute__((weak))

#endif