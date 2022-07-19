#ifndef CHECK_FUNCTIONS_H
#define CHECK_FUNCTIONS_H

#include <QString>

// [^A-Za-z0-9] acid limit chars filter
// [^\\*\\.A-Za-z0-9()\[\\]+,-] formula for parsing chars filter

bool InputHaseCorrectChars(const QString& input_formula, const QString& correct_chars);

bool EquivalentIsUnsignedInt(const QString& input_equivalent);

QString CheckDBInput(const QString& acid_limit_input, const QString& equivalent_limit);

QString CheckFormula(const QString& formula);

QString CheckFloatInput(const QString& float_input);

QString CheckInput(const QString& formula_input, const QString& float_input1, const QString& float_input2);

QString CheckLigationInput(
        const QString& float_input1,
        const QString& float_input2,
        const QString& float_input3,
        const QString& float_input4,
        const QString& float_input5
        );

#endif // CHECK_FUNCTIONS_H
