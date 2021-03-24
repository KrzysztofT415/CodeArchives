#ifndef AISD_L2_POINT2D_HPP
#define AISD_L2_POINT2D_HPP

template <class T>
class Point2D {
private:
    T x;
    T y;
public:
    Point2D() : x(0), y(0) {}
    Point2D(T x, T y) : x(x), y(y) {}

    auto operator<=>(const Point2D&) const = default;

    friend std::ostream &operator<<(std::ostream &os, Point2D const &point) {
        return os << "{" << point.x << ";" << point.y << "}";
    }

    friend std::istream& operator >> (std::istream& in, Point2D &point) {
        std::cin >> point.x >> point.y;
        return in;
    };

    static Point2D randInt(int size) {
        return Point2D(rand() % size, rand() % size);
    }

    static Point2D randDouble(int size) {
        return Point2D((rand() % (100 * size)) / 100., (rand() % (100 * size)) / 100.);
    }
};

#endif //AISD_L2_POINT2D_HPP
