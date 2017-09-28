/*
    Copyright (c) 2012, Intel Corporation
    All rights reserved.

    Redistribution and use in source and binary forms, with or without 
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this 
      list of conditions and the following disclaimer.  
      
    * Redistributions in binary form must reproduce the above copyright notice, 
      this list of conditions and the following disclaimer in the documentation 
      and/or other materials provided with the distribution.

    * Neither the name of the Intel Corporation nor the names of its contributors 
      may be used to endorse or promote products derived from this software without 
      specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Program for ngram generation.
//
// Usage:
// 	ngram [-n] [-v] count [inputfile [outputfile]]\n", argv[0]);
//
// where count is a non-negative integer written as decimal numeral.  
// The output is a file of count characters where the statistical
// distribution of ngrams matches the input file's distribution.
// 
// The value of N is a program-specified constant.
// N=3 gives you text that looks like Jabberwocky.
// N=4 gives you incoherent text with words that look mostly real.
//
// The program will announce if it gets stuck ("terminal state").
// If that happens, try a bigger input file.
// An input file of at least 100 KBytes of text seems to work well.
// 
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>
#include <cstdio>

// The N in "ngram".
const size_t N = 4;

// Global options
int noclobber = 0;
int verbose = 0;

// "Random" number generator that is consistent across platforms with 32-bit unsigned
unsigned Rand32() {
    // Linear congruential number generator, mod 2^32.
    static unsigned state = 0;
    const unsigned a = 0x41c64e6d;  // Must be equal to 1 modulo 4 
    const unsigned c = 0x3039;
    state = a*state+c;
    // Because of the way Rand32 is used, the less predicatble bits should be in the 
    // low-order portion, otherwise the automaton is more likely to get caught in a 
    // cycle when there is a power-of-two choices.  
    return state>>24|state<<8;
}

// A sequence of N characters
class N_Gram {
    char my_char[N];
public:
    // Append c to end and erase first character
    void shift( char c ) {
        for( size_t i=0; i<N-1; ++i )
            my_char[i] = my_char[i+1];
        my_char[N-1] = c;
    }
    // Lexicograph order on n-grams.
    friend bool operator<( const N_Gram& x, const N_Gram& y ) {
        return std::memcmp( x.my_char, y.my_char, N )<0;
    }
    void put() const {
        for( int i=0; i<N; ++i ) 
            putchar(my_char[i]);
    }
};

struct Item: N_Gram {
    char next;
};

typedef std::vector<Item> TableType;
TableType Table;

struct State {
    unsigned index;
    unsigned next:8;
    unsigned size:24;
};
 
typedef std::vector<State> AutomataType;
AutomataType Automata;

void usage( int argc, char* argv[]) {
    fprintf(stderr,"usage: %s [-n] [-v] count [inputfile [outputfile]]\n", argv[0]);
    std::exit(1);
}

int main( int argc, char* argv[] ) {
    int argbase = 1;

    if( argc<2 ) {
        usage( argc, argv );
    }

    while (*argv[argbase] == '-') {
        if (strcmp(argv[argbase], "-n") == 0) {
            noclobber = 1;
            ++argbase;
        }
        else if (strcmp(argv[argbase], "-v") == 0) {
            verbose = 1;
            ++argbase;
        }
        else
            usage( argc, argv );
    }

    if (*argv[argbase] < '0' | *argv[argbase] > '9') {
        usage( argc, argv );
    }

    long n = strtol(argv[argbase++],0,10);

    // Open input file
    FILE* input = stdin;
    if( argc>argbase ) {
        input = fopen(argv[argbase],"rb");
        if( !input ) {
            fprintf(stderr,"%s: cannot open input file %s\n",argv[0], argv[argbase]);
            exit(1);
        }
        ++argbase;
    }

    // Open output file
    FILE* output = stdout;
    if( argc>argbase ) {
        if (noclobber) {
            output = fopen(argv[argbase], "rb");
            if (output != 0) {
                fclose( output );
                if ( verbose ) {
                    fprintf(stderr,"%s: will not overwrite output file %s\n",argv[0], argv[argbase]);
                }
                exit(0);
            }
        }

        output = fopen(argv[argbase],"wb");
        if( !output ) {
            fprintf(stderr,"%s: cannot open output file %s\n",argv[0], argv[argbase]);
            exit(1);
        }
        ++argbase;
    }

    if( argc>argbase ) {
        usage( argc, argv );
    }

    // Read input file
    Item g;
    int k = 0;
    int wrap[N+1];
    wrap[N] = EOF;
    int c;
    while( k<N && (c=getc(input))!=EOF ) {
        g.shift( c );
        wrap[k++]=c;
    }
    if( k!=N ) {
        fprintf(stderr,"input too short\n");
        exit(1);
    }
    k = 0;
    while( (c=getc(input))!=EOF || (c=wrap[k++])!=EOF ) {
        g.next = c;
        Table.push_back(g);
        g.shift( c );
    }    
    if( input!=stdin ) 
        fclose(input);

    // Sort ngrams
    std::stable_sort( Table.begin(), Table.end() );

    // Generate automaton
    for( TableType::iterator i=Table.begin(); i!=Table.end(); ++i ) {
        g = *i;
        g.shift(g.next);
        std::pair<TableType::iterator,TableType::iterator> range = std::equal_range( Table.begin(), Table.end(), g );
        State s;
        s.next = g.next;
        s.index = range.first-Table.begin();
        s.size = range.second-range.first;
        Automata.push_back(s);
    }

    // Generate output by running automaton.
    unsigned i = Rand32() % Automata.size();
    for( long j=0; j<n; ++j ) {
        State s = Automata[i];
        putc(s.next,output); 
        i = s.index + Rand32() % s.size;
    }

    // Close output file
    if( output!=stdout ) 
        fclose(output);

    return 0;
}
