template<typename T>
class temp_space {
    static const size_t n = 4096/sizeof(T);
    T temp[n];
    T* base;
public:
    T* data() {return base;}
    T& operator[]( size_t k ) {return base[k];}
    temp_space( size_t size ) {
        base = size<=n ? temp : new T[size];
    }
    ~temp_space() {
        if( base!=temp ) 
            delete[] base;
    }
};