#include "check_functions.h"

#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

bool InputHaseCorrectChars(const QString& input_formula, const QString& correct_chars) {

    static QRegularExpression rx(correct_chars);

    auto match = rx.match(input_formula);

    if (match.hasMatch()) {

        return false;
    }

    return true;
}

bool EquivalentIsUnsignedInt(const QString& input_equivalent) {

    if (input_equivalent.toInt() < 0 || !input_equivalent.toInt()) {

        return false;
    }

    return true;
}

QString CheckFormula(const QString& formula){

    if(!InputHaseCorrectChars(formula,"[^\\*\\.A-Za-z0-9()\[\\]+,-]")){

        return "Формула содержит некорректные значения";

    }

    return "";

}

QString CheckDBInput(const QString& acid_limit_input, const QString& equivalent_limit){


    if (acid_limit_input.isEmpty()) {

       return "Пустое поле кислотного остатка";

    } else if (!InputHaseCorrectChars(acid_limit_input, "[^A-Za-z0-9]")){

        return "Кислотный остаток содержит некорректные значения";

    }

    if (equivalent_limit.isEmpty()) {

        return "Пустое поле эквивалента";

    } else if (!EquivalentIsUnsignedInt(equivalent_limit)) {

        return "Некорректное значение эквивалента";

    }

    return "";

}

QString CheckFloatInput(const QString& float_input){

    if(float_input.isEmpty()){

        return "Пустое поле ввода";

    }

    else if(!InputHaseCorrectChars(float_input, "[^\\.0-9,]")){

        return "Проверьте введенные значения на недопустимые символы";
    }

    else if(float_input.contains(".") && float_input.contains(",")){

       return "Проверьте введенные значения на недопустимые символы";

    }

    else if(float_input.count('.') > 1 || float_input.count(',') > 1){

        return "Проверьте введенные значения на недопустимые символы";

    }

    else if(float_input == "." || float_input == "," || float_input == ",." || float_input == ".,"){

        return "Проверьте введенные значения на недопустимые символы";

    }

    return "";

}

QString CheckInput(const QString& formula_input, const QString& float_input1, const QString& float_input2){

    QString error = CheckFormula(formula_input);

    if(error.isEmpty()){

    error = CheckFloatInput(float_input1);

    }

    else if(error.isEmpty()){

    error = CheckFloatInput(float_input2);

    }

    return error;

}

QString CheckLigationInput(
        const QString& float_input1,
        const QString& float_input2,
        const QString& float_input3,
        const QString& float_input4,
        const QString& float_input5
        ){

    QString error = CheckFloatInput(float_input1);

    if(error.isEmpty()){

    error = CheckFloatInput(float_input2);

    }

   else if(error.isEmpty()){

    error = CheckFloatInput(float_input3);

    }

   else if(error.isEmpty()){

    error = CheckFloatInput(float_input4);

    }

   else if(error.isEmpty()){

    error = CheckFloatInput(float_input5);

    }

    return error;
}
