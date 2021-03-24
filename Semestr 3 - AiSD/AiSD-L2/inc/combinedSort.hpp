#ifndef AISD_L2_COMBINEDSORT_HPP
#define AISD_L2_COMBINEDSORT_HPP

#include <mergeSort.hpp>

template<class T>
class CombinedSort : public SortType<T> {
public:
    CombinedSort() = default;
    CombinedSort(CombinedSort const&) = delete;
    CombinedSort& (operator=(CombinedSort const&)) = delete;

    static std::shared_ptr<CombinedSort> instance() {
        static std::shared_ptr<CombinedSort> pointer = std::make_shared<CombinedSort>();
        return pointer;
    }

    void sort_typed(T* array, int length) {
        merge_sort(array, 0, length - 1);
    }

    void setThreshold(const int &t) {
        threshold = t;
    }

private:
    int threshold = 22;

    void merge_sort(T* array, const int &left, const int &right) {
        if (left >= right - threshold - 1) {
            InsertionSort<T>::instance()->setCompNum(0);
            InsertionSort<T>::instance()->setMoveNum(0);
            InsertionSort<T>::instance()->setDesc(this->isDesc());
            InsertionSort<T>::instance()->sort_typed(&array[left], (right - left + 1));

            this->setCompNum(this->getCompNum() + InsertionSort<T>::instance()->getCompNum());
            this->setMoveNum(this->getMoveNum() + InsertionSort<T>::instance()->getMoveNum());

            return;
        }
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
            (this->*(CombinedSort::move_log))(i, &tmp_left[i], left + i, array[left + i], true, true);

        for (int j = 0; j < n2; j++)
            (this->*(CombinedSort::move_log))(j, &tmp_right[j], middle + 1 + j, array[middle + 1 + j], true, false);

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if ((this->*(CombinedSort::comp_log))(i, tmp_left[i], j, tmp_right[j]))
                (this->*(CombinedSort::move_log))(k++, &array[k], i++, tmp_left[i], false, true);
            else
                (this->*(CombinedSort::move_log))(k++, &array[k], j++, tmp_right[j], false, false);
        }

        while (i < n1)
            (this->*(CombinedSort::move_log))(k++, &array[k], i++, tmp_left[i], false, true);
        while (j < n2)
            (this->*(CombinedSort::move_log))(k++, &array[k], j++, tmp_right[j], false, false);
    }

    bool (CombinedSort::*comp_log)(int i, const T &a, int j, const T &b);
    void (CombinedSort::*move_log)(int i, T* container, int j, T value, bool isSave, bool isLeft);

    void mute() {
        comp_log = &CombinedSort::comp_log_silent;
        move_log = &CombinedSort::move_log_silent;
        InsertionSort<T>::instance()->mute();
    };
    bool comp_log_silent(int i, const T &a, int j, const T &b) {
        return this->compare(a, b);
    }
    void move_log_silent(int i, T* container, int j, T value, bool isSave, bool isLeft) {
        this->move(container, value);
    }

    void unmute() {
        comp_log = &CombinedSort::comp_log_full;
        move_log = &CombinedSort::move_log_full;
        InsertionSort<T>::instance()->unmute();
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

#endif //AISD_L2_COMBINEDSORT_HPP
