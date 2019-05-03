# PathTracer1
Implemented a path tracing algorithm which simulates the interaction of light rays with primitive shapes (spheres and triangles), to allow for the rendering of 3D meshes with realistic lighting.

## Part 1: Ray Generation and Intersection

Started by setting up basic ray generation and allowing for the intersection of rays with spheres and triangles, including the calculation of normals to allow for simple, fast shading.

### Simple model rendering

<img src="docs/images/part1_1.png" width="400"/>  <img src="docs/images/part1_2.png" width="400"/>

## Part 2: Bounding Volume Hierarchy

Test ray by Bounding volume hierarchy(BVH) to accelerate.

### Complex model rendering

<img src="docs/images/part2_2.png" width="400"/>  <img src="docs/images/part2_4.png" width="400"/>

## Part 3: Direct Illumination

Two direct sampling functions: uniform hemisphere sampling and lighting sampling.

### Uniform hemisphere sampling

<img src="docs/images/part3_2.png" height="300"/>

### Light sampling

<img src="docs/images/part3_3.png" height="300"/>  <img src="docs/images/part3_4.png" height="300"/>

## Part 4: Global Illumination

Combined direct illumination with indirect illumination to get global illumination effect. Compared to direct lighting, the BSDF is sampled at the hit point and recursively trace a ray in that sample direction.

Bunny with 1024 samples per pixel.

<img src="docs/images/part4_12.png" width="400"/>  
