#ifndef AISD_L2_SORTER_HPP
#define AISD_L2_SORTER_HPP

#include <utility>
#include <functional>

#include <sortType.hpp>
#include <insertionSort.hpp>
#include <mergeSort.hpp>
#include <quickSort.hpp>
#include <dualPivotQuickSort.hpp>
#include <combinedSort.hpp>

template <class T>
class Sorter {
public:
    explicit Sorter(std::function<T (const int&)> randomElementFunction)
            : randomElement(std::move(randomElementFunction)) { };

    // OPTION 1 EXECUTION

    void runAutomatedTest(const bool &desc, const int &k) {

        std::string types[] = {"insertion", "merge", "quick", "dp_quick", "combined"};

        for (int n = 100; n <= 10000; n += 100) {
            for (int i = 0; i < k; ++i) {

                std::unique_ptr<T[]> arrayArch = generateArray(n);

                for (const std::string &type : types) {

                    std::cerr << "n : " << n << ";  type : " << type.c_str() << ";\t";
                    (*pickSortType(type)).sort(copyArray(arrayArch, n).get(), n, desc, true);
                    std::cerr << "\n";
                }
            }
        }
    }

    // OPTION 2 EXECUTION

    void runSpecifiedTest(const std::string &type, T* array, const int &size, const bool &desc) {
        std::cerr << "\n>> " << type.c_str() << " sort <<\n";

        std::shared_ptr<SortType<T>> sortType = pickSortType(type);
        if (type == "combined") {
            std::cout << "Pick threshold :";
            int t;
            std::cin >> t;
            CombinedSort<T>::instance()->setThreshold(t);
        }

        std::cerr << " before ";
        printArray(array, size);

        (*sortType).sort(array, size, desc, false);

        std::cerr << "\n after ";
        printArray(array, size);

        std::cerr << "   should be in " << (desc ? "'>=' descending" : "'<=' ascending") << " order -> checked and it is "
                << (checkArray(array, size, desc) ? "correct" : "not correct") << "\n";
    }

    void runEx1() {
        FILE* stream;
        errno_t err = freopen_s(&stream, "../ex1_full.txt", "w", stderr);

        if (err != 0) {
            std::cout << "error on opening save file\n";
            return;
        }
        int size[] {10, 50, 100};
        for (int n : size) {
            std::string types[] = {"insertion", "merge", "quick", "dp_quick"};
            std::unique_ptr<T[]> arrayArch = generateArray(n);

            // RANDOM
            for (const std::string &type : types) {
                runSpecifiedTest(type, copyArray(arrayArch, n).get(), n, false);
            }
            runSpecifiedTest("combined", arrayArch.get(), n, false);

            // IN ORDER
            for (const std::string &type : types) {
                runSpecifiedTest(type, copyArray(arrayArch, n).get(), n, false);
            }
            runSpecifiedTest("combined", arrayArch.get(), n, false);

            // OPPOSITE ORDER
            for (const std::string &type : types) {
                runSpecifiedTest(type, copyArray(arrayArch, n).get(), n, true);
            }
            runSpecifiedTest("combined", arrayArch.get(), n, true);
        }
        fclose(stream);
    }

    void runEx3() {
        FILE* stream;
        errno_t err = freopen_s(&stream, "../ex3.txt", "w", stderr);

        if (err != 0) {
            std::cout << "error on opening save file\n";
            return;
        }
        for (int n = 100; n <= 10000; n += 100) {
            std::unique_ptr<T[]> arrayArch = generateArray(n);

            std::cerr << "n : " << n << ";  type : quick;   \t";
            (*pickSortType("quick")).sort(copyArray(arrayArch, n).get(), n, false, true);
            std::cerr << "\n";

            std::cerr << "n : " << n << ";  type : dp_quick;\t";
            (*pickSortType("dp_quick")).sort(arrayArch.get(), n, false, true);
            std::cerr << "\n";
        }
        fclose(stream);
    }

    void runEx4(const std::string &type) {
        FILE* stream;
        std::string file_str = "../ex4_";
        file_str += type;
        file_str += ".txt";
        errno_t err = freopen_s(&stream, file_str.c_str(), "w", stderr);

        if (err != 0) {
            std::cout << "error on opening save file\n";
            return;
        }

        std::shared_ptr<InsertionSort<T>> insert = InsertionSort<T>::instance();
        std::shared_ptr<MergeSort<T>> merge = MergeSort<T>::instance();
        std::shared_ptr<CombinedSort<T>> comb = CombinedSort<T>::instance();

        for (int n = 100; n <= 10000; n += 100) {
            std::unique_ptr<T[]> arrayArch = generateArray(n);

            std::cerr << "\nn : " << n << ";  type : insertion;\t";
            insert->sort(copyArray(arrayArch, n).get(), n, false, true);

            for (int t = n; t >= 2; t /= 2) {
                std::cerr << "\nn : " << n << ";  type : combined;\t";
                comb->setThreshold(t);
                comb->sort(copyArray(arrayArch, n).get(), n, false, true);
                std::cerr << ";\t t : " << t;
            }
            std::cerr << "\nn : " << n << ";  type : merge;    \t";
            merge->sort(arrayArch.get(), n, false, true);
        }

        fclose(stream);
    }

    std::unique_ptr<T[]> generateArray(const int &size) {
        std::unique_ptr<T[]> array = std::make_unique<T[]>(size);
        for (int i = 0; i < size; ++i)
            array[i] = randomElement(size < 40 ? 40 : 2 * size);
        return array;
    }

    std::unique_ptr<T[]> cinArray(const int &size) {
        std::unique_ptr<T[]> array = std::make_unique<T[]>(size);
        for (int i = 0; i < size; ++i)
            std::cin >> array[i];
        return array;
    }

    std::unique_ptr<T[]> copyArray(const std::unique_ptr<T[]> &array, const int &size) {
        std::unique_ptr<T[]> array_copy = std::make_unique<T[]>(size);
        for (int i = 0; i < size; ++i)
            array_copy[i] = array[i];
        return array_copy;
    }

    void printArray(T* array, const int &size) {
        std::cerr << "array [" << size << "] : ";
        for (int i = 0; i < size; ++i)
            std::cerr << array[i] << " ";
        std::cerr << std::endl;
    }

    bool checkArray(T* array, const int &size, const bool &desc) {
        for (int i = 0; i < size - 1; ++i)
            if (desc * (array[i] < array[i + 1]) + !desc * (array[i] > array[i + 1])) return false;
        return true;
    }

private:
    std::function<T (const int&)> randomElement;

    std::shared_ptr<SortType<T>> pickSortType(const std::string &type) {
        if (type == "insertion") return InsertionSort<T>::instance();
        if (type == "merge") return MergeSort<T>::instance();
        if (type == "quick") return QuickSort<T>::instance();
        if (type == "dp_quick") return DPQuickSort<T>::instance();
        if (type == "combined") return CombinedSort<T>::instance();

        std::cerr << "UNRECOGNIZED TYPE OF SORTING - QuickSort chosen as default\n";
        return QuickSort<T>::instance();
    }
};

#endif //AISD_L2_SORTER_HPP
