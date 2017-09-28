size_t choose_number_of_bins( size_t n ) {
    const size_t BIN_CUTOFF = 1024;
    return std::min( M_MAX, size_t(1)<<floor_lg2(n/BIN_CUTOFF));
}