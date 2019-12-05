enum
{
    MAX_NUMBER_MULT = 8
};

STYPE
bit_reverse(STYPE value)
{
    UTYPE unsignedValue = (UTYPE) value;
    int stype_size = sizeof(unsignedValue);
    UTYPE returnValue = 0;
    for (int i = 0; i < stype_size * MAX_NUMBER_MULT; i++) {
        returnValue = returnValue | ((unsignedValue >> i) & 1) << (stype_size * 8 - i - 1);
    }

    return (STYPE) returnValue;
}
