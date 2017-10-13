class InputState {
public:
    InputState() : prev_state_char(256), prev_state_len(0), nbytes_in(0), buf_ptr(NULL), buf_end(NULL) {}
    void getOneBlock(FILE* inputFile, EState* s);
    // Volume of uncompressed data
    off_t nbytes_in;
private:
    // Values carried between instances of EState
    UInt32 prev_state_char;
    Int32 prev_state_len;
    // Field and routine related to buffering input.
    UChar *buf_ptr;
    UChar *buf_end;
    UChar buf[8192];
    void copy_input_until_stop( EState* s, FILE* infile );
};

// Some of the methods use macros defined in bzlib.cpp.
// So instead of putting these methods in a separate .cpp file,
// they are compiled as part of bzlib.cpp.

#if IMPLEMENT_InputState
void InputState::getOneBlock(FILE* inputFile, EState* s) {
    // Carry information from previous EState
    s->state_in_ch = prev_state_char;
    s->state_in_len = prev_state_len;

    copy_input_until_stop( s, inputFile );

    // Remember information to be carried to next EState
    prev_state_char = s->state_in_ch;
    prev_state_len = s->state_in_len;

    // Accumulate total input volume
    nbytes_in += s->nblock;
}

void InputState::copy_input_until_stop( EState* s, FILE* infile ) {
    do {
        if( buf_ptr==buf_end ) {
            size_t n = fread( buf, 1, sizeof(buf), infile );
            if ( n==0 ) {
                flush_RL ( s );    // empty state buffer
                break;
            }
            buf_ptr = buf;
            buf_end = buf+n;
        }
        ADD_CHAR_TO_BLOCK( s, (int)*buf_ptr++ );
    } while( s->nblock < s->nblockMAX );
}
#endif /* IMPLEMENT_InputState */
