#ifndef HEX_H
#define HEX_H

#include <string>
#include <stdexcept>
#include <initializer_list>

class Hex {
public:
    Hex();
    Hex(const size_t& n, unsigned char t = 0);
    Hex(const std::initializer_list<unsigned char>& t);
    Hex(const std::string& t);
    Hex(const Hex& other);
    Hex(Hex&& other) noexcept;
    virtual ~Hex() noexcept;

    Hex add(const Hex& other) const;
    Hex subtract(const Hex& other) const;
    bool equals(const Hex& other) const;
    bool lessThan(const Hex& other) const;
    bool greaterThan(const Hex& other) const;

    std::string toString() const;
    size_t size() const;

private:
    unsigned char* data_;
    size_t size_;

    void removeLeadingZeros();
    int compare(const Hex& other) const;
};

#endif
