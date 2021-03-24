#ifndef AISD_L2_QUICKSORT_HPP
#define AISD_L2_QUICKSORT_HPP

#include <sortType.hpp>

template<class T>
class QuickSort : public SortType<T> {
public:
    QuickSort() = default;
    QuickSort(QuickSort const&) = delete;
    QuickSort& (operator=(QuickSort const&)) = delete;

    static std::shared_ptr<QuickSort> instance() {
        static std::shared_ptr<QuickSort> pointer = std::make_shared<QuickSort>();
        return pointer;
    }

    void sort_typed(T* array, int length) {
        quick_sort(array, 0, length - 1);
    }

private:
    void quick_sort(T* array, int left, int right) {
        if (left >= right) return;

        T* pivot = &array[right];
        (this->*(QuickSort::save_log))(right, array[right]);

        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (!(this->*(QuickSort::comp_log))(j, *pivot, array[j])) {
                i++;
                if (i != j)
                    (this->*(QuickSort::swap_log))(i, array[i], j, array[j], false);
            }
        }
        if (i + 1 != right)
            (this->*(QuickSort::swap_log))(i + 1, array[i + 1], right, array[right], true);

        quick_sort(array, left, i);
        quick_sort(array, i + 2, right);
    }

    bool (QuickSort::*comp_log)(int i, const T &a, const T &b);
    void (QuickSort::*save_log)(const int &j, const T &value);
    void (QuickSort::*swap_log)(int i, T &a, int j, T &b, bool pivot);

    void mute() {
        comp_log = &QuickSort::comp_log_silent;
        save_log = &QuickSort::save_log_silent;
        swap_log = &QuickSort::swap_log_silent;
    };
    bool comp_log_silent(int i, const T &a, const T &b) {
        return this->compare(a, b);
    }
    void save_log_silent(const int &j, const T &value) {}
    void swap_log_silent(int i, T &a, int j, T &b, bool pivot) {
        this->swap(a, b);
    }

    void unmute() {
        comp_log = &QuickSort::comp_log_full;
        save_log = &QuickSort::save_log_full;
        swap_log = &QuickSort::swap_log_full;
    };
    bool comp_log_full(int i, const T &a, const T &b) {
        std::cerr << "\tComp : PIVOT " << b << " ? A[" << i << "] " << a << "\n";
        return this->compare(a, b);
    }
    void save_log_full(const int &j, const T &value) {
        std::cerr << "\t\tSave : A[" << j << "] " << value << " -> PIVOT\n";
    }
    void swap_log_full(int i, T &a, int j, T &b, bool pivot) {
        std::cerr << "Swap : A[" << i << "] " << a << " <-> A[" << j << "] " << b << (pivot ? " ~ PIVOT" : "") << "\n";
        this->swap(a, b);
    }
};

#endif //AISD_L2_QUICKSORT_HPP