#ifndef INCLUDE_COMP_ATTR_H_
#define INCLUDE_COMP_ATTR_H_

// Do it yourself file
#define INCLUDE_COMP_ATTR_NORETURN __attribute__((noreturn))
#define INCLUDE_COMP_ATTR_USED __attribute__((__used__))
#define INCLUDE_COMP_ATTR_ALIGNED(n) __attribute__((aligned(n)))
#define INCLUDE_COMP_ATTR_PACKED __attribute__((packed))
#define INCLUDE_COMP_ATTR_SECTION(s) __attribute__((section(s)))
#define INCLUDE_COMP_ATTR_NORETURN __attribute__((noreturn))

#endif