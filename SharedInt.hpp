#pragma once
#include <iostream>
#include <string>
#include <string_view>

class SharedInt {
   private:
    int* counter_;
    int* obj_;

    std::string name_;
    void print_counter() const {
        if (counter_) {
            std::cout << name_ << ": &" << *counter_ << '\n';
        } else {
            std::cout << name_ << ": &0" << '\n';
        }
    }

   public:
    SharedInt(std::string_view name) : name_(name) {
        obj_ = nullptr;
        counter_ = nullptr;
        std::cout << name_ << " -> Default constructor.\n";
        print_counter();
    };

    ~SharedInt() {
        if (counter_) {
            if (--(*counter_) == 0) {
                delete obj_;
                delete counter_;
                std::cout << name_ << " -> destructed.\n";
            }
        } else {
            std::cout << "Fake destructor, no data to clean.\n";
        }
    }

    SharedInt(std::string_view name, int obj) : name_(name) {
        obj_ = new int(obj);
        counter_ = new int(1);
        std::cout << name_ << "-> constructor with parameters.\n";
        print_counter();
    }

    SharedInt(const SharedInt& other) {
        counter_ = other.counter_;
        obj_ = other.obj_;
        name_ = other.name_;
        if (counter_) {
            ++(*counter_);
        }
        print_counter();
        std::cout << name_ << "-> copy constructor.\n";
    }

    int& operator*() { return *obj_; }
};