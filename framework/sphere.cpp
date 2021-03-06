#include "sphere.hpp"

Sphere::Sphere() : Shape{}, center_{glm::vec3{0.0, 0.0, 0.0}}, radius_{0.0} {
  std::cout << "ctor sphere ()" << "\n";
  }  
Sphere::Sphere(glm::vec3 const& c, double r) : 
  Shape{}, center_{c}, radius_{r} {
    std::cout << "ctor sphere (center, radius)" << "\n";
  }

Sphere::Sphere(Color const& clr, std::string const& n, glm::vec3 const& c, double r) :
    Shape{clr, n}, center_{c}, radius_{r} {
      std::cout << "ctor sphere (color, name, center, radius)" << "\n";
    }

Sphere::Sphere(glm::vec3 const& c, double r, Color const& clr, std::string const& n) :
    Shape{clr, n}, center_{c}, radius_{r} {
      std::cout << "ctor sphere (center, radius, color, name)" << "\n";
    }

Sphere::~Sphere() { std::cout << "Sphere::~Sphere" << "\n"; }

/* virtual */ double Sphere::area() const {
  return 4.0 * PI * (radius_ * radius_);
}

/* virtual */ double Sphere::volume() const {
  return 4.0/3.0 * PI * (radius_ * radius_ * radius_);
}

/* virtual */ std::ostream& Sphere::print(std::ostream& os) const {
  os << "\n";
  os << "Sphere \"" << name() << "\" : \n";
  os << "  name    :  " << name() << "\n";
  os << "  color   :  " << color();

  os << "  center  :  "
    << "(" << center().x << "," << center().y << "," 
    << center().z << ")" << "\n"; 

  os << "  radius  :  " << radius() << "\n";
  os << "  area    :  " << area() << "\n";
  os << "  volume  :  " << volume() << "\n";

  return os;
}

bool Sphere::intersect(Ray const& ray, Sphere const& sph, float& dist) {
  glm::vec3 dir = glm::normalize(ray.direction);

  return glm::intersectRaySphere(
      ray.origin, dir,
      sph.center(), sph.radius()*sph.radius(),
      dist);

  //return result;
}

std::ostream& operator<<(std::ostream& os, Sphere const& sph) {
  sph.print(os);
}
