# slabdemo

A quick demonstration of how the linux kernel's slab allocator works. This creates a kernel module which initialises a kernel cache and allocates a handful of objects on the heap when it's loaded, then frees the objects and destroys the cache when it's unloaded.

This is to support a little [blog post I wrote])http://blog.mclemon.io/discover-a-linux-utility-slabtop) to explore the ```slabtop``` utility.
