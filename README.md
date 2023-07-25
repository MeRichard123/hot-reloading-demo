# Hot Reloading Demo

- Shared Libraries or DLL in Windows exist to dynamically reload code.
- Modern operating systems rely on this a lot.
- You don’t need a fancy virtual machine to hot-reload.
- Code is stored in memory so you can load new code into memory and jump execution there.

1. First you need a module so a header file in C.
2. This header will define the types for each function or varaible which needs to be hot reloaded.
3. You also need an implementation file.

Now let’s make it dynamically linked:

> NOTE: MacOS uses .dylib Linux uses .so and Windows uses .dll

```bash
clang -o ./build/lib.dylib -fPIC -shared ./lib.c
```
The `-fPIC` generates position independent code which means it uses it’s own relative addresses in memory to jump. The `-shared` will generate the SO file (Unix specific)

> Our goal is to detach the library completely so we can use it dynamically. And load all the symbols at run time.

To do what we use `void* dlopen(const char filename, int flags)` which takes the path to the SO file and return the handle of the library. you can then feed the handle into `void* dlsym(void *handle, const char *symbol)` if you know the name of a symbol lets say the name of a function it will find that symbol in the dynamic library, you can cast the returned pointer to the signature of the function and call it. 

To hot reload you call `dlclose` and then reopen it to reload the symbols.

You have to pick a required flag: (for when you have loads of dependencies)

- RTLD_LAZY: lazy bindings
- RTLD_NOW: instant bindings
