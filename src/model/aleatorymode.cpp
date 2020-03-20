#include "aleatorymode.h"

Mode_Aleatory_Flags &operator^=(Mode_Aleatory_Flags &lhs, Mode_Aleatory_Flags rhs)
{
    lhs = static_cast<Mode_Aleatory_Flags> (
                static_cast<int>(lhs) ^
                static_cast<int>(rhs)
                );

    return lhs;
}

Mode_Aleatory_Flags &operator&=(Mode_Aleatory_Flags &lhs, Mode_Aleatory_Flags rhs)
{
    lhs = static_cast<Mode_Aleatory_Flags> (
                static_cast<int>(lhs) &
                static_cast<int>(rhs)
                );

    return lhs;
}

Mode_Aleatory_Flags operator&(Mode_Aleatory_Flags lhs, Mode_Aleatory_Flags rhs)
{
    return static_cast<Mode_Aleatory_Flags> (
                static_cast<int>(lhs) &
                static_cast<int>(rhs)
                );
}

Mode_Aleatory_Flags operator^(Mode_Aleatory_Flags lhs, Mode_Aleatory_Flags rhs)
{
    return static_cast<Mode_Aleatory_Flags> (
                static_cast<int>(lhs) ^
                static_cast<int>(rhs)
                );
}

Mode_Aleatory_Flags operator~(Mode_Aleatory_Flags rhs)
{
    return static_cast<Mode_Aleatory_Flags> (
                ~static_cast<int>(rhs)
                );
}

Mode_Aleatory_Flags &operator|=(Mode_Aleatory_Flags &lhs, Mode_Aleatory_Flags rhs)
{
    lhs = static_cast<Mode_Aleatory_Flags> (
                static_cast<int>(lhs) |
                static_cast<int>(rhs)
                );

    return lhs;
}

Mode_Aleatory_Flags operator|(Mode_Aleatory_Flags lhs, Mode_Aleatory_Flags rhs)
{
    return static_cast<Mode_Aleatory_Flags>(
                static_cast<int>(lhs) |
                static_cast<int>(rhs)
                );
}
