#include "box.hpp"


Box::Box() : 
    Shape{},
    min_{glm::vec3{0.0, 0.0, 0.0}},
    max_{glm::vec3{0.0, 0.0, 0.0}} { std::cout << "ctor box ()" << "\n"; }

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape{}, min_{min}, max_{max} { std::cout << "ctor box (min, max)" << "\n"; }

Box::Box(Color const& clr, std::string const& n,
    glm::vec3 const& min, glm::vec3 const& max) :
    Shape{clr, n}, min_{min}, max_{max} {
      std::cout << "ctor box (color, name, min, max)" << "\n";
    }

Box::~Box() { std::cout << "Box::~Box" << "\n"; }

/* virtual */ double Box::area() const {
    // 6*(area of one side)
    return 6.0 * (std::abs(max_.x - min_.x) * std::abs(max_.x - min_.x));
}

/* virtual */ double Box::volume() const {
  //length * width * height
  return std::abs(max_.x - min_.x) 
    * std::abs(max_.y - min_.y) 
    * std::abs(max_.z - min_.z);
}

/* virtual */ std::ostream& Box::print(std::ostream& os) const {
  os << "\n";
  os << "Box \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  color   :  " << color();

  os << "  minimum :  " 
    << "(" << min().x << "," << min().y << "," << min().z << ")" << "\n";
  
  os << "  maximum :  "
    << "(" << max().x << "," << max().y << "," << max().z << ")" << "\n";
      
  os << "  area    :  " << area() << "\n";
  os << "  volume  :  " << volume() << "\n";

  return os;
}

bool Box::intersect(Ray const& r) const {
  float foo{0.0};
  return Box::intersect(r, foo);
}

bool Box::intersect(Ray const& r, float& dist) const {
  glm::vec3 dir = glm::normalize(r.direction);

  /*
    t-values: scalar of ray vector, 
    calculated by solving ray = min(min_.x, max_x) or ray = max(min_.x, max_.x)
    respectively.
  */

  double tx_min, ty_min, tz_min, tx_max, ty_max, tz_max;

  /*
    tX_min: possible t-values of intersect point on the box side nearer to 
            ray.origin.
    tX_max: possible t-values of  intersect point on the far side of the box.
  */

  if (dir.x != 0) {
    tx_min = (std::min(min_.x - r.origin.x, max_.x - r.origin.x)) / dir.x;
    tx_max = (std::max(min_.x - r.origin.x, max_.x - r.origin.x)) / dir.x;
  } else tx_min = 0;

  if (dir.y != 0) {
    ty_min = (std::min(min_.y - r.origin.y, max_.y - r.origin.y)) / dir.y;
    ty_max = (std::max(min_.y - r.origin.y, max_.y - r.origin.y)) / dir.y;
  } else ty_min = 0;
  
  if (dir.z != 0) {
    tz_min = (std::min(min_.z - r.origin.z, max_.z - r.origin.z)) / dir.z;
    tz_max = (std::max(min_.z - r.origin.z, max_.z - r.origin.z)) / dir.z;
  } else tz_min = 0;

  /*
    tmin: t-value of intersection point on near box side
    tmax: t-value of intersection point on far box side
  */

  double tmin = std::max(std::max(std::min(tx_min, tx_max), 
                  std::min(ty_min, ty_max)), std::min(tz_min, tz_max));

  double tmax = std::min(std::min(std::max(tx_min, tx_max),
                  std::max(ty_min, ty_max)), std::max(tz_min, tz_max));

  //is there a distance between the two intersection points?
  if (tmax < std::max(0.0, tmin)) return false;

  //calculate distance with transformed pythagoras:
  dist = std::sqrt( dir.x*(tmax-tmin)*dir.x*(tmax-tmin) 
                        + dir.y*(tmax-tmin)*dir.y*(tmax-tmin)
                        + dir.z*(tmax-tmin)*dir.y*(tmax-tmin) ); 

  return true;
}



std::ostream& operator<<(std::ostream& os, Box const& b) {
  b.print(os);
}
