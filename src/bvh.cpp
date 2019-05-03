#include "bvh.h"

#include "CGL/CGL.h"
#include "static_scene/triangle.h"

#include <iostream>
#include <stack>

using namespace std;

namespace CGL { namespace StaticScene {

BVHAccel::BVHAccel(const std::vector<Primitive *> &_primitives,
                   size_t max_leaf_size) {

  root = construct_bvh(_primitives, max_leaf_size);

}

BVHAccel::~BVHAccel() {
  if (root) delete root;
}

BBox BVHAccel::get_bbox() const {
  return root->bb;
}

void BVHAccel::draw(BVHNode *node, const Color& c, float alpha) const {
  if (node->isLeaf()) {
    for (Primitive *p : *(node->prims))
      p->draw(c, alpha);
  } else {
    draw(node->l, c, alpha);
    draw(node->r, c, alpha);
  }
}

void BVHAccel::drawOutline(BVHNode *node, const Color& c, float alpha) const {
  if (node->isLeaf()) {
    for (Primitive *p : *(node->prims))
      p->drawOutline(c, alpha);
  } else {
    drawOutline(node->l, c, alpha);
    drawOutline(node->r, c, alpha);
  }
}

    
    int count_bvh = 0;
    
BVHNode *BVHAccel::construct_bvh(const std::vector<Primitive*>& prims, size_t max_leaf_size) {
  
  // TODO (Part 2.1):
  // Construct a BVH from the given vector of primitives and maximum leaf
  // size configuration. The starter code build a BVH aggregate with a
  // single leaf node (which is also the root) that encloses all the
  // primitives.

//  BBox centroid_box, bbox;
//
//  for (Primitive *p : prims) {
//      BBox bb = p->get_bbox();
//      bbox.expand(bb);
//      Vector3D c = bb.centroid();
//      centroid_box.expand(c);
//  }
//
//  BVHNode *node = new BVHNode(bbox);
//
//
//  node->prims = new vector<Primitive *>(prims);
//  return node;

    if(prims.size() == 0)
        return NULL;
    
    BBox centroid_box, bbox;
    
    for (Primitive *p : prims) {
        BBox bb = p->get_bbox();
        bbox.expand(bb);
        Vector3D c = bb.centroid();
        centroid_box.expand(c);
    }
    
    BVHNode *node = new BVHNode(bbox);
    
    if(prims.size() > max_leaf_size){
        
        //pick the axis of bounding box
        int axis; //45-x 23-y 01-z
        axis = ((((fabs(bbox.extent.x) > fabs(bbox.extent.y)) << 1)
                 +(fabs(bbox.extent.y) > fabs(bbox.extent.z))) << 1 )
        +(fabs(bbox.extent.x) > fabs(bbox.extent.z));
        
        //find split plane equation
        double mid;
        double left;
        double right;
        
        int axis_idx;
        
        if(axis == 7 || axis == 5){
            left = bbox.min.x;
            right = bbox.max.x;
            axis_idx = 0;
            
        }
        else if(axis == 2 || axis == 3){
            left = bbox.min.y;
            right = bbox.max.y;
            axis_idx = 1;
        }
        else if(axis == 4 || axis == 0){
            left = bbox.min.z;
            right = bbox.max.z;
            axis_idx = 2;
        }else{
            cout<<"axis == "<<axis<<endl;
            exit(0);
        }
        
//        double d = 1.0;
        
        vector<Primitive *> lPrimes;
        vector<Primitive *> rPrimes;
        
//        BBox lbox;
//        BBox rbox;
//
        
        do{
            mid = (left + right) * 0.5;
//            double mid_abs;
//            if(mid < 0){
//                mid_abs = -mid;
//                d = -1;
//            }
////            cout<<"l:"<<lPrimes.size()<< " r:"<<rPrimes.size()<<" "<<left<<" "<<mid<<" "<<right<<endl;
//
//            split = axisVec/mid_abs;
//
//            cout<<"split: " << split.x <<" "<<split.y<<" "<<split.z<<endl;
//
//            lbox.clear();
//            rbox.clear();
//
            lPrimes.clear();
            rPrimes.clear();
            
            for (Primitive *p : prims) {
                BBox bb = p->get_bbox();
                Vector3D c = bb.centroid();
                
                if(c[axis_idx] < mid)
                    lPrimes.push_back(p);
                else
                    rPrimes.push_back(p);
                
//                cout<<"centroid: "<<c.x<<" "<<c.y<<" "<<c.z<<endl;
//
//                if( dot(split,c) < d){
//                    lPrimes.push_back(p);
//                    BBox bb = p->get_bbox();
//                    lbox.expand(bb);
//                }else{
//                    rPrimes.push_back(p);
//                    BBox bb = p->get_bbox();
//                    rbox.expand(bb);
//                }
            }
            if(lPrimes.size() == 0){
                left = mid;
            }else if(rPrimes.size() == 0){
                right = mid;
            }
        }while(lPrimes.size() == 0 || rPrimes.size() == 0);

        node->l = construct_bvh(lPrimes, max_leaf_size);
        node->r = construct_bvh(rPrimes, max_leaf_size);
    }else{
        node->prims = new vector<Primitive *>(prims);
    }
    
    return node;

}


bool BVHAccel::intersect(const Ray& ray, BVHNode *node) const {

  // TODO (Part 2.3):
  // Fill in the intersect function.
  // Take note that this function has a short-circuit that the
  // Intersection version cannot, since it returns as soon as it finds
  // a hit, it doesn't actually have to find the closest hit.


//  for (Primitive *p : *(root->prims)) {
//    total_isects++;
//    if (p->intersect(ray))
//      return true;
//  }
//  return false;
    double t0, t1;
    if(node->bb.intersect(ray, t0, t1)){
        if(node->isLeaf()){
            for (Primitive *p : *(node->prims)) {
                total_isects++;
                if(p->intersect(ray))
                    return true;
            }
        }else{
            return intersect(ray, node->l) || intersect(ray, node->r);
        }
    }
    
    return false;

}

bool BVHAccel::intersect(const Ray& ray, Intersection* i, BVHNode *node) const {

  // TODO (Part 2.3):
  // Fill in the intersect function.


//  bool hit = false;
//  for (Primitive *p : *(root->prims)) {
//    total_isects++;
//    if (p->intersect(ray, i)) 
//      hit = true;
//  }
//  return hit;
    bool naive = false;
    
    if(naive){
        bool hit = false;
        for (Primitive *p : *(root->prims)) {
            total_isects++;
            if (p->intersect(ray, i))
                hit = true;
        }
        return hit;
    }else{
        bool hit = false;
        double t0, t1;
        if(node->bb.intersect(ray, t0, t1)){
            if(node->isLeaf()){
                for (Primitive *p : *(node->prims)) {
                    total_isects++;
                    Intersection eachI;
                    if(p->intersect(ray, &eachI)){
                        *i = eachI;
                        hit = true;
                    }
                }
            }else{
                Intersection leftI;
                Intersection rightI;
                if(intersect(ray, &leftI, node->l)){
                    *i = leftI;
                    hit = true;
                }
                if(intersect(ray, &rightI, node->r)){
                    *i = rightI;
                    hit = true;
                }
            }
        }
        return hit;
    }
  
}

}  // namespace StaticScene
}  // namespace CGL
