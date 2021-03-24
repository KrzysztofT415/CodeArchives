#ifndef AISD_L2_SORTTYPE_HPP
#define AISD_L2_SORTTYPE_HPP

#include <chrono>

template <class T>
class SortType {
public:
    virtual void sort(T* array, int length, bool desc, bool silent) {
        comp_num = 0;
        move_num = 0;
        time = 0;
        m_desc = desc;

        if (silent) { this->mute(); }
        else { this->unmute(); }

        auto t1 = std::chrono::high_resolution_clock::now();

        sort_typed(array, length);

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
        time = duration.count();

        std::cerr << "  compares : " << comp_num << ";\tmoves : " << move_num << ";\ttime : " << time << " us";
    }

    int getCompNum() const { return comp_num; }
    int getMoveNum() const { return move_num; }
    int getTime() const { return time; }
    bool isDesc() const { return m_desc; }

    void setCompNum(int compNum) { comp_num = compNum; }
    void setMoveNum(int moveNum) { move_num = moveNum; }
    void setTime(int n_time) { time = n_time; }
    void setDesc(bool mDesc) { m_desc = mDesc; }

protected:
    bool compare(const T &a, const T &b) {
        comp_num++;
        return m_desc * (a >= b) + !m_desc * (a <= b);
    };

    void move(T* container, T value) {
        move_num++;
        *container = std::move(value);
    }

    void swap(T &a, T &b) {
        move_num++;
        std::swap(a, b);
    }

private:
    virtual void sort_typed(T* array, int length) = 0;
    virtual void mute() = 0;
    virtual void unmute() = 0;

    unsigned long long int comp_num = 0;
    unsigned long long int move_num = 0;
    unsigned long long int time = 0;
    bool m_desc = false;
};

#endif //AISD_L2_SORTTYPE_HPP
