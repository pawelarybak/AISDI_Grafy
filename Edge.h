#ifndef IZOMORFIZMY_EDGE_H
#define IZOMORFIZMY_EDGE_H

#include <utility>
#include <iosfwd>
#include <string>

template <typename T> class Edge {
public:
    friend std::ostream& operator<<(std::ostream& stream, const Edge& edge) {
        stream << std::to_string(edge.ends.first) << " " << std::to_string(edge.ends.second);
        return stream;
    }

    Edge(T v1, T v2) : ends(std::make_pair(std::min(v1, v2), std::max(v1, v2))) {}

    T first() const {
        return ends.first;
    }

    T second() const {
        return ends.second;
    }

    bool operator==(const Edge& other) const {
        return (other.ends.first == ends.first && other.ends.second == ends.second) ||
               (other.ends.first == ends.second && other.ends.second == ends.first);
    }

    bool operator!=(const Edge& other) const {
        return !operator==(other);
    }

    bool operator<(const Edge& other) const {
        return ends < other.ends;
    }

    bool operator>(const Edge& other) const {
        return ends > other.ends;
    }

    bool operator<=(const Edge& other) const {
        return !operator>(other);
    }

    bool operator>=(const Edge& other) const {
        return !operator<(other);
    }

private:
    std::pair<T, T> ends;
};

#endif //IZOMORFIZMY_EDGE_H
