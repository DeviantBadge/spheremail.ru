#include <vector>
#include <iostream>
#include <regex>
#include <exception>

using namespace std;

enum class Token {
    number,
    multiply,
    add,
    sub,
    divide,
    wrong_lexeme,
    expression_end
};

struct lexeme {
    Token type;
    int value;
};

bool is_number(char ch) {
    return ch <= '9' && ch >= '0';
}

class calculator {
private:
    int result = -1;
public:
    calculator() {
    }

    bool calc(const string &str) {
        lexeme cur_lexeme;
        string::const_iterator position = str.begin();
        const string::const_iterator end = str.end();
        try {
            result = calc_expression(position, end);
            return true;
        } catch (const invalid_argument &e) {
            return false;
        }

    }

    int get_result() {
        return result;
    }

private:

    int calc_expression(string::const_iterator &position, string::const_iterator end) {
        int res = calc_addend(position, end);
        lexeme cur_lexeme;

        do {
            cur_lexeme = get_lexeme(position, end);
            switch (cur_lexeme.type) {
                case Token::add:
                    res += calc_addend(++position, end);
                    continue;

                case Token::sub:
                    res -= calc_addend(++position, end);
                    continue;

                case Token::expression_end:
                    return res;

                default:
                    throw invalid_argument("Expected (+|-).");
            }
        } while (true);
    }

    int calc_addend(string::const_iterator &position, string::const_iterator end) {
        int res = calc_value(position, end);
        lexeme cur_lexeme;
        int quotient;

        do {
            cur_lexeme = get_lexeme(position, end);
            switch (cur_lexeme.type) {
                case Token::multiply:
                    res *= calc_value(++position, end);
                    continue;

                case Token::divide:
                    quotient = calc_value(++position, end);
                    if (quotient == 0)
                        throw invalid_argument("Cant divide by zero");
                    res /= quotient;
                    continue;

                case Token::add:
                case Token::sub:
                case Token::expression_end:
                    return res;

                default:
                    throw invalid_argument("Expected (+|-|/|*).");
            }
        } while (true);
    }


    int calc_value(string::const_iterator &position, string::const_iterator end) {
        lexeme cur_lexeme = get_lexeme(position, end);

        switch (cur_lexeme.type) {
            case Token::number:
                return cur_lexeme.value;
            case Token::add:
                return calc_value(++position, end);
            case Token::sub:
                return -calc_value(++position, end);
            default:
                throw invalid_argument("Expected (+|-|number).");
        }
    }

    lexeme get_lexeme(string::const_iterator &position, string::const_iterator end) {
        if (position == end)
            return lexeme{Token::expression_end};
        char cur_char = *position;
        switch (cur_char) {
            case '*':
                return lexeme{Token::multiply};
            case '/':
                return lexeme{Token::divide};
            case '-':
                return lexeme{Token::sub};
            case '+':
                return lexeme{Token::add};
            case ' ':
                return get_lexeme(++position, end);
            default:
                if (!is_number(cur_char))
                    return lexeme{Token::wrong_lexeme};
                int res = 0;
                do {
                    res = res * 10 + cur_char - '0';
                    ++position;
                    cur_char = *position;
                } while (is_number(cur_char) && position != end);
                return lexeme{Token::number, res};
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "error" << endl;
        return 1;
    }

    calculator calc;
    if (!calc.calc(argv[1])) {
        cout << "error" << endl;
        return 1;
    } else {
        cout << calc.get_result() << endl;
        return 0;
    }
}
