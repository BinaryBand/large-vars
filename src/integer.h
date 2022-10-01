#include "./word.h"


class Integer: public Word {
private:
    void add(const Word&);
    void sub(const Word&);
    void mult(const Word&);
    void flip();
public:
    Integer(): Word() {}
    Integer(const int value): Word(value) {}
    Integer(const Word& value): Word(value) {}
    bool isNegative() const;
    void operator += (const Word&);
    void operator -= (const Word&);
    void operator *= (const Word&);
    Integer operator + (const Word&) const;
    Integer operator - (const Word&) const;
    friend Integer abs(Integer&);
    friend std::ostream& operator << (std::ostream&, Integer&);
};