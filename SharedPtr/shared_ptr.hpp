template <typename T>
class SharedPtr {
private:
    T* resource_;
    size_t* refs_;

public:
    // constructors
    // default
    SharedPtr();
    // parameter constructor
    SharedPtr(const T& resource);
    // destructor
    ~SharedPtr();

    // overload operator*
    T& operator*();

    // get resource address
    T* get();
};

// default constructor
template <typename T>
SharedPtr<T>::SharedPtr()
    : resource_(nullptr), refs_(nullptr) {}

// constructor with parameter
template <typename T>
SharedPtr<T>::SharedPtr(const T& resource) {
    resource_ = new T(resource);
    refs_ = new size_t(1);
}

// destructor
// maybe need resource_ == nullptr && refs_ == nullptr
// since memory is allocated and deleted synchronously
// but mb its for debug only
template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (resource_ == nullptr) {
        return;
    } else {
        *refs_ -= 1;
    }

    if (*refs_ == 0) {
        delete resource_;
        delete refs_;

        resource_ = nullptr;
        refs_ = nullptr;
    }
}

// operator* overloaded
template <typename T>
T& SharedPtr<T>::operator*() {
    if (resource_ == nullptr) {
        throw std::logic_error("Dereference nullptr");
    }

    return *resource_;
}

template <typename T>
T* SharedPtr<T>::get() {
    return resource_;
}