#include "./word.h"


class Integer: public Word<4> {
private:
    void add(const Word& b);
public:
    Integer(): Word() {}
    Integer(int value): Word(value) {}
    Integer(Word& value): Word(value) {}
    void operator += (const Word& b);
    Integer operator + (const Word& b) const;
};