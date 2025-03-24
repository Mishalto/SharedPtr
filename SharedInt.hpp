template <typename T>
class SharedPtr {
   private:

    size_t counter_;
    T* obj_;

    std::string name_;
    void print_counter() const {
        if (counter_) {
            std::cout << name_ << ": &" << counter_ << '\n';
        } else {
            std::cout << name_ << ": &0" << '\n';
        }
    }

   public:
    SharedPtr(std::string_view name) : name_(name) {
        obj_ = nullptr;
        counter_ = 0;
        std::cout << name_ << " -> Default constructor.\n";
        print_counter();
    };

    SharedPtr(std::string_view name, T obj) : name_(name) {
        obj_ = new T(obj);
        counter_ = 1;
        std::cout << name_ << "-> constructor with parameters.\n";
        print_counter();
    }
    ~SharedPtr() {
        if (--counter_ == 0) {
            delete obj_;
            std::cout << name_ << " -> destructed.\n";
        }
    }

    SharedPtr(const SharedPtr& other) {
        counter_ = other.counter_;
        obj_ = other.obj_;
        name_ = other.name_;

        ++counter_;

        print_counter();
        std::cout << name_ << "-> copy constructor.\n";
    }

    T& operator*() { return *obj_; }
};