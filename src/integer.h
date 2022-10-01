#include "./word.h"


class Integer: public Word {
private:
    void add(Word&);
    void sub(Word&);
    void mult(Word&);
    void flip();
public:
    Integer(): Word() {}
    Integer(int value): Word(value) {}
    Integer(Word& value): Word(value) {}
    bool isNegative() const;
    void operator += (const Word&);
    void operator -= (const Word&);
    Integer operator + (const Word&) const;
    Integer operator - (const Word&) const;
    friend std::ostream& operator << (std::ostream& out, Integer&);
};