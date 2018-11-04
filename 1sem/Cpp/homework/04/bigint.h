#ifndef INC_04_BIGINT_H
#define INC_04_BIGINT_H

#include <algorithm>
#include <iostream>
#include <cmath>
#include "my_vector.h"

class BigInt {
private:
    // cant be more then 31
    // one for all BigInt`s
    static const unsigned BIT_BASE = 31;
    static const unsigned CARRY_FLAG = 1 << BIT_BASE;

public:

    inline static unsigned bit_mask(unsigned bits = BIT_BASE);

    inline static unsigned reversed(unsigned val);

private:

    MyVector<unsigned> value;
    bool sign;

public:

    BigInt();

    BigInt(long long initial);

    BigInt(const BigInt &other) = default;

    BigInt(BigInt &&other) = default;

    BigInt &operator=(const BigInt &other) = default;

    BigInt &operator=(BigInt &&other) = default;

    BigInt operator+(const BigInt &other) const;

    BigInt &operator+=(const BigInt &other);

    BigInt operator-(const BigInt &other) const;

    BigInt &operator-=(const BigInt &other);

    BigInt operator-() const;

    BigInt operator*(int other) const;

    BigInt &operator*=(int other);

    BigInt operator/(int other) const;

    BigInt &operator/=(int other);

    int operator%(int other) const;

    BigInt operator>>(unsigned other) const;

    BigInt &operator>>=(unsigned other);

    BigInt operator<<(unsigned other) const;

    BigInt &operator<<=(unsigned other);

    bool operator>(const BigInt &other) const;

    bool operator<=(const BigInt &other) const;

    bool operator<(const BigInt &other) const;

    bool operator>=(const BigInt &other) const;

    bool operator==(const BigInt &other) const;

    bool operator!=(const BigInt &other) const;

    std::string toString(const std::string &separator = "") const;
};

std::ostream &operator<<(std::ostream &out, const BigInt &value) {
    return out << value.toString();
}

BigInt::BigInt() :
        value(),
        sign(false) {
}

BigInt::BigInt(long long initial) :
        value(),
        sign(initial < 0) {
    initial = sign ? -initial : initial;
    while (initial) {
        value.add(initial & bit_mask());
        initial >>= BIT_BASE;
    }
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt sum(*this);
    sum += other;
    return sum;
}

BigInt &BigInt::operator+=(const BigInt &other) {
    if (sign != other.sign)
        return this->operator-=(-other);

    unsigned next_addend = 0;
    std::size_t min_size = std::min(value.size(), other.value.size());
    for (std::size_t i = 0; i < min_size; i++) {
        next_addend += other.value[i];
        value[i] += next_addend;
        if (value[i] & CARRY_FLAG) {
            next_addend = 1;
            value[i] ^= CARRY_FLAG;
        } else
            next_addend = 0;
    }
    if (value.size() >= other.value.size()) {
        for (std::size_t i = min_size; next_addend != 0 && i < value.size(); i++) {
            value[i] += next_addend;
            if (value[i] & CARRY_FLAG)
                value[i] ^= CARRY_FLAG;
            else
                next_addend = 0;
        }
    } else {
        for (std::size_t i = min_size; i < other.value.size(); i++) {
            next_addend += other.value[i];
            value.add(next_addend);
            if (value[i] & CARRY_FLAG) {
                next_addend = 1;
                value[i] ^= CARRY_FLAG;
            } else
                next_addend = 0;
        }
    }
    if (next_addend != 0) {
        value.add(next_addend);
    }
    return *this;
}

BigInt BigInt::operator-(const BigInt &other) const {
    BigInt sub(*this);
    sub -= other;
    return sub;
}

BigInt &BigInt::operator-=(const BigInt &other) {
    if (sign != other.sign)
        return this->operator+=(-other);

    unsigned next_sub = 0;
    std::size_t min_size = std::min(value.size(), other.value.size());
    for (std::size_t i = 0; i < min_size; i++) {
        next_sub += other.value[i];
        value[i] += reversed(next_sub);
        if (value[i] & CARRY_FLAG) {
            next_sub = 0;
            value[i] ^= CARRY_FLAG;
        } else
            next_sub = 1;
    }

    if (value.size() >= other.value.size()) {
        for (std::size_t i = min_size; next_sub != 0 && i < value.size(); i++) {
            value[i] += reversed(next_sub);
            if (value[i] & CARRY_FLAG) {
                next_sub = 0;
                value[i] ^= CARRY_FLAG;
            }
        }
        if (next_sub != 0) {
            value.last() = reversed(value.last());
            sign = !sign;
        }
    } else {
        if (value.size() > 0)
            value.last() = reversed(value.last());
        sign = !sign;
        for (std::size_t i = min_size; i < other.value.size(); i++) {
            value.add(other.value[i] + reversed(next_sub));
            if (value[i] & CARRY_FLAG) {
                next_sub = 0;
                value[i] ^= CARRY_FLAG;
            }
        }
    }
    while (value.size() > 0 && value.last() == 0)
        value.pop();
    return *this;
}

BigInt BigInt::operator-() const {
    BigInt new_int(*this);
    new_int.sign = !sign;
    return new_int;
}

BigInt BigInt::operator*(int other) const {
    BigInt mul(*this);
    mul *= other;
    return mul;
}

BigInt &BigInt::operator*=(int other) {
    sign = sign ^ (other < 0);
    other = abs(other);
    long long cur_res = 0;

    if (other == 0) {
        value.resize(0);
        sign = false;
        return *this;
    }

    for (std::size_t i = 0; i < value.size(); i++) {
        cur_res += value[i] * (long long) other;
        value[i] = cur_res & bit_mask();
        cur_res >>= BIT_BASE;
    }
    if (cur_res > 0)
        value.add(cur_res);
    return *this;
}

BigInt BigInt::operator/(int other) const {
    BigInt div(*this);
    div /= other;
    return div;
}

BigInt &BigInt::operator/=(int other) {
    if (other == 0)
        throw std::invalid_argument("Division by zero");
    sign = sign ^ (other < 0);
    other = abs(other);
    long long cur_res = 0;

    for (int i = value.size() - 1; i >= 0; i--) {
        cur_res = value[i] + (cur_res << BIT_BASE);
        value[i] = cur_res / other;
        cur_res %= other;
    }
    while (value.size() > 1 && value.last() == 0)
        value.pop();
    return *this;
}

int BigInt::operator%(int other) const {
    other = abs(other);
    long long cur_res = 0;

    for (int i = value.size() - 1; i >= 0; i--) {
        cur_res = value[i] + (cur_res << BIT_BASE);
        cur_res %= other;
    }
    return cur_res;
}

BigInt BigInt::operator>>(unsigned other) const {
    BigInt res = *this;
    res >>= other;
    return res;
}

BigInt &BigInt::operator>>=(unsigned other) {
    unsigned shift_blocks = other / BIT_BASE;
    unsigned shift_bits = other % BIT_BASE;
    if (shift_blocks >= value.size()) {
        value.resize(0);
        sign = false;
        return *this;
    }

    if (shift_blocks > 0) {
        for (int i = value.size() - 1; i >= shift_blocks; i--) {
            value[i - shift_blocks] = value[i];
        }
        value.resize(value.size() - shift_blocks);
    }
    long long rem = 0;
    if (shift_bits > 0) {
        for (int i = value.size() - 1; i >= 0; i--) {
            rem = value[i] + (rem << BIT_BASE);
            value[i] = rem >> shift_bits;
            rem &= bit_mask(shift_bits);
        }
    }
    while (value.size() > 1 && value.last() == 0)
        value.pop();
    return *this;
}

BigInt BigInt::operator<<(unsigned other) const {
    BigInt res = *this;
    res <<= other;
    return res;
}

BigInt &BigInt::operator<<=(unsigned other) {
    unsigned shift_blocks = other / BIT_BASE;
    unsigned shift_bits = other % BIT_BASE;

    long long rem = 0;
    if (shift_bits > 0) {
        for (std::size_t i = 0; i < value.size(); i++) {
            rem = ((long long) value[i] << shift_bits) + rem;
            value[i] = rem & bit_mask();
            rem >>= BIT_BASE;
        }
    }
    if (shift_blocks > 0) {
        value.resize(value.size() + shift_blocks);
        int i = shift_blocks;
        for (i = value.size() - 1; i >= shift_blocks; i--) {
            value[i] = value[i - shift_blocks];
        }
        for (; i >= 0; i--)
            value[i] = 0;
    }
    return *this;
}

bool BigInt::operator>(const BigInt &other) const {
    if (sign != other.sign)
        return !sign;
    if (sign)
        return -(*this) < -other;
    if (value.size() > other.value.size())
        return true;
    for (int i = value.size() - 1; i >= 0; i--) {
        if (value[i] > other.value[i])
            return true;
        else if (value[i] < other.value[i])
            return false;
    }
    return false;
}

bool BigInt::operator<=(const BigInt &other) const {
    return !this->operator>(other);
}

bool BigInt::operator<(const BigInt &other) const {
    if (sign != other.sign)
        return sign;
    if (sign)
        return -(*this) > -other;
    if (value.size() < other.value.size())
        return true;
    for (int i = value.size() - 1; i >= 0; i--) {
        if (value[i] < other.value[i])
            return true;
        else if (value[i] > other.value[i])
            return false;
    }
    return false;
}

bool BigInt::operator>=(const BigInt &other) const {
    return !this->operator<(other);
}

bool BigInt::operator==(const BigInt &other) const {
    return (value.size() == 0 || sign == other.sign) &&
           value == other.value;
}

bool BigInt::operator!=(const BigInt &other) const {
    return !operator==(other);
}

unsigned BigInt::bit_mask(unsigned bits) {
    return (((unsigned) 1) << bits) - 1;
}

unsigned BigInt::reversed(unsigned val) {
    return (bit_mask() ^ val) + 1;
}

std::string BigInt::toString(const std::string &separator) const {
    if (value.size() == 0)
        return "0";

    std::string res = "";
    BigInt buff = *this;
    int count = 0;
    unsigned rem = 0;

    for (; buff.value.size() > 1 || buff.value[0] != 0;) {
        if (count % 3 == 0) {
            count = 0;
            res += separator;
        }

        rem = buff % 10;
        buff /= 10;
        res += std::to_string(rem);
        count++;
    }
    res += (sign ? "-" : "");
    std::reverse(res.begin(), res.end());
    return res;
}

#endif //INC_04_BIGINT_H
