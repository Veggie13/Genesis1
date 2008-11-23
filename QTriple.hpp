#ifndef QTRIPLE_HPP
#define QTRIPLE_HPP

#include <QPair>


template <typename T1, typename T2, typename T3>
struct QTriple
{
    QTriple() : contents(),
                first(contents.first.first),
                second(contents.first.second),
                third(contents.second) { }
    QTriple(const T1& v1, const T2& v2, const T3& v3)
    :   contents(QPair<T1, T2>(v1, v2), v3),
        first(contents.first.first),
        second(contents.first.second),
        third(contents.second) { }
    QTriple(const QTriple<T1, T2, T3>& other)
    :   contents(other.contents),
        first(contents.first.first),
        second(contents.first.second),
        third(contents.second) { }

    QTriple<T1, T2, T3>& operator =(const QTriple<T1, T2, T3>& other)
    {
        if (&other == this)
            return *this;

        first  = other.first;
        second = other.second;
        third  = other.third;

        return *this;
    }

private:
    typedef QPair< QPair<T1, T2>, T3 > Type;
    Type contents;

public:
    T1& first;
    T2& second;
    T3& third;

};

#endif
