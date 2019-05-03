#include "sphere.h"

#include <cmath>

#include  "../bsdf.h"
#include "../misc/sphere_drawing.h"

namespace CGL { namespace StaticScene {

bool Sphere::test(const Ray& r, double& t1, double& t2) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection test.
  // Return true if there are intersections and writing the
  // smaller of the two intersection times in t1 and the larger in t2.

  
//  return false;
    double a, b, c;
    a = dot(r.d, r.d);
    if(a < __DBL_EPSILON__ && a > -__DBL_EPSILON__)
        return false;
    
    b = 2.0 * dot((r.o - o), r.d);
    c = dot(r.o - o, r.o - o) - this->r * this->r;
    double sq = b * b-4 * a * c;
    if(sq < 0.0)
        return false;
    
    double sqroot = sqrt(sq);
    t1 = (-b + sqroot) / 2.0 / a;
    t2 = (-b - sqroot) / 2.0 / a;
    
    if(t2 < t1)
        swap(t1, t2);
    if(t1 > r.min_t && t1 < r.max_t){
        r.max_t = t1;
        return true;
    }
    
    if(t2 > r.min_t && t2 < r.max_t){
        r.max_t = t2;
        return true;
    }
    
    r.max_t = t1;
    
    return false;

}

bool Sphere::intersect(const Ray& r) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection.
  // Note that you might want to use the the Sphere::test helper here.
    double t1, t2;
    
    return test(r, t1, t2);

  return false;


}

bool Sphere::intersect(const Ray& r, Intersection *i) const {

  // TODO (Part 1.4):
  // Implement ray - sphere intersection.
  // Note again that you might want to use the the Sphere::test helper here.
  // When an intersection takes place, the Intersection data should be updated
  // correspondingly.
  
  
//  return false;
    double t1, t2;
    if(test(r, t1, t2)){
        if(t1 == r.max_t){
            i->t = t1;
        }else{
            i->t = t2;
        }
        Vector3D hit = r.o + i->t * r.d;
        i->n = hit - this->o;
        i->n.normalize();
        i->primitive = this;
        i->bsdf = get_bsdf();
        return true;
    }
    return false;
  
}

void Sphere::draw(const Color& c, float alpha) const {
  Misc::draw_sphere_opengl(o, r, c);
}

void Sphere::drawOutline(const Color& c, float alpha) const {
    //Misc::draw_sphere_opengl(o, r, c);
}


} // namespace StaticScene
} // namespace CGL
