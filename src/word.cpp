#include "./word.h"


Word::Word() {
    bytes = new unsigned char[size]();

    for (int i = 0; i < size; i++) {
        bytes[i] = 0;
    }
}

Word::Word(int value) {
    bytes = new unsigned char[size]();

    for (int i = size - 1; i >= 0; i--) {
        bytes[i] = value | 0;
        value >>= 8;
    }
}

Word::Word(const Word& value) {
    bytes = new unsigned char[size]();

    for (int i = 0; i < size; i++) {
        bytes[i] = value.bytes[i];
    }
}

int Word::getSize() const {
    return this->size;
}

bool Word::toBool() const {
    for (int i = 0; i < size; i++) {
        if (this->bytes[i] != 0) {
            return true;
        }
    }
    
    return false;
}

void Word::leftShift(const int shift) {
    // Shift bytes.
    int i = 0;
    int bigShift = shift / 8;
    for (; i < size - bigShift; i++) {
        bytes[i] = bytes[i + bigShift];
    }
    for (; i < size; i++) {
        bytes[i] = 0;
    }

    // Shift bits.
    int littleShift = shift % 8;
    for (int i = 0; i < size - 1; i++) {
        bytes[i] <<= littleShift;
        bytes[i] |= bytes[i + 1] >> (8 - littleShift);
    }
    bytes[size - 1] <<= littleShift;
}

void Word::rightShift(const int shift) {
    int i = size - 1;
    int bigShift = shift / 8;
    for (; i >= bigShift; i--) {
        bytes[i] = bytes[i - bigShift];
    }
    for (; i >= 0; i--) {
        bytes[i] = 0;
    }

    int littleShift = shift % 8;
    for (int i = size - 1; i > 0; i--) {
        bytes[i] >>= littleShift;
        bytes[i] |= bytes[i - 1] << (8 - littleShift);
    }
    bytes[0] >>= littleShift;
}

void Word::bitwiseAnd(const Word& b) {
    for (int i = 0; i < size; i++) {
        this->bytes[i] &= b.bytes[i];
    }
}

void Word::bitwiseOr(const Word& b) {
    for (int i = 0; i < size; i++) {
        this->bytes[i] |= b.bytes[i];
    }
}

void Word::bitwiseXor(const Word& b) {
    for (int i = 0; i < size; i++) {
        this->bytes[i] ^= b.bytes[i];
    }
}

void Word::bitwiseNot() {
    for (int i = 0; i < size; i++) {
        this->bytes[i] = ~this->bytes[i];
    }
}

void Word::operator <<= (const int shift) {
    this->leftShift(shift);
}

void Word::operator >>= (const int shift) {
    this->rightShift(shift);
}

void Word::operator &= (const Word& b) {
    this->bitwiseAnd(b);
}

void Word::operator |= (const Word& b) {
    this->bitwiseOr(b);
}

void Word::operator ^= (const Word& b) {
    this->bitwiseXor(b);
}

Word Word::operator << (const int shift) const {
    Word out = *this;
    out.leftShift(shift);
    return out;
}

Word Word::operator >> (const int shift) const {
    Word out = *this;
    out.rightShift(shift);
    return out;
}

Word Word::operator & (const Word& b) const {
    Word out = *this;
    out.bitwiseAnd(b);
    return out;
}

Word Word::operator | (const Word& b) const {
    Word out = *this;
    out.bitwiseOr(b);
    return out;
}

Word Word::operator ^ (const Word& b) const {
    Word out = *this;
    out.bitwiseXor(b);
    return out;
}

Word Word::operator ~ () const {
    Word out = *this;
    out.bitwiseNot();
    return out;
}