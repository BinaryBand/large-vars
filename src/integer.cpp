#include "./integer.h"
#include <cmath>


void Integer::add(const Word& b) {
    Integer c = b;
    Word carry;
    while (c.toBool()) {
        carry = *this & c;
        *this ^= c;
        c = carry << 1;
    }
}

void Integer::sub(const Word& b) {
    Integer c = b;
    Word borrow;
    while (c.toBool()) {
        borrow = ~(*this) & c;
        *this ^= c;
        c = borrow << 1;
    }
}

void Integer::mult(const Word& b) {
    Integer out;
    Integer c = b;
    bool isNegative = this->isNegative() != c.isNegative();
    abs(*this);
    abs(c);

    while (c.toBool()) {
        if ((c & 1).toBool()) {
            out += *this;
        }
        *this <<= 1;
        c >>= 1;
    }

    if (isNegative) {
        out.flip();
    }

    *this = out;
}

void Integer::flip() {
    int i = 0;
    for (; i < size; i++) {
        this->bytes[i] = ~(this->bytes[i]);
    }
    *this += 1;
}

bool Integer::isNegative() const {
    return this->bytes[0] & 0b10000000;
}

void Integer::operator += (const Word& b) {
    this->add(b);
}

void Integer::operator -= (const Word& b) {
    this->sub(b);
}

void Integer::operator *= (const Word& b) {
    this->mult(b);
}

Integer Integer::operator + (const Word& b) const {
    Integer out = *this;
    out.add(b);
    return out;
}

Integer Integer::operator - (const Word& b) const {
    Integer out = *this;
    out.sub(b);
    return out;
}

Integer abs(Integer& a) {
    if (a.isNegative()) {
        a.flip();
    }
    return a;
}

std::ostream& operator << (std::ostream& os, Integer& a) {
    const int IN_BASE = 256;
    const int OUT_BASE = 10;

    bool isNegative = a.isNegative();
    if (isNegative) {
        a.flip();
        os << '-';
    }

    int maxSize = ceil(a.getSize() * log(IN_BASE) / log(OUT_BASE));
    int* out = new int[maxSize]();

    int outLength = 0;
    for (int i = 0; i < a.getSize(); i++) {
        int j = 0;
        for (int carry = a.bytes[i]; j < outLength || carry; j++) {
            out[j] = out[j] * IN_BASE + carry;
            carry = out[j] / OUT_BASE;
            out[j] %= OUT_BASE;
        }
        outLength = j;
    }

    if (isNegative) {
        a.flip();
    }

    while (outLength--) {
        int charIndex = out[outLength];
        os << charIndex;
    }

    return os;
}