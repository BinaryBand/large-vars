#include "./integer.h"
#include <cmath>


void Integer::add(Word& b) {
    Word carry;
    while (b.toBool()) {
        carry = *this & b;
        *this ^= b;
        b = carry << 1;
    }
}

void Integer::sub(Word& b) {
    Word borrow;
    while (b.toBool()) {
        borrow = ~(*this) & b;
        *this ^= b;
        b = borrow << 1;
    }
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
    Word c = b;
    this->add(c);
}

void Integer::operator -= (const Word& b) {
    Word c = b;
    this->sub(c);
}

Integer Integer::operator + (const Word& b) const {
    Integer out = *this;
    Word c = b;
    out.add(c);
    return out;
}

Integer Integer::operator - (const Word& b) const {
    Integer out = *this;
    Word c = b;
    out.sub(c);
    return out;
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
        unsigned int carry = a.bytes[i];

        int j = 0;
        for (; j < outLength || carry; j++) {
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