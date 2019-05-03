#include "bbox.h"

#include "GL/glew.h"

#include <algorithm>
#include <iostream>

namespace CGL {

bool BBox::intersect(const Ray& r, double& t0, double& t1) const {

  // TODO (Part 2.2):
  // Implement ray - bounding box intersection test
  // If the ray intersected the bouding box within the range given by
  // t0, t1, update t0 and t1 with the new intersection times.

  
//  return false;
    
    //x axis
    double factor = r.d.x;
    double tt1, tt2;
    double tmin = __DBL_MIN__, tmax = __DBL_MAX__;
    if(factor > __DBL_EPSILON__ || factor < -__DBL_EPSILON__){
        tt1 = (min.x - r.o.x) / factor;
        tt2 = (max.x - r.o.x) / factor;
        if(tt2 < tt1)
            std::swap(tt1, tt2);
        tmin = std::max(tmin, std::min(tt1,tt2));
        tmax = std::min(tmax, std::max(tt1,tt2));
    }
    factor = r.d.y;
    if(factor > __DBL_EPSILON__ || factor < -__DBL_EPSILON__){
        tt1 = (min.y - r.o.y) / factor;
        tt2 = (max.y - r.o.y) / factor;
        if(tt2 < tt1)
            std::swap(tt1, tt2);
        tmin = std::max(tmin, std::min(tt1,tt2));
        tmax = std::min(tmax, std::max(tt1,tt2));
    }
    factor = r.d.z;
    if(factor > __DBL_EPSILON__ || factor < -__DBL_EPSILON__){
        tt1 = (min.z - r.o.z) / factor;
        tt2 = (max.z - r.o.z) / factor;
        if(tt2 < tt1)
            std::swap(tt1, tt2);
        tmin = std::max(tmin, std::min(tt1,tt2));
        tmax = std::min(tmax, std::max(tt1,tt2));
    }
    
    //very important!!!!!
    if(tmin > tmax)
        return false;
    
    if((tmin >= r.min_t && tmin <= r.max_t )|| (tmax >= r.min_t && tmax <= r.max_t )){
        t0 = tmin;
        t1 = tmax;
        return true;
    }
    return false;
  
}

void BBox::draw(Color c, float alpha) const {

  glColor4f(c.r, c.g, c.b, alpha);

  // top
  glBegin(GL_LINE_STRIP);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(max.x, max.y, max.z);
  glEnd();

  // bottom
  glBegin(GL_LINE_STRIP);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, min.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glEnd();

  // side
  glBegin(GL_LINES);
  glVertex3d(max.x, max.y, max.z);
  glVertex3d(max.x, min.y, max.z);
  glVertex3d(max.x, max.y, min.z);
  glVertex3d(max.x, min.y, min.z);
  glVertex3d(min.x, max.y, min.z);
  glVertex3d(min.x, min.y, min.z);
  glVertex3d(min.x, max.y, max.z);
  glVertex3d(min.x, min.y, max.z);
  glEnd();

}

std::ostream& operator<<(std::ostream& os, const BBox& b) {
  return os << "BBOX(" << b.min << ", " << b.max << ")";
}

} // namespace CGL
