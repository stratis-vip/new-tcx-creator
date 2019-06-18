#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <stdexcept>

class Coordinates {
public:
  Coordinates() = default;
  Coordinates(double lon, double lat, double alt = 0) : _alt(alt) {
    setLat(lat);
    setLon(lon);
  }

  Coordinates(const Coordinates &cord) {
    _lon = cord._lon;
    _lat = cord._lat;
    _alt = cord._alt;
  }

  double getLat() const { return _lat; }
  double getLon() const { return _lon; }
  double getAlt() const { return _alt; }

  void setLat(const double value) {
    if (value <= 0)
      throw std::invalid_argument("Latitude must be bigger than 0");
    if (value != _lat)
      _lat = value;
  }
  void setLon(const double value) {
    if (value <= 0)
      throw std::invalid_argument("Longtitude must be bigger than 0");
    if (value != _lon)
      _lon = value;
  }
  void setAlt(const double alt) {
    if (alt != _alt)
      _alt = alt;
  }

private:
  double _lat;
  double _lon;
  double _alt;
};

#endif
