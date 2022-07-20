#ifndef PERIODIC_TABLE_H
#define PERIODIC_TABLE_H

#include <map>
#include <string>

class PeriodicTable {
public:

    static PeriodicTable& Instence() {
        static PeriodicTable periodic_table;
        return periodic_table;
    }

    float GetAtomicWeightFromClass(const std::string& element) const {

        auto it = periodic_table.find(element);

        if(it != periodic_table.end()){

            return it->second;

        }

        return 0;
    }

    PeriodicTable(const PeriodicTable& other) = delete;

    PeriodicTable& operator = (const PeriodicTable& other) = delete;

private:

    PeriodicTable() = default;

    const std::map<std::string, float> periodic_table{
    {"Ac",227 },      { "Ag",107.868 },  { "Al",26.9815 }, { "Am",243.06 },   { "Ar",39.948 },
    { "As",74.992 },  { "At",209.99 },   { "Au",196.967 }, { "B",10.811 },    { "Ba",137.33 },
    { "Be",9.0122 },  { "Bh",262 },      { "Bi",208.98 },  { "Bk",247.07 },   { "Br",79.904 },
    { "C",12.011 },   { "Ca",40.08 },    { "Cd",112.41 },  { "Ce",140.12 },   { "Cf",251.08 },
    { "Cl",35.453 },  { "Cm",247.07 },   { "Co",58.933 },  { "Cr",51.996 },   { "Cs",132.905 },
    { "Cu",63.546 },  { "Db",262 },      { "Dy",162.5 },   { "Er",167.26 },   { "Es",252.08 },
    { "Eu",151.96 },  { "F",18.998 },    { "Fe",55.847 },  { "Fm",257.1 },    { "Fr",223 },
    { "Ga",69.72 },   { "Gb",157.25 },   { "Ge",72.59 },   { "H",1.00794 },   { "He",4.002602 },
    { "Hf",178.49 },  { "Hg",200.59 },   { "Ho",164.93 },  { "Hs",265 },      { "I",126.9045 },
    { "In",114.82 },  { "Ir",192.22 },   { "K",39.098 },   { "Kr",83.8 },     { "La",138.9055 },
    { "Li",6.941 },   { "Lr",260.1 },    { "Lu",174.967 }, { "Md",258.1 },    { "Mg",24.305 },
    { "Mn",54.938 },  { "Mo",95.94 },    { "Mt",266 },     { "N",14.007 },    { "Na",22.99 },
    { "Nb",92.906 },  { "Nd",144.24 },   { "Ne",20.179 },  { "Ni",58.7 },     { "No",259.1 },
    { "Np",237.05 },  { "O",15.999 },    { "Os",190.2 },   { "P",30.974 },    { "Pa",231.04 },
    { "Pb",207.19 },  { "Pd",106.4 },    { "Pm",144.91 },  { "Po",209.98 },   { "Pr",140.908 },
    { "Pt",195.08 },  { "Pu",244.06 },   { "Ra",226 },     { "Rb",85.468 },   { "Re",186.207 },
    { "Rf",261 },     { "Rh",102.906 },  { "Rn",222 },     { "Ru",101.07 },   { "S",32.066 },
    { "Sb",121.75 },  { "Sc",44.956 },   { "Se",78.96 },   { "Sg",263 },      { "Si",28.086 },
    { "Sm",150.36 },  { "Sn",118.71 },   { "Sr",87.62 },   { "Ta",180.9479 }, { "Tb",158.926 },
    { "Tc",97.91 },   { "Te",127.6 },    { "Th",232.038 }, { "Ti",47.9 },     { "Tl",204.38 },
    { "Tm",168.934 }, { "U",238.03 },    { "V",50.941 },   { "W",183.85 },    { "Xe",131.29 },
    { "Y",88.906 },   { "Yb",173.04 },   { "Zn",65.39 },   { "Zr",91.22 }
    };
};

#endif // PERIODIC_TABLE_H
