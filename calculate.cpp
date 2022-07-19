
float MolarConcentration(const float molecular_weigth, const float volume_l, const float mass) {
   return mass / (molecular_weigth * volume_l);
}

float Volume(const float molecular_weigth, const float molar_concentration, const float mass) {
return mass / (molecular_weigth * molar_concentration);
}

float Mass(const float molecular_weigth, const float volume_l, const float molar_concentration) {
return molar_concentration * volume_l * molecular_weigth;
}


float MassInsertion(
    const float vector_mass,
    const float vector_lenght,
    const float ratio_l,
    const float ratio_r,
    const float lenght_insertion
) {

    float number_of_moles_of_vector = vector_mass / vector_lenght;

    int left = ratio_l;
    int right = ratio_r;

    float number_of_moles_of_an_insertion = 0;

    if (left < right) {
        number_of_moles_of_an_insertion = number_of_moles_of_vector * right;
    }
    else if (left > right) {
        number_of_moles_of_an_insertion = number_of_moles_of_vector / left;
    }
    else if (left == right) {
        number_of_moles_of_an_insertion = number_of_moles_of_vector;
    }

    return number_of_moles_of_an_insertion * lenght_insertion;
}
