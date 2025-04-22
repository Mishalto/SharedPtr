# shared_ptr

This is my own implementation of a template-based std::shared_ptr, without using `std`.  

## Features & Tools Used

- **Valgrind**: No memory leaks.
```bash
HEAP SUMMARY:
in use at exit: 0 bytes in 0 blocks
heap usage: 20,311 allocs, 20,311 frees, 767,643 bytes allocated

All heap blocks were freed -- no leaks are possible

For lists of detected and suppressed errors, rerun with: -s
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

- **Google Test**: The entire basic interface is covered with unit tests.
```cpp
TEST(MyShared, default_constructor) {
    SharedPtr<int> ptr;
    ASSERT_THROW(*ptr, std::logic_error);
}
```

## Interface

- `SharedPtr()` — default constructor    
- `SharedPtr(const T& resource)` — constructor with object  
- `SharedPtr(const SharedPtr& other)` — copy constructor  
- `~SharedPtr()` — destructor, delete resource  
- `SharedPtr<T>& operator=(const SharedPtr<T>& other);` — copy assigment  
- `T& operator*()` — return valid resource  
- `T* get()` — get resource address
- `size_t use_refs()` — get refs count

## Notes

Move constructor is not implemented, and its explicit deletion is not possible.

## Example Usage

```cpp
SharedPtr<int> ptr(1);
std::cout << *ptr << '\n;  // Output: 1;
```
## Build and Run

To build and run the project, follow these steps:

1. **Requirements:**:  
   - **VS Code**  
   - **CMake (last stable release)**  
   - **Git**

2. **Clone the Repository**:

3. **Open folder with VSCode and start build**

4. **In build folder**
```bash
./shared_ptr
```
