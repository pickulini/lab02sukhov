#include "../include/16g.h"
#include <algorithm>
#include <cctype>
#include <iostream>

Hex::Hex() : data_(new unsigned char[1]{0}), size_(1) {}

Hex::Hex(const size_t& n, unsigned char t) : data_(new unsigned char[n]), size_(n) {
    std::fill(data_, data_ + n, t);
    removeLeadingZeros();
}

Hex::Hex(const std::initializer_list<unsigned char>& t) : data_(new unsigned char[t.size()]), size_(t.size()) {
    size_t i = 0;
    for (auto it = t.begin(); it != t.end(); ++it, ++i) {
        data_[size_ - 1 - i] = *it;
    }
    removeLeadingZeros();
}

Hex::Hex(const std::string& t) {
    if (t.empty()) throw std::invalid_argument("Empty string");
    size_ = t.size();
    data_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; ++i) {
        char c = t[i];
        if (c >= '0' && c <= '9') data_[size_ - 1 - i] = c - '0';
        else if (c >= 'A' && c <= 'F') data_[size_ - 1 - i] = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') data_[size_ - 1 - i] = c - 'a' + 10;
        else throw std::invalid_argument("Invalid hex digit");
    }
    removeLeadingZeros();
}

Hex::Hex(const Hex& other) : data_(new unsigned char[other.size_]), size_(other.size_) {
    std::copy(other.data_, other.data_ + size_, data_);
}

Hex::Hex(Hex&& other) noexcept : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

Hex::~Hex() noexcept {
    delete[] data_;
}

Hex Hex::add(const Hex& other) const {
    size_t maxSize = std::max(size_, other.size_);
    unsigned char* resultData = new unsigned char[maxSize + 1];
    std::fill(resultData, resultData + maxSize + 1, 0);
    
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char sum = carry;
        if (i < size_) sum += data_[i];
        if (i < other.size_) sum += other.data_[i];
        resultData[i] = sum % 16;
        carry = sum / 16;
    }
    
    if (carry) {
        resultData[maxSize] = carry;
    }
    
    Hex result;
    delete[] result.data_;
    result.data_ = resultData;
    result.size_ = carry ? maxSize + 1 : maxSize;
    result.removeLeadingZeros();
    return result;
}

Hex Hex::subtract(const Hex& other) const {
    if (lessThan(other)) throw std::underflow_error("Negative result");
    
    size_t maxSize = size_;
    unsigned char* resultData = new unsigned char[maxSize];
    std::fill(resultData, resultData + maxSize, 0);
    
    int borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        int digit = data_[i] - borrow;
        if (i < other.size_) digit -= other.data_[i];
        
        if (digit < 0) {
            digit += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultData[i] = digit;
    }
    
    Hex result;
    delete[] result.data_;
    result.data_ = resultData;
    result.size_ = maxSize;
    result.removeLeadingZeros();
    return result;
}

bool Hex::equals(const Hex& other) const {
    return compare(other) == 0;
}

bool Hex::lessThan(const Hex& other) const {
    return compare(other) < 0;
}

bool Hex::greaterThan(const Hex& other) const {
    return compare(other) > 0;
}

std::string Hex::toString() const {
    if (size_ == 1 && data_[0] == 0) return "0";
    std::string result;
    for (int i = size_ - 1; i >= 0; --i) {
        unsigned char digit = data_[i];
        if (digit < 10) result += '0' + digit;
        else result += 'A' + (digit - 10);
    }
    return result;
}

size_t Hex::size() const {
    return size_;
}

void Hex::removeLeadingZeros() {
    size_t newSize = size_;
    while (newSize > 1 && data_[newSize - 1] == 0) {
        newSize--;
    }
    
    if (newSize != size_) {
        unsigned char* newData = new unsigned char[newSize];
        std::copy(data_, data_ + newSize, newData);
        delete[] data_;
        data_ = newData;
        size_ = newSize;
    }
}

int Hex::compare(const Hex& other) const {
    if (size_ != other.size_) {
        return static_cast<int>(size_) - static_cast<int>(other.size_);
    }
    
    for (int i = size_ - 1; i >= 0; --i) {
        if (data_[i] != other.data_[i]) {
            return static_cast<int>(data_[i]) - static_cast<int>(other.data_[i]);
        }
    }
    return 0;
}
