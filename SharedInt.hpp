template <typename T>
class SharedPtr {
private:
    size_t* counter_ = nullptr;
    T* obj_ = nullptr;
    std::string name_;

    void print_counter() const {
        if (counter_) {
            std::cout << name_ << ": &" << *counter_ << '\n';
        } else {
            std::cout << name_ << ": &0" << '\n';
        }
    }

public:
    // Default
    SharedPtr(std::string_view name) : name_(name) {
        std::cout << name_ << " -> Default constructor.\n";
        print_counter();
    };

    // With parameters
    SharedPtr(std::string_view name, T obj) : name_(name) {
        obj_ = new T(obj);
        counter_ = new size_t(1);
        std::cout << name_ << "-> constructor with parameters.\n";
        print_counter();
    }

    // Destructor
    ~SharedPtr() {
        if (counter_) {
            --(*counter_);
            if (*counter_ == 0) {
                delete obj_;
                delete counter_;
                std::cout << name_ << " -> destructed.\n";
            }
        }
    }

    // Copy
    SharedPtr(const SharedPtr& other) : counter_(other.counter_), obj_(other.obj_), name_(other.name_) {
        if (counter_) {
            ++(*counter_);
        }
        std::cout << name_ << "-> copy constructor.\n";
        print_counter();
    }

    // Move
    SharedPtr(SharedPtr&& other) : counter_(other.counter_), obj_(other.obj_), name_(other.name_) {
        other.obj_ = nullptr;
        other.counter_ = nullptr;
        std::cout << name_ << " -> move constructor.\n";
        print_counter();
    }

    SharedPtr& operator=(const SharedPtr& other) {
        std::cout << name_ << " copy assignment operator\n";
        if (this != &other) {
            if (counter_) {
                --(*counter_);
                if (*counter_ == 0) {
                    delete obj_;
                    delete counter_;
                }
            }
            obj_ = other.obj_;
            counter_ = other.counter_;
            name_ = other.name_;
            if (counter_) {
                ++(*counter_);
            }
        }
        return *this;
    }

    T& operator*() {
        return *obj_;
    }
};