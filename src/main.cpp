#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#include <chrono>




int main() {
    auto start = std::chrono::steady_clock::now();
   
    // World  ==================================================================================
    hittable_list world;

    world.add(make_shared<sphere>(point3(1,0,-1), 0.2));
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));    //middle sphere
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100)); //ground

    camera cam{};
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 800;
    cam.render(world);

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::clog << "Execution time: " << duration.count() << " microseconds" << std::endl;
}