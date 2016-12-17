### aligned_vector
An STL-like vector implementation which internally aligns the array to a desired number of bytes. Intended for e.g. SIMD purposes.

### Introduction
The common STL std::vector is a great container for automatic memory management, but it does not provide the option of allocating aligned memory (the starting address of the allocated memory block to be divisible by a given constant, usually the sizeof() a primitive data type, e.g. 8 bytes for int64_t).  

Aligning memory is critical in some applications, such as SIMD vectorization.  
For instance, to most efficiently load the SIMD registers in SSE, the data needs to be aligned to 16 byte addresses.

This class provides similar capabilities to std::vector, but it ensures that data are aligned to a desired number of bytes in the memory.

### Description

```is::aligned_vector``` is a template class requiring two template arguments:  
1. ```T``` - object class type  
2. ```A``` - alignment size in number of bytes  

```is::aligned_vector``` allocates a contiguous array on the heap (similar to std::vector) but allocates slightly more memory than is absolutely necessary for an array of arbitrary placement.  
This is done in order to ensure alignment.  
```std::align``` is to obtain the first memory address for a particular alignment size:  

```is::aligned_vector``` automatically handles memory allocation and destructs the correct address of the entire raw chunk of memory, while only exposing the aligned part to the user.  

### Features  
```is::aligned_vector``` attempts to be as much compatible to the ```std::vector``` as possible. This includes functioning members:  

- push_back()
- emplace_back() - currently the same as push_back
- operator[]
- at()
- data()
- clear()
- reserve()
- resize()
- size()
- empty()


### ToDo  
1. **The class currently does not provide an implementation of iterators. This is needed to ensure complete STL compatibility.**  
2. Implement a more efficient ```emplace_back()```.  



### Usage
```  
#include <iostream>
#include "aligned_vector.hpp"  

int main() {  
  // The definition is in the namespace "is".  
  is::aligned_vector<int16_t, 16> v;  

  // push_back works like in std::vector.
  for (int32_t i=0; i<20; i++) {  
    v.push_back(i);  
  }  

  // operator[] access works like in std::vector.  
  for (int32_t i=0; i<v.size(); i++) {  
    std::cout << v[i] << std::endl;  
  }  

  // Clearing the vector works like in std::vector.  
  v.clear();  

  // aligned_vector can be resized like std::vector.  
  v.resize(37);  

  // You can reserve memory without resizing the vector as well.  
  v.reserve(1000);  

  return 0;  
}
```  
