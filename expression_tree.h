#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <utility>
#include <memory>

//==============================================================================

template <typename T>
class Expression {
public:
    virtual T Evaluate() const = 0;
    virtual ~Expression() = default;
};

//==============================================================================

template <typename T>
using ExprPtr = std::unique_ptr<Expression<T>>;

//==============================================================================

template <typename T>
class VelueExpr : public Expression<T> {
public:
    VelueExpr(T value) : value_(value) {}
    T Evaluate() const final {
        return value_;
    }
private:
    T value_;
};

//==============================================================================

template <typename T>
class ByneryExpr : public Expression<T> {
public:
    ByneryExpr(ExprPtr<T> left, ExprPtr<T> right) :
        left_(std::move(left)), right_(std::move(right)) {}

    T Evaluate() const final {
        return EvaluateOnValues(left_->Evaluate(), right_->Evaluate());
    }
private:
    virtual T EvaluateOnValues(T left, T right) const = 0;
    ExprPtr<T> left_;
    ExprPtr<T> right_;
};

//==============================================================================

template <typename T>
class ProductExpr : public ByneryExpr<T> {
public:
    ProductExpr(ExprPtr<T> left, ExprPtr<T> right) :
        ByneryExpr<T>(std::move(left), std::move(right)) {}

private:
    float EvaluateOnValues(T left, T right) const final {
        return left * right;
    }
};

//==============================================================================

template <typename T>
class SumExpr : public ByneryExpr<T> {
public:
    SumExpr(ExprPtr<T> left, ExprPtr<T> right) :
        ByneryExpr<T>(std::move(left), std::move(right)) {}
private:
    float EvaluateOnValues(T left, T right) const final {
        return left + right;
    }
};

//==============================================================================

template <typename T>
ExprPtr<T> Value(T value) {
    return std::make_unique<VelueExpr<T>>(value);
}

//==============================================================================

template <typename T>
ExprPtr<T> Sum(ExprPtr<T> left, ExprPtr<T> right) {
    return std::make_unique<SumExpr<T>>(std::move(left), std::move(right));
}

//==============================================================================

template <typename T>
ExprPtr<T> Product(ExprPtr<T> left, ExprPtr<T> right) {
    return std::make_unique<ProductExpr<T>>(std::move(left), std::move(right));
}

//==============================================================================

#endif // EXPRESSION_TREE_H
