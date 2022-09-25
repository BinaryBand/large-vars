#include <iostream>
using namespace std;


const unsigned char BYTE_MASK = 0b11111111;

template<int ARRAY_SIZE>
class Word {
protected:
    const int size;
    unsigned char bytes[ARRAY_SIZE];
    void leftShift(const int shift);
    void rightShift(const int shift);
    void bitwiseAnd(const Word& b);
    void bitwiseOr(const Word& b);
    void bitwiseXor(const Word& b);
    void bitwiseNot();
public:
    Word();
    Word(int value);
    Word(const Word& value);
    string toBin() const;
    explicit operator bool() const {
        for (int i = 0; i < size; i++) {
            if (this->bytes[i] != 0) {
                return true;
            }
        }
        return false;
    }
    void operator <<= (const int shift);
    void operator >>= (const int shift);
    void operator &= (const Word& b);
    void operator |= (const Word& b);
    void operator ^= (const Word& b);
    Word operator << (const int shift) const;
    Word operator >> (const int shift) const;
    Word operator & (const Word& b) const;
    Word operator | (const Word& b) const;
    Word operator ^ (const Word& b) const;
    Word operator ~ () const;
};

template<int ARRAY_SIZE>
Word<ARRAY_SIZE>::Word(): size(ARRAY_SIZE) {
    for (int i = 0; i < size; i++) {
        bytes[i] = 0;
    }
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE>::Word(int value): size(ARRAY_SIZE) {
    for (int i = size - 1; i >= 0; i--) {
        bytes[i] = value & BYTE_MASK;
        value >>= 8;
    }
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE>::Word(const Word& value): size(ARRAY_SIZE) {
    for (int i = 0; i < size; i++) {
        bytes[i] = value.bytes[i];
    }
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::leftShift(const int shift) {
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

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::rightShift(const int shift) {
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

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::bitwiseAnd(const Word& b) {
    for (int i = 0; i < size; i++) {
        this->bytes[i] &= b.bytes[i];
    }
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::bitwiseOr(const Word& b) {
    for (int i = 0; i < size; i++) {
        this->bytes[i] |= b.bytes[i];
    }
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::bitwiseXor(const Word& b) {
    for (int i = 0; i < size; i++) {
        this->bytes[i] ^= b.bytes[i];
    }
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::bitwiseNot() {
    for (int i = 0; i < size; i++) {
        this->bytes[i] = ~this->bytes[i];
    }
}

template<int ARRAY_SIZE>
string Word<ARRAY_SIZE>::toBin() const {
    string out = "";
    for (int i = size - 1; i >= 0; i--) {
        unsigned char view = bytes[i];
        for (int j = 0; j < 8; j++) {
            out = ((view & 1) ? '1' : '0') + out;
            view >>= 1;
        }
    }

    return out;
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::operator <<= (const int shift) {
    this->leftShift(shift);
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::operator >>= (const int shift) {
    this->rightShift(shift);
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::operator &= (const Word& b) {
    this->bitwiseAnd(b);
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::operator |= (const Word& b) {
    this->bitwiseOr(b);
}

template<int ARRAY_SIZE>
void Word<ARRAY_SIZE>::operator ^= (const Word& b) {
    this->bitwiseXor(b);
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE> Word<ARRAY_SIZE>::operator << (const int shift) const {
    Word out = *this;
    out.leftShift(shift);
    return out;
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE> Word<ARRAY_SIZE>::operator >> (const int shift) const {
    Word out = *this;
    out.rightShift(shift);
    return out;
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE> Word<ARRAY_SIZE>::operator & (const Word& b) const {
    Word out = *this;
    out.bitwiseAnd(b);
    return out;
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE> Word<ARRAY_SIZE>::operator | (const Word& b) const {
    Word out = *this;
    out.bitwiseOr(b);
    return out;
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE> Word<ARRAY_SIZE>::operator ^ (const Word& b) const {
    Word out = *this;
    out.bitwiseXor(b);
    return out;
}

template<int ARRAY_SIZE>
Word<ARRAY_SIZE> Word<ARRAY_SIZE>::operator ~ () const {
    Word out = *this;
    out.bitwiseNot();
    return out;
}