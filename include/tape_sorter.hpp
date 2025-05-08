#include "i_tape_handler.hpp"

class TapeSorter {
public:
    TapeSorter() = default;
    ~TapeSorter() = default;

    template<typename T>
    void sort(iTapeHandler<T> *th) {
        // a selection sorting algorithm is used
        for (int i = 0; i < th->tapeSize() - 1; ++i) {
            th->moveTo(i);
            int mn = th->head();
            int to_swap = i;
            for (int j = i+1; j < th->tapeSize(); ++j) {
                th->moveTo(j);
                int val = th->head();
                if (val < mn) {
                    mn = val; to_swap = j;
                }
            }
            swap(th, i, to_swap);
        }

    }

private:

    template<typename T>
    void swap(iTapeHandler<T> *th, int i, int j) {
        th->moveTo(i); int i_val = th->head();
        th->moveTo(j); int j_val = th->head();
        th->setHead(i_val);
        th->moveTo(i); th->setHead(j_val);
    }
};