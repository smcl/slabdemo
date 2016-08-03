#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>

// specify info about our slab cache should be setup
#define SLABNAME "slabdemo"
#define SLABALIGN 8
#define SLABFLAGS 0

// just some module-specific stuff
#define NUMOBJECTS 128

typedef struct slabthing_struct
{
  char foo; 
  char bar; 
  char baz;
  struct slabthing_struct *next;
} slabthing;

struct kmem_cache *slabthing_cache;

slabthing *head;

int init_module(void)
{
  int i;
  slabthing *s;
  slabthing *sprev;

  printk(KERN_INFO "init slabdemo module\n");

  // create the slab cache
  slabthing_cache = kmem_cache_create(SLABNAME, sizeof(slabthing), SLABALIGN, SLABFLAGS, NULL);

  // allocate two objects in our slab
  for (i = 0; i < NUMOBJECTS; i++) {
    s = (slabthing *)kmem_cache_alloc(slabthing_cache, SLABFLAGS);
    s->next = NULL;
    if (i == 0) {
      head = s;
      sprev = s;
    } else {
      sprev->next = s;
      sprev = s;
    }
  }
    
  // dump addresses - they should be next to each other
  s = head;
  while(s) {
    printk(KERN_INFO "allocated slabthing: 0x%p\n", s);
    s = s->next;
  }
    
  return 0;
}

void cleanup_module(void)
{
  slabthing *s = head;

  printk(KERN_INFO "cleanup slabdemo module\n");

  // free our two objects
  while(s) {
    printk(KERN_INFO "freed slabthing: 0x%p\n", s);
    kmem_cache_free(slabthing_cache, s);
    s = s->next;
  }
  
  // destroy the value
  kmem_cache_destroy(slabthing_cache);
}
