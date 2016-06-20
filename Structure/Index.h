#ifndef Index_h
#define Index_h

#include "../Common/Macro.h"
#include "../Common/Math.hpp"
#include<unordered_map>

NS_LIBSPIRAL_BEGIN

class Index {
public:
    int x, y;
    
    SPIRAL_CONSTEXPR Index()
    : x(0.0f), y(0.0f)
    {}
    
    SPIRAL_CONSTEXPR Index(int xx, int yy)
    : x(xx), y(yy)
    {}
    
    SPIRAL_CXX14_CONSTEXPR Index(std::initializer_list<int> list)
    :x(*list.begin()), y(*(list.begin() + 1))
    {}
    
    SPIRAL_CONSTEXPR Index(const Index& copy)
    :x(copy.x), y(copy.y)
    {}
    
    ~Index() = default;
    
    SPIRAL_CONSTEXPR float distance(const Index& v) const {
        return libspiral::sqrt(libspiral::pow(v.x - this->x, 2) + libspiral::pow(v.y - this->y, 2));
    }
    
    SPIRAL_CONSTEXPR int manhattanDistance(const Index& v) const {
        return (v.x - this->x) + (v.y - this->y);
    }
    
    SPIRAL_CONSTEXPR Index operator+(const Index& v) const{
        return Index(x + v.x, y + v.y);
    }
    
    SPIRAL_CONSTEXPR Index operator-(const Index &v) const{
        return Index(this->x - v.x, this->y - v.y);
    }
    
    SPIRAL_CONSTEXPR Index operator-() const {
        return Index(-this->x, -this->y);
    }
    
    SPIRAL_CONSTEXPR Index operator*(int s) const {
        return Index(this->x * s, this->y * s);
    }
    
    SPIRAL_CONSTEXPR Index operator/(int s) const {
        return Index(this->x / s, this->y / s);
    }
    
    SPIRAL_CONSTEXPR bool operator<(const Index& v) const{
        return (x == v.x) ? y < v.y : x < v.x;
    }

    SPIRAL_CONSTEXPR bool operator>(const Index& v) const{
        return (x == v.x) ? y > v.y : x > v.x;
    }
    
    SPIRAL_CONSTEXPR bool operator==(const Index& v) const {
        return x == v.x && y == v.y;
    }

    SPIRAL_CONSTEXPR bool operator!=(const Index& v) const {
        return x != v.x || y != v.y;
    }
    
    SPIRAL_CXX14_CONSTEXPR Index& operator-=(const Index& v) {
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }
    
    SPIRAL_CXX14_CONSTEXPR Index& operator+=(const Index& v) {
        this->x = this->x + v.x;
        this->y = this->y + v.y;
        
        return *this;
    }
    
    SPIRAL_CXX14_CONSTEXPR Index& operator*=(int s) {
        this->x *= s;
        this->y *= s;
        return *this;
    }
    
    SPIRAL_CXX14_CONSTEXPR Index& operator/=(int s) {
        this->x /= s;
        this->y /= s;
        return *this;
    }
    
public:
    void setPoint(int xx, int yy);
    int getLength() const {
        return libspiral::sqrt(x*x + y*y);
    };

    static const Index ZERO;
};

const Index operator*(int x, const Index& v);

template<std::size_t IndexWidth>
struct IndexHash {
    typedef std::size_t result_type;
    result_type operator()(const Index& key) const {
        int hash = key.y * IndexWidth + key.x;
        return std::hash<int>()(hash);
    }
};


NS_LIBSPIRAL_END

#endif /* Index_h */
