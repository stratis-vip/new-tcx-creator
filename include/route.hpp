#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <vector>
#include "coordinates.hpp"

using std::vector;
using vCor = vector<Coordinates>;

class Route {
    public:
        Route() = default;
        size_t size() const {return _col.size();}
        const Coordinates & add(const Coordinates & a) {
            _col.push_back(a);
            return a;
        }

        vCor::iterator begin() {
            return _col.begin();
        }
        vCor::iterator end() {
            return _col.end();
        }
        vCor::const_iterator cbegin() const {
            return _col.cbegin();
        }
        vCor::const_iterator cend() const {
            return _col.cend();
        }

        Coordinates operator[](const size_t ind) const {
            return _col[ind];
        }

    private:
        vCor _col{};
};

#endif