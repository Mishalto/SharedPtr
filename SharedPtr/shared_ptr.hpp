template <typename T>
class SharedPtr {
private:
    T* resource_;
    size_t* refs_;

public:
    // default constructor
    SharedPtr();

    // parameter constructor
    SharedPtr(const T& resource);

    // copy constructor
    SharedPtr(const SharedPtr& other);

    // destructor
    ~SharedPtr();

    // copy assigment
    SharedPtr<T>& operator=(const SharedPtr<T>& other);

    // overload operator*
    T& operator*();

    // get resource address
    T* get();

    // get refs count
    size_t use_refs();
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

// copy constructor
template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) {
    if (other.resource_ == nullptr) {
        resource_ = nullptr;
        refs_ = nullptr;
    } else {
        resource_ = other.resource_;
        refs_ = other.refs_;
        *refs_ += 1;
    }
}

// destructor
// maybe need resource_ == nullptr && refs_ == nullptr
// since memory is allocated and deleted synchronously
// but mb its only debug
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

// get resource address
template <typename T>
T* SharedPtr<T>::get() {
    return resource_;
}

// operator* overloaded
template <typename T>
T& SharedPtr<T>::operator*() {
    if (resource_ == nullptr) {
        throw std::logic_error("Dereference nullptr");
    }

    return *resource_;
}

// copy assigment
template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if (this == &other) { return *this; }

    if (resource_ != nullptr) {
        *refs_ -= 1;
        if (*refs_ == 0) {
            delete resource_;
            delete refs_;
        }
    }

    resource_ = other.resource_;
    refs_ = other.refs_;
    *refs_ += 1;

    return *this;
}

// get count refs
template <typename T>
size_t SharedPtr<T>::use_refs() {
    if (refs_ == nullptr) {
        return 0;
    }

    return *refs_;
}