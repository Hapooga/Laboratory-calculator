#ifndef CALCULATE_H
#define CALCULATE_H

float MolarConcentration(const float molecular_weigth, const float volume_l, const float mass);

float Volume(const float molecular_weigth, const float molar_concentration, const float mass);

float Mass(const float molecular_weigth, const float volume_l, const float molar_concentration);

float MassInsertion(
    const float vector_mass,
    const float vector_lenght,
    const float ratio_l,
    const float ratio_r,
    const float lenght_insertion
);

#endif // CALCULATE_H
