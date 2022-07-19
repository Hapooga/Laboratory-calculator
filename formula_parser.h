#ifndef FORMULA_PARSER_H
#define FORMULA_PARSER_H

#include "periodic_table.h"
#include "expression_tree.h"

#include <string>
#include <string_view>
#include <memory>
#include <QString>

float ToFloat(std::string& element_atomic_weight);

std::string GetElement(std::string_view& formula, QString& error);

std::string_view CatSubFormula(std::string_view& formula, const size_t left_pose, const size_t right_pose);

bool IsIn(const std::string_view formula, const size_t pose);

std::string_view GetSubFormula(std::string_view& formula);

std::unique_ptr<Expression<float>> Parse(std::string_view& formula, std::string& error);

float ConvertToMolecularWeight(const QString& chemical_formula, QString& error);

#endif // FORMULA_PARSER_H
