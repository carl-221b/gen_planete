#ifndef ALEATORYMODE_H
#define ALEATORYMODE_H

#include <iostream>

/**
 * @brief Flags in oder to decide the application of aleatory in editor parameters.
 */
enum Mode_Aleatory_Flags
{
    NO_ALEATORY         = 0,
    ALEA_OCTAVE         = 1 << 0,
    ALEA_FREQUENCE      = 1 << 1,
    ALEA_PERSISTENCE    = 1 << 2,
    ALEA_SEED           = 1 << 3,
};

//Bitwise operators

Mode_Aleatory_Flags operator |(Mode_Aleatory_Flags lhs, Mode_Aleatory_Flags rhs);

Mode_Aleatory_Flags operator &(Mode_Aleatory_Flags lhs, Mode_Aleatory_Flags rhs);

Mode_Aleatory_Flags operator ^(Mode_Aleatory_Flags lhs, Mode_Aleatory_Flags rhs);

Mode_Aleatory_Flags operator ~(Mode_Aleatory_Flags rhs);

Mode_Aleatory_Flags& operator |=(Mode_Aleatory_Flags &lhs, Mode_Aleatory_Flags rhs);

Mode_Aleatory_Flags& operator &=(Mode_Aleatory_Flags &lhs, Mode_Aleatory_Flags rhs);

Mode_Aleatory_Flags& operator ^=(Mode_Aleatory_Flags &lhs, Mode_Aleatory_Flags rhs);


#endif // ALEATORYMODE_H
