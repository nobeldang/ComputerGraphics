#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <stdio.h>

// my own implementation of Vec3
struct Vec3 {
    double x, y, z;
    Vec3(double x_ = 0, double y_ = 0, double z_ = 0){
      x = x_;
      y = y_;
      z = z_;
    }
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
    Vec3 operator*(double d) const { return Vec3(x * d, y * d, z * d); }
    Vec3 normalize() const {
        double mg = sqrt(x*x + y*y + z*z);
        return Vec3(x/mg, y/mg, z/mg);
    }
    double dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }
};

// initialize some constants and variables
Vec3 bg_color = Vec3(0.1, 0.1, 0.1);
Vec3 I_amb = Vec3(0.3, 0.3, 0.3);
Vec3 I_dir = Vec3(0.7, 0.7, 0.7);
Vec3 dir_light_loc = Vec3(5.0, 18.0, 10.0);
int recursion_depth;

struct Sphere {
    Vec3 center;
    double radius;
    Vec3 color;
    double ref_coef;
    Sphere(const Vec3& center_, double radius_, const Vec3& color_, double ref_coef_){
      center = center_;
      radius = radius_;
      color = color_;
      ref_coef = ref_coef_;
    }
};

struct RayCast {
    Vec3 origin, dir;
    RayCast(const Vec3& origin_, const Vec3& dir_){
      origin = origin_;
      dir = dir_;
    }
};

bool sphere_intersect(const Sphere& sphere, const RayCast& ray, double& t) {
    Vec3 oc = ray.origin - sphere.center;

    double a = ray.dir.dot(ray.dir);
    double b = 2.0 * oc.dot(ray.dir);
    double c = oc.dot(oc) - sphere.radius * sphere.radius;
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0){
      return false;
    }
    else {
        double root1 = double(-b - sqrt(discriminant)) / double(2.0*a);
        double root2 = double(-b + sqrt(discriminant)) / double(2.0*a);
        if (root1 < root2){
          t = root1;
        }
        else{
          t = root2;
        }
        return t > 0.0;
    }
}

Vec3 reflect_dir(const Vec3& dir, const Vec3& n_vec){
  // calculating the reflected ray's (unit) direction vector
  return (dir + (n_vec*2.0*((Vec3(0.0, 0.0, 0.0)-dir).normalize().dot(n_vec)))).normalize();
}

Vec3 pixel_color(const RayCast& ray, const std::vector<Sphere>& spheres, int recursion_depth) {
    extern Vec3 dir_light_loc;
    extern Vec3 I_amb;
    extern Vec3 I_dir;
    extern Vec3 bg_color;
    if (recursion_depth <= 0){
      return bg_color;
    }

    double closest_t = std::numeric_limits<double>::infinity();
    const Sphere* closest_sphere = nullptr;

    for (const auto& sphere : spheres) {
        double t;
        if (sphere_intersect(sphere, ray, t) && t < closest_t) {
            closest_t = t;
            closest_sphere = &sphere;
        }
    }

    if (closest_sphere) {
        // performing blinn phong shading now with reflection
        Vec3 point = ray.origin + (ray.dir * closest_t);
        Vec3 n_vec = (point - closest_sphere->center).normalize();
        Vec3 l = (dir_light_loc - point).normalize();
        Vec3 h = (l + ray.origin).normalize();
        double cos_factor_diff = std::max(0.0, n_vec.dot(l));
        double cos_factor_spec = std::max(0.0, n_vec.dot(h));
        double alpha = 32.0;

        Vec3 reflected_dir = reflect_dir(ray.dir, n_vec).normalize();
        RayCast reflected_ray(point, reflected_dir);
        Vec3 reflected_ray_color = pixel_color(reflected_ray, spheres, recursion_depth - 1);

        Vec3 init_ray_clr = (closest_sphere->color *I_amb) +
                   (closest_sphere->color * I_dir * cos_factor_diff) +
                   (closest_sphere->color * I_dir * pow(cos_factor_spec, alpha));

        Vec3 final_color = init_ray_clr * (1 - closest_sphere->ref_coef) +
                          reflected_ray_color * closest_sphere->ref_coef;

        return final_color;
    }
    else{
        return bg_color; // returning background colors for pixles whose rays do not intersect with the sphere
    }
}


int main() {
    // FInal project Graphics: Nobel Dang
  	scanf("%d", &recursion_depth);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3(0, 0, -5), 1, Vec3(1, 0, 0), 0.3)); // red clored sphere
    spheres.push_back(Sphere(Vec3(2, 0, -6), 1, Vec3(0, 0, 1), 0.5)); // blue colored sphere with much higher reflectivity

    int width = 800;
    int height = 600;
    double aspect_ratio = double(width) / double(height);

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            RayCast ray(Vec3(0, 0, 0), Vec3((u - 0.5) * aspect_ratio, v - 0.5, -1).normalize()); // for each pixel cast a ray
            Vec3 pix_clr = pixel_color(ray, spheres, recursion_depth);  // for each object calculate intersection and shade the pixel

            int red = int(255 * std::min(1.0, pix_clr.x));
            int green = int(255 * std::min(1.0, pix_clr.y));
            int blue = int(255 * std::min(1.0, pix_clr.z));

            std::cout << red << ' ' << green << ' ' << blue << '\n';
        }
    }
}
