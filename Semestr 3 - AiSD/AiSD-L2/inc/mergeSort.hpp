#ifndef AISD_L2_MERGESORT_HPP
#define AISD_L2_MERGESORT_HPP

#include <sortType.hpp>

template<class T>
class MergeSort : public SortType<T> {
public:
    MergeSort() = default;
    MergeSort(MergeSort const&) = delete;
    MergeSort& (operator=(MergeSort const&)) = delete;

    static std::shared_ptr<MergeSort> instance() {
        static std::shared_ptr<MergeSort> pointer = std::make_shared<MergeSort>();
        return pointer;
    }

    void sort_typed(T* array, int length) {
        merge_sort(array, 0, length - 1);
    }

private:
    void merge_sort(T* array, const int &left, const int &right) {
        if (left >= right) return;
        int middle = (left + right) / 2;

        merge_sort(array, left, middle);
        merge_sort(array, ++middle, right);
        merge(array, left, --middle, right);
    }

    void merge(T* array, const int &left, const int &middle, const int &right) {

        int n1 = middle - left + 1;
        int n2 = right - middle;

        std::unique_ptr<T[]> tmp_left{new T[n1]};
        std::unique_ptr<T[]> tmp_right{new T[n2]};

        for (int i = 0; i < n1; i++)
            (this->*(MergeSort::move_log))(i, &tmp_left[i], left + i, array[left + i], true, true);

        for (int j = 0; j < n2; j++)
            (this->*(MergeSort::move_log))(j, &tmp_right[j], middle + 1 + j, array[middle + 1 + j], true, false);

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if ((this->*(MergeSort::comp_log))(i, tmp_left[i], j, tmp_right[j]))
                (this->*(MergeSort::move_log))(k++, &array[k], i++, tmp_left[i], false, true);
            else
                (this->*(MergeSort::move_log))(k++, &array[k], j++, tmp_right[j], false, false);
        }

        while (i < n1)
            (this->*(MergeSort::move_log))(k++, &array[k], i++, tmp_left[i], false, true);
        while (j < n2)
            (this->*(MergeSort::move_log))(k++, &array[k], j++, tmp_right[j], false, false);
    }

    bool (MergeSort::*comp_log)(int i, const T &a, int j, const T &b);
    void (MergeSort::*move_log)(int i, T* container, int j, T value, bool isSave, bool isLeft);

    void mute() {
        comp_log = &MergeSort::comp_log_silent;
        move_log = &MergeSort::move_log_silent;
    };
    bool comp_log_silent(int i, const T &a, int j, const T &b) {
        return this->compare(a, b);
    }
    void move_log_silent(int i, T* container, int j, T value, bool isSave, bool isLeft) {
        this->move(container, value);
    }

    void unmute() {
        comp_log = &MergeSort::comp_log_full;
        move_log = &MergeSort::move_log_full;
    };
    bool comp_log_full(int i, const T &a, int j, const T &b) {
        std::cerr << "\tComp : L[" << i << "] " << a << " ? R[" << j << "] " << b << "\n";
        return this->compare(a, b);
    }
    void move_log_full(int i, T* container, int j, T value, bool isSave, bool isLeft) {
        if (isSave)
            std::cerr << "Move : A[" << j << "] " << value << " -> " << (char)(isLeft * 'L' + !isLeft * 'R') << "[" << i << "]\n";
        else
            std::cerr << "Move : " << (char)(isLeft * 'L' + !isLeft * 'R') << "[" << j << "] " << value << " -> A[" << i << "]\n";
        this->move(container, value);
    }
};

#endif //AISD_L2_MERGESORT_HPP
