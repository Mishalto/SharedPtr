template <typename T>
class SharedPtr {
private:
    size_t counter_ = 0;
    T* obj_ = nullptr;
    std::string name_;

    void print_counter() const {
        if (counter_) {
            std::cout << name_ << ": &" << counter_ << '\n';
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
        counter_ = 1;
        std::cout << name_ << "-> constructor with parameters.\n";
        print_counter();
    }

    // Destructor
    ~SharedPtr() {
        if (counter_ > 0) {
            --counter_;
            std::cout << name_ << " -> is alive, " << counter_ + 1 << " -> " << counter_  << '\n';
            print_counter();
        } else {
            delete obj_;
            std::cout << name_ << " destructed.\n";
        }
    }

    // Copy
    SharedPtr(const SharedPtr& other) : counter_(other.counter_), obj_(other.obj_), name_(other.name_) {
        ++counter_;
        print_counter();
        std::cout << name_ << "-> copy constructor.\n";
    }

    // Move
    SharedPtr(SharedPtr&& other) : counter_(other.counter_), obj_(other.obj_), name_(other.name_) {
        other.obj_ = nullptr;
        other.counter_ = 0;

        std::cout << name_ << " -> move constructor.\n";
        print_counter();
    }

    T& operator*() {
        return *obj_;
    }
};