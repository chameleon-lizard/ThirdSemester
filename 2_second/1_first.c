int
bitcount(STYPE value)
{
    int count = 0;

    UTYPE unsigned_value = (UTYPE) value;

    while (unsigned_value != 0) {
        count += unsigned_value & 1;
        unsigned_value = unsigned_value >> 1;
    }

    return count;
}
