#include "./integer.h"


void Integer::add(const Word& b) {
    Word<4> carry = *this;
    carry &= b;
    *this ^= b;
    if (carry) {
        carry <<= 1;
        this->add(carry);
    }
}

void Integer::operator += (const Word& b) {
    this->add(b);
}

Integer Integer::operator + (const Word& b) const {
    Integer out = *this;
    out.add(b);
    return out;
}