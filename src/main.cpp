#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "cube.h"

#include <chrono>




int main() {
    auto start {std::chrono::steady_clock::now()};
   
    // World  ==================================================================================
    hittable_list world;

    auto material_ground    {std::make_shared<lambertian>(color(0.8, 0.8, 0.0))};
    auto material_center    {std::make_shared<basic>(color(1.0, 1.0, 1.0))};
    auto material_left      {std::make_shared<dielectric>(1.50)};
    auto material_bubble    {std::make_shared<dielectric>(1.00 / 1.50)};
    auto material_right     {std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0)};
    auto material_gold      {std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0)};

    world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<cube>  (point3( 0.0,    0.0, -1.2),   0.6, material_right));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
    world.add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));


    // Cam =====================================================================================
    camera cam{};

    cam.aspect_ratio        = 16.0 / 9.0;
    cam.image_width         = 480;
    cam.samples_per_pixel   = 100;
    cam.max_depth           = 50;

    cam.render(world);

    auto end {std::chrono::steady_clock::now()};
    auto duration {std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};
    std::clog << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}