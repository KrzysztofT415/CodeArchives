#ifndef AISD_L2_DUALPIVOTQUICKSORT_HPP
#define AISD_L2_DUALPIVOTQUICKSORT_HPP

#include <sortType.hpp>

template<class T>
class DPQuickSort : public SortType<T> {
public:
    DPQuickSort() = default;
    DPQuickSort(DPQuickSort const&) = delete;
    DPQuickSort& (operator=(DPQuickSort const&)) = delete;

    static std::shared_ptr<DPQuickSort> instance() {
        static std::shared_ptr<DPQuickSort> pointer = std::make_shared<DPQuickSort>();
        return pointer;
    }

    void sort_typed(T* array, int length) {
        dp_quick_sort(array, 0, length - 1);
    }

private:
    void dp_quick_sort(T* array, int left, int right) {
        if (left >= right) return;

        if (!(this->*(DPQuickSort::comp_log))(left, array[left], right, array[right], false))
            (this->*(DPQuickSort::swap_log))(left, array[left], right, array[right]); // if (A[left] > A[right]) swap(A[left], A[right]);

        T* p = &array[left];
        T* q = &array[right];
        (this->*(DPQuickSort::save_log))(left, array[left], right, array[right]);

        int l = left + 1, g = right - 1;
        int l_c = 0, s_c = 0;

        for (int k = l; k <= g; ++k) {
            std::cerr << l_c << " " << s_c;
            if ((l_c > s_c) && (this->*(DPQuickSort::comp_log))(-1, *q, k, array[k], false)) { // if (A[k] >= q)
                ++l_c;
                while (!(this->*(DPQuickSort::comp_log))(g, array[g], -1, *q, false) && k < g) --g; // while (A[g] > q && k < g) g--;

                (this->*(DPQuickSort::swap_log))(k, array[k], g--, array[g]); // swap(A[k], A[g]); g--;
                if (!(this->*(DPQuickSort::comp_log))(-1, *p, k, array[k], true))
                    (this->*(DPQuickSort::swap_log))(k, array[k], l++, array[l]); // if (A[k] < *p) swap(A[k], A[l]); l++;
            }

            else if (!(this->*(DPQuickSort::comp_log))(-1, *p, k, array[k], true)) { // if (A[k] < p)
                (this->*(DPQuickSort::swap_log))(k, array[k], l++, array[l]);// swap(A[k], A[l]);
                ++s_c;
            }

            else if ((this->*(DPQuickSort::comp_log))(-1, *q, k, array[k], false)) { // if (A[k] >= q)
                ++l_c;
                while (!(this->*(DPQuickSort::comp_log))(g, array[g], -1, *q, false) && k < g) --g; // while (A[g] > q && k < g) g--;

                (this->*(DPQuickSort::swap_log))(k, array[k], g--, array[g]); // swap(A[k], A[g]); g--;
                if (!(this->*(DPQuickSort::comp_log))(-1, *p, k, array[k], true))
                    (this->*(DPQuickSort::swap_log))(k, array[k], l++, array[l]); // if (A[k] < *p) swap(A[k], A[l]); l++;
            }
        }

        (this->*(DPQuickSort::swap_log))(left, array[left], l, array[--l]); // l--; swap(A[left], A[l]);
        (this->*(DPQuickSort::swap_log))(right, array[right], g, array[++g]); // g++; swap(A[right], A[g]);

        dp_quick_sort(array, left, l - 1);
        dp_quick_sort(array, l + 1, g - 1);
        dp_quick_sort(array, g + 1, right);
    }

    bool (DPQuickSort::*comp_log)(int i, const T &a, int j, const T &b, bool isLeft);
    void (DPQuickSort::*save_log)(const int &i, const T &left, const int &j, const T &right);
    void (DPQuickSort::*swap_log)(int i, T &a, int j, T &b);

    void mute() {
        comp_log = &DPQuickSort::comp_log_silent;
        save_log = &DPQuickSort::save_log_silent;
        swap_log = &DPQuickSort::swap_log_silent;
    };
    bool comp_log_silent(int i, const T &a, int j, const T &b, bool isLeft) {
        return this->compare(a, b);
    }
    void save_log_silent(const int &i, const T &left, const int &j, const T &right) {}
    void swap_log_silent(int i, T &a, int j, T &b) {
        this->swap(a, b);
    }

    void unmute() {
        comp_log = &DPQuickSort::comp_log_full;
        save_log = &DPQuickSort::save_log_full;
        swap_log = &DPQuickSort::swap_log_full;
    };
    bool comp_log_full(int i, const T &a, int j, const T &b, bool isLeft) {
        if (i == -1) std::cerr << "\tComp : A[" << j << "] " << b << " ? piv_" << (isLeft ? "P " : "Q ") << a << "\n";
        else if (j == -1) std::cerr << "\tComp : A[" << i << "] " << a <<  " ? piv_Q " << b << "\n";
        else std::cerr << "\tComp : A[" << i << "] " << a << " ? A[" << j << "] " << b << "\n";
        return this->compare(a, b);
    }
    void save_log_full(const int &i, const T &left, const int &j, const T &right) {
        std::cerr << "\t\tSave : A[" << i << "] " << left << " -> piv_P\n"
                  << "\t\tSave : A[" << j << "] " << right << " -> piv_Q\n";
    }
    void swap_log_full(int i, T &a, int j, T &b) {
        std::cerr << "Swap : A[" << i << "] " << a << " <-> A[" << j << "] " << b << "\n";
        this->swap(a, b);
    }
};

#endif //AISD_L2_DUALPIVOTQUICKSORT_HPP
