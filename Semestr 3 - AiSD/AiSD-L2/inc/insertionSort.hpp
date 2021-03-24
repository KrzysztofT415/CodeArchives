#ifndef AISD_L2_INSERTIONSORT_HPP
#define AISD_L2_INSERTIONSORT_HPP

#include <sortType.hpp>

template<class T>
class InsertionSort : public SortType<T> {
public:
    InsertionSort() = default;
    InsertionSort(InsertionSort const&) = delete;
    InsertionSort& (operator=(InsertionSort const&)) = delete;

    static std::shared_ptr<InsertionSort> instance() {
        static std::shared_ptr<InsertionSort> pointer = std::make_shared<InsertionSort>();
        return pointer;
    }

    void sort_typed(T* array, int length) {
        std::unique_ptr<T> key{new T};
        int i;
        for (int j = 1; j < length; ++j) {
            (this->*(InsertionSort::move_log))(-1, key.get(), j, array[j]);

            i = j - 1;
            while (i >= 0 && !(this->*(InsertionSort::comp_log))(i, array[i], *key.get())) {
                (this->*(InsertionSort::move_log))(i + 1, &array[i + 1], i, array[i]);
                i = i - 1;
            }
            (this->*(InsertionSort::move_log))(i + 1, &array[i + 1], -1, *key.get());
        }
    };

    void mute() {
        comp_log = &InsertionSort::comp_log_silent;
        move_log = &InsertionSort::move_log_silent;
    };
    void unmute() {
        comp_log = &InsertionSort::comp_log_full;
        move_log = &InsertionSort::move_log_full;
    };

private:
    bool (InsertionSort::*comp_log)(int i, const T &value, const T &key);
    void (InsertionSort::*move_log)(int j, T* container, int i, T value);

    bool comp_log_silent(int i, const T &value, const T &key) {
        return this->compare(value, key);
    }
    void move_log_silent(int j, T* container, int i, T value) {
        this->move(container, value);
    }

    bool comp_log_full(int i, const T &value, const T &key) {
        std::cerr << "\tComp : KEY " << key << " ? A[" << i << "] " << value << "\n";
        return this->compare(value, key);
    }
    void move_log_full(int j, T* container, int i, T value) {
        if (j == -1)
            std::cerr << "Move : A[" << i << "] " << value << " -> KEY\n";
        else if (i == -1)
            std::cerr << "Move : KEY " << value << " -> A[" << j << "]\n";
        else
            std::cerr << "Move : A[" << i << "] " << value << " -> A[" << j << "]\n";
        this->move(container, value);
    }
};

#endif //AISD_L2_INSERTIONSORT_HPP
