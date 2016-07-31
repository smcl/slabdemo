#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#define SLABNAME "slabdemo"
#define SLABALIGN 8
#define SLABFLAGS 0

typedef struct
{
  int foo;
  int bar;
} slabthing;

struct kmem_cache_t *mySlab;

int init_module(void)
{
  printk(KERN_INFO "init slabdemo module\n");

  mySlab = kmem_cache_create(SLABNAME, sizeof(slabthing), SLABALIGN, SLABFLAGS, NULL);
  
  return 0;
}

void cleanup_module(void)
{
  printk(KERN_INFO "cleanup slabdemo module\n");

  kmem_cache_destroy(mySlab);
}
