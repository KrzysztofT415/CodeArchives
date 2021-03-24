#include <iostream>
#include <chrono>

#include <sorter.hpp>
#include <point2d.hpp>

// METHODS USED BY SORTER

#define DEFAULT_TYPE "insertion"
#define DEFAULT_COMP false

int randInt(const int &size) {
    return rand() % size;
}

std::string randString(const int &size) {
    int len = rand() % 10 + 4;
    std::string word;
    for (int j = 0; j < len; j++)
        word += char(rand() % 25 + 97);
    return word;
}

// MAIN TESTING SORTER

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    // DEFAULT INIT
    std::string type_string = DEFAULT_TYPE;
    bool desc = DEFAULT_COMP;

//    Sorter<Point2D<double>> sorter(Point2D<double>::randDouble);
//    Sorter<std::string> sorter(randString);
    Sorter<int> sorter(randInt);

//    sorter.runEx4("int_nto2");
//    return 1;

    const char* type = nullptr, *comp = nullptr, *file = nullptr, *k_str = nullptr;

    // PARSING ARGUMENTS

    for (int i = 1; i < argc; ++i) {
        if (i + 1 != argc) {
            if (strcmp(argv[i], "--type") == 0) {
                type = argv[i + 1];
                i++;
            }
            else if (strcmp(argv[i], "--comp") == 0) {
                comp = argv[i + 1];
                i++;
            }
            else if (strcmp(argv[i], "--stat") == 0) {
                if (i + 2 != argc) {
                    file = argv[i + 1];
                    k_str = argv[i + 2];
                    i += 2;
                }
            }
        }
    }

    if (comp && comp == std::string("'>='")) desc = true;

    // OPTION 1 : REDIRECT STDERR TO FILE AND RUN AUTOMATED TESTING ({k} times, for each sortType, for size 1000 <+100> - 10000, printed to {file})

    if (k_str && file) {
        const int k = strtol(std::string(k_str).c_str(), nullptr, 0);

        FILE* stream;
        std::string file_str = "../";
        file_str += file;
        errno_t err = freopen_s(&stream, file_str.c_str(), "w", stderr);

        if (err != 0) {
            std::cout << "error on opening save file\n";
            return MATH_ERRNO;
        }

        std::cout << "STARTED TESTING\n Output >> " << file << " | each sort " << k << " times " << (desc ? "descending" : "ascending") << "\n";

        auto t1 = std::chrono::high_resolution_clock::now();

        sorter.runAutomatedTest(desc, k);
//        sorter.runTestOnCombined(desc);

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        unsigned long long int time = duration.count();

        fclose(stream);
        std::cout << "FINISHED TESTING\n Elapsed time : " << (time / 1000000) << " s\n";

        return 0;
    }

    // OPTION 2 : RUN SPECIFIED TEST (one time, for defined {type}, for defined {array}(/random array) with its size, printed to stderr)

    if (type) type_string = std::string(type);

    std::string first;
    int size;
    {
        using std::cout, std::cin, std::endl;
        cout << "Parameters : " << type_string << "sort " << (desc ? "descending" : "ascending") << endl;
        cout << "Size (+r for random):" << endl;
        cin >> first;
        size = strtol(first.c_str(), nullptr, 0);
    }


    if (first.ends_with("r") || first.ends_with("R")) {
        sorter.runSpecifiedTest(type_string, sorter.generateArray(size).get(), size, desc);
        return 0;
    }
    std::cout << "Array :" << std::endl;
    sorter.runSpecifiedTest(type_string, sorter.cinArray(size).get(), size, desc);
    return 0;
}


