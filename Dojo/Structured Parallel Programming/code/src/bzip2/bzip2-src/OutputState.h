class OutputState {
public:
    bitblock carry;
    uint64_t total;
    uint32_t combinedCRC; // reduced(combined) CRC
    FILE* zStream;

    OutputState( FILE* zStream_ );
    void putOneBlock( EState* s);
    void write( const unsigned char *data, unsigned int length, const bitblock overflow);
    void flush();
};
OutputState::OutputState( FILE* zStream_ ) :
    combinedCRC(0), carry(bitblock()), total(32), zStream(zStream_) {}

void OutputState::write(const unsigned char *data, unsigned int length, const bitblock overflow) {
    // update total bits written
    total += (length * 8) + (overflow.numbits);
    
    assert(zStream);
    const int align_in = carry.numbits;
    if (align_in == 0) { // no carry from the previous block
        fwrite_force(zStream, data, length);
        carry = overflow;
        return;
    }

    unsigned char buf[1024];
    int c = carry.bits;
    for (unsigned int i = 0; i < length / sizeof buf; i++) {
        c = copy_shift(buf, bitblock(c, align_in), data, sizeof buf);
        fwrite_force(zStream, buf, sizeof buf);
        data += sizeof buf;
    }
    if (length % sizeof(buf)) {
        c = copy_shift(buf, bitblock(c, align_in), data, length % sizeof(buf));
        fwrite_force(zStream, buf, length % sizeof(buf));
    }
    c = (c << 8) | (overflow.bits << (8 - align_in));
    const int new_align = align_in + overflow.numbits;
    if (new_align > 7) {
        fputc(c >> 8, zStream);
        carry = bitblock(c & 255, new_align & 7);
    } else {
        carry = bitblock(c >> 8, new_align & 7);
    }
}

void OutputState::flush() {
    assert(zStream);
    if (carry.numbits) fputc(carry.bits, zStream);
}

void OutputState::putOneBlock( EState* s ) {
    // CRC reduction
    combinedCRC = (combinedCRC << 1) | (combinedCRC >> 31);
    combinedCRC ^= s->blockCRC;

    // write to file
    write( s->zbits, s->numZ, bitblock(s->bsBuff >> 24, s->bsLive));
}
