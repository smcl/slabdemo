#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

#define SLABNAME "slabdemo"
#define SLABALIGN 8
#define SLABFLAGS 0

typedef struct
{
  char foo; 
  char bar; 
  char baz; 
} slabthing;

struct kmem_cache_t *slabthing_cache;

slabthing *thing_one;
slabthing *thing_two;
slabthing *thing_three;

int init_module(void)
{
  printk(KERN_INFO "init slabdemo module\n");

  // create the slab cache
  slabthing_cache = kmem_cache_create(SLABNAME, sizeof(slabthing), SLABALIGN, SLABFLAGS, NULL);

  // allocate two objects in our slab
  thing_one = (slabthing *)kmem_cache_alloc(slabthing_cache, SLABFLAGS);
  thing_two = (slabthing *)kmem_cache_alloc(slabthing_cache, SLABFLAGS);
  thing_three = (slabthing *)kmem_cache_alloc(slabthing_cache, SLABFLAGS);

  // dump addresses - they should be next to each other
  printk(KERN_INFO "thing_one:   0x%p\n", thing_one);
  printk(KERN_INFO "thing_two:   0x%p\n", thing_two);
  printk(KERN_INFO "thing_three: 0x%p\n", thing_three);
  
  return 0;
}

void cleanup_module(void)
{
  printk(KERN_INFO "cleanup slabdemo module\n");

  // free our two objects
  kmem_cache_free(slabthing_cache, thing_one);
  kmem_cache_free(slabthing_cache, thing_two);
  kmem_cache_free(slabthing_cache, thing_three);

  // destroy the value
  kmem_cache_destroy(slabthing_cache);
}
