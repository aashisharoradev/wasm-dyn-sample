#include<iostream>
#include<dlfcn.h>
#include<emscripten.h>
#include<emscripten/bind.h>

using namespace std;

typedef double (*cube_function)(int);

double call_dynamic(int number) {
    const char* error;
    void *handle = dlopen("/assets/cuberoot.wasm", RTLD_NOW);  // 
    if(!handle) {
        cout << "Failed to load webassembly" << dlerror() << endl;
        return 0;
    }
    dlerror();
    
    cube_function cube = (cube_function)dlsym(handle, "cuberoot");

    if((error = dlerror())) {
         cout << "Failed to load symbol" << error << endl;
         dlclose(handle);
        return 0; 
    }
    
    double data =  cube(number);
    
    dlclose(handle);
    return data;
}

EMSCRIPTEN_BINDINGS(dynamic_module) {
    emscripten::function("test_dynamic", &call_dynamic);
}
