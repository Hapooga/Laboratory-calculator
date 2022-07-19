#ifndef RESIDUE_FINDER_H
#define RESIDUE_FINDER_H

#include "db_worker.h"

#include <QString>
#include <string>

size_t FindEquivalent(const QString& formula) {

    size_t molecules = 0;

    size_t max_tail_after_taple = 2;

    std::pair<size_t, std::string> equivalent = DBWorker::Instence().GetEquivalentFromBuffer(formula);

    if(formula.back().isDigit() && formula[formula.size() - max_tail_after_taple] == ')') {

        molecules = formula.back().digitValue();
    }
    else if(equivalent.second.front() != formula.back()){

        molecules = formula.back().digitValue();

    }

     return molecules > 1 ? equivalent.first * molecules : equivalent.first;
}

#endif // RESIDUE_FINDER_H
