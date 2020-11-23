#ifdef INT_2_BYTES
    using int8_t = char;
    using int16_t = int;
    using int32_t = long;
#else
    using int8_t = char;
    using int16_t = short;
    using int32_t = int;
#endif

// that's also why int8_t is usually printed as char