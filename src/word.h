#include <iostream>


class Word {
private:
    void leftShift(const int);
    void rightShift(const int);
    void bitwiseAnd(const Word&);
    void bitwiseOr(const Word&);
    void bitwiseXor(const Word&);
    void bitwiseNot();
protected:
    static const int size = 4;
    unsigned char* bytes;
public:
    Word();
    Word(int);
    Word(const Word&);
    int getSize() const;
    bool toBool() const;
    void operator <<= (const int);
    void operator >>= (const int);
    void operator &= (const Word&);
    void operator |= (const Word&);
    void operator ^= (const Word&);
    Word operator << (const int) const;
    Word operator >> (const int) const;
    Word operator & (const Word&) const;
    Word operator | (const Word&) const;
    Word operator ^ (const Word&) const;
    Word operator ~ () const;
    friend std::string bin(Word w);
};