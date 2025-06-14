#ifndef EXS_OPERATOR_LOWER_EQUAL_H
#define EXS_OPERATOR_LOWER_EQUAL_H

namespace exs {
  
template <class A, typename S = EmptySettings>
class OperatorLowerEqual: public OperatorBase<A, S> {
public:
  OperatorLowerEqual(std::string s="<="): OperatorBase<A, S>("le", s, LOWER_EQUAL_OPERATOR) {}
    void operate_binary(TokenListBase<A>* tokens) override {
        Token<A> left = tokens->get_left();
        Token<A> right = tokens->get_right();
        left.atom->comparison_lower_equal(right.atom);
        tokens->put_left(left);
    };
};

}

#endif // EXS_OPERATOR_LOWER_EQUAL_H
