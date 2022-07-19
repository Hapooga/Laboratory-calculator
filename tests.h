#ifndef TESTS_H
#define TESTS_H

#include <vector>
#include <string>

#include "tester.h"
#include "formula_parser.h"

#include <QString>


void TestFindEquivalent(){
// ZnCl2 - исключения
// остатки из одного элемента в скобки не заключаются
// KHCO3
// Al2(CO3)3
// Al(HCO3)3
//(MgOH)2SO4
}

void TestParse() {

    std::vector<std::string> formuls{
        "HCO3-",
        "HC5H5N+",
        "[Cu(H2O)4]SO4*0.5H2O",
        "[Cu(H2O)4]SO4*H2O",
        "Cu(NO3)2*6H2O",
        "Co3(Fe(CN)6)2",
        "(NH4)2[Pt(SCN)6]",
        "(NH4)2Hg(SCN)4",
        "C4H11NO3*HCl",
        "C18H36N4O11*H2SO4*H2O"
    };


    std::vector<float> results;

    QString error;

    for (const auto& formula : formuls) {

        QString tmp = QString::fromStdString(formula);

        results.push_back(ConvertToMolecularWeight(tmp, error));

    }

    std::vector<std::string> comparation{
        "61.0159",
        "66.1026",
        "240.675",
        "249.682",
        "295.643",
        "600.709",
        "579.661",
        "469.004",
        "157.596",
        "600.594"
    };

    for (size_t i = 0; i < comparation.size(); ++i) {

        ASSERT_EQUAL(comparation[i], results[i]);

    }
}

#endif // TESTS_H
