#include <cilk/reducer.h>
#include <list>
#include <cassert>

template<typename State, typename Item>
class reducer_consume {
public:
    // Function that consumes an Item to update a State object.
    typedef void (*func_type)(State*,Item);
private:
    struct View {
        std::list<Item> items;
        bool is_leftmost;
        View( bool leftmost=false ) : is_leftmost(leftmost)  {}
        ~View() {}
    };

    struct Monoid: cilk::monoid_base<View> {
        State* state;
        func_type func;
        void munch( const Item& item ) const {
            func(state,item);
        }
        void reduce(View* left, View* right) const {
            assert( !right->is_leftmost );
            if( left->is_leftmost ) 
                while( !right->items.empty() ) {
                    munch(right->items.front());
                    right->items.pop_front();
                }
            else 
                left->items.splice( left->items.end(), right->items );
        }
        Monoid( State* s, func_type f ) : state(s), func(f) {}
    };

    cilk::reducer<Monoid> impl;

public:
    reducer_consume( State* s, func_type f ) : 
        impl(Monoid(s,f), /*leftmost=*/true) 
    {}

    void consume( const Item& item ) {
        View& v = impl.view();
        if( v.is_leftmost ) 
            impl.monoid().munch( item );
        else 
            v.items.push_back(item);
    }
};