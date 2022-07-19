#include "expression_tree.h"
#include "periodic_table.h"
#include "formula_parser.h"

#include <QString>
#include <string>
#include <sstream>
#include <cctype>
#include <memory>
#include <string_view>

using namespace std;

float ToFloat(const string& element_atomic_weight) {

    stringstream str(element_atomic_weight);

    float result = 0;

    str >> result;

    return result;
}

string GetElement(string_view& formula, QString& error) {

    string result;
    result.push_back(formula.front());
    formula.remove_prefix(1);

    if (!formula.empty()) {

        if (isdigit(result[0]) && (isdigit(formula.front()) || formula.front() == '.')) {

            while (isdigit(formula.front()) || formula.front() == '.') {

                result.push_back(formula.front());
                formula.remove_prefix(1);
                if (formula.empty()) {

                    break;
                }

                else if ((formula.front() == '.' && result.back() == '.') || (formula.front() == '.' && isdigit(result.back()))) {

                    error = "Неверный ввод " + QString::fromStdString(string(formula));
                }
            }
        }
        else if (islower(formula.front())) {

            result.push_back(formula.front());
            formula.remove_prefix(1);
        }
    }

    return result;
}

string_view CatSubFormula(string_view& formula, const size_t left_pose, const size_t right_pose) {

    string_view sub_formula = formula.substr(left_pose, right_pose);

    formula.remove_prefix(right_pose);

    return sub_formula;
}

bool IsIn(const string_view formula, const size_t pose) {

    return pose < formula.size();
}

string_view GetSubFormula(string_view& formula) {

    size_t after_opening_bracket_pose = 0;
    size_t closing_bracket = formula.find_first_of(')');
    size_t one_more_sub_formula_bracket = formula.find_first_of('(');

    if (IsIn(formula, closing_bracket) && IsIn(formula, one_more_sub_formula_bracket)) {

        if (closing_bracket < one_more_sub_formula_bracket) {
            return {CatSubFormula(formula, after_opening_bracket_pose, closing_bracket)};
        }

        if (closing_bracket > one_more_sub_formula_bracket) {
            closing_bracket = formula.find_last_of(')');
            return {CatSubFormula(formula, after_opening_bracket_pose, closing_bracket)};
        }

    }

    //if (IsIn(formula, closing_bracket) && !IsIn(formula, one_more_sub_formula_bracket))
        return {CatSubFormula(formula, after_opening_bracket_pose, closing_bracket)};
}

unique_ptr<Expression<float>> Parse(string_view& formula, QString& error) {

    if (formula.empty()) {

        return Value(static_cast<float>(0));
    }
    // =========================================================================================================================
    if (formula.front() == '[' || formula.front() == ']' ||
        formula.front() == '*' || formula.front() == '-' ||
        formula.front() == '+'
        ) {

        formula.remove_prefix(1);

        return Parse(formula, error);
    }
    // =========================================================================================================================
    if (formula.front() == '(') {

        formula.remove_prefix(1);

        string_view sub_formula_view(GetSubFormula(formula));

        unique_ptr<Expression<float>> sub_formula = Parse(sub_formula_view, error);

        formula.remove_prefix(1);

        // -----------------------------------
        if (formula.empty()) {

            error = "Неверно установлены скобки " + QString::fromStdString(string(formula));

        }
        // -----------------------------------

        float l_value = ToFloat(GetElement(formula, error));

        // -----------------------------------
        if (formula.empty()) {

            return Product(Value(sub_formula->Evaluate()), Value(l_value));
        }
        // -----------------------------------
        return Sum(Product(Value(sub_formula->Evaluate()), Value(l_value)), Parse(formula, error));
    }
    // =========================================================================================================================
    if (isdigit(formula.front())) {

        float l_value = ToFloat(GetElement(formula, error));
        // -----------------------------------
        if (formula.front() == '(') {

            error = "Неверно установлены скобки " + QString::fromStdString(string(formula));
        }
        // -----------------------------------
        if (isupper(formula.front())) {

            return Product(Value(l_value), Parse(formula, error));
        }
        // -----------------------------------
        if (formula.empty()) {

            return Value(l_value);
        }
        // ------------------------------------
    }
    // =========================================================================================================================
    if (isupper(formula.front())) {

        float l_value = PeriodicTable::Instence().GetAtomicWeightFromClass(GetElement(formula, error));
        // -----------------------------------
        if(l_value == 0){

            error = "Неверно введен химический элемент";

        }
        // -----------------------------------
        if (formula.empty()) {

            return Value(l_value);
        }
        // -----------------------------------
        if (isupper(formula.front())) {

            return Sum(Value(l_value), Parse(formula, error));
        }
        // -----------------------------------
        if (isdigit(formula.front())) {

            float r_value = ToFloat(GetElement(formula, error));
            // ------------------
            if (formula.empty()) {

                return Product(Value(l_value), Value(r_value));
            }
            // ------------------

            return Sum(Product(Value(l_value), Value(r_value)), Parse(formula, error));

        }
        // -----------------------------------
        if (formula.front() == '(') {

            formula.remove_prefix(1);

            string_view sub_formula_view(GetSubFormula(formula));

            unique_ptr<Expression<float>> sub_formula = Parse(sub_formula_view, error);

            formula.remove_prefix(1);

            // ------------------
            if (formula.empty()) {

                error = "Неверно установлены скобки " + QString::fromStdString(string(formula));

            }
            // ------------------

            float r_value = ToFloat(GetElement(formula, error));

            // ------------------
            if (formula.empty()) {

                return Sum(Value(l_value), Product(Value(sub_formula->Evaluate()), Value(r_value)));
            }
            // ------------------
            return Sum(Sum(Value(l_value), Product(Value(sub_formula->Evaluate()), Value(r_value))), Parse(formula, error));
        }
        // -----------------------------------
        return Parse(formula, error);
    }
    // =========================================================================================================================

    error = "Неверный ввод " + QString::fromStdString(string(formula));

    return Value(static_cast<float>(0));
}

float ConvertToMolecularWeight(const QString& сhemical_formula, QString& error) {

    string formula = сhemical_formula.toStdString();

    string_view formula_view(formula);

    unique_ptr<Expression<float>> formula_expression = Parse(formula_view, error);

    return formula_expression->Evaluate();

}

