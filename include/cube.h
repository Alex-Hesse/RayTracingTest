#ifndef CUBE_H
#define CUBE_H

#include <cmath>
#include <limits>
#include "hittable.h"
#include "vec3.h"

class cube : public hittable {
    public:
        cube(const point3& center, double edgeLen, std::shared_ptr<material> mat) : center{center}, edgeL{std::fmax(0,edgeLen)}, mat{mat} {
            double halfEdgeL {edgeL/2.0};
            minX = center.x() - halfEdgeL;
            minY = center.y() - halfEdgeL;
            minZ = center.z() - halfEdgeL;
            maxX = center.x() + halfEdgeL;
            maxY = center.y() + halfEdgeL;
            maxZ = center.z() + halfEdgeL;
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            const double EPS {1e-12}; //std::numeric_limits<double>::epsilon()
             	
            const double INF {std::numeric_limits<double>::infinity()};

            double tx1{}, tx2{}, ty1 {}, ty2 {}, tz1 {}, tz2 {};

            // X slab
            if (std::abs(r.direction().x()) < EPS) {
                if (r.origin().x() < minX || r.origin().x() > maxX) return false;
                tx1 = -INF; tx2 = INF;
            } else {
                double inv {1.0 / r.direction().x()};
                tx1 = (minX - r.origin().x()) * inv;
                tx2 = (maxX - r.origin().x()) * inv;
            }

            // Y slab
            if (std::abs(r.direction().y()) < EPS) {
                if (r.origin().y() < minY || r.origin().y() > maxY) return false;
                ty1 = -INF; ty2 = INF;
            } else {
                double inv {1.0 / r.direction().y()};
                ty1 = (minY - r.origin().y()) * inv;
                ty2 = (maxY - r.origin().y()) * inv;
            }

            // Z slab
            if (std::abs(r.direction().z()) < EPS) {
                if (r.origin().z() < minZ || r.origin().z() > maxZ) return false;
                tz1 = -INF; tz2 = INF;
            } else {
                double inv {1.0 / r.direction().z()};
                tz1 = (minZ - r.origin().z()) * inv;
                tz2 = (maxZ - r.origin().z()) * inv;
            }

            double tminX {std::min(tx1, tx2)};
            double tmaxX {std::max(tx1, tx2)};
            double tminY {std::min(ty1, ty2)};
            double tmaxY {std::max(ty1, ty2)};
            double tminZ {std::min(tz1, tz2)};
            double tmaxZ {std::max(tz1, tz2)};

            double tmin {std::max(std::max(tminX, tminY), tminZ)};
            double tmax {std::min(std::min(tmaxX, tmaxY), tmaxZ)};

            if (tmin > tmax) return false;

            // Choose the nearest acceptable t within the provided interval
            double t_hit = tmin;
            if (!ray_t.surrounds(t_hit)) {
                t_hit = tmax;
                if (!ray_t.surrounds(t_hit)) return false;
            }

            rec.t = t_hit;
            rec.p = r.at(rec.t);

            // Determine which face was hit by checking the hit point coordinate
            const double NORM_EPS {1e-8};
            if (std::abs(rec.p.x() - minX) < NORM_EPS) {
                vec3 outward_normal{-1.0, 0.0, 0.0};
                rec.set_face_normal(r, outward_normal);
            } else if (std::abs(rec.p.x() - maxX) < NORM_EPS) {
                vec3 outward_normal{1.0, 0.0, 0.0};
                rec.set_face_normal(r, outward_normal);
            } else if (std::abs(rec.p.y() - minY) < NORM_EPS) {
                vec3 outward_normal{0.0, -1.0, 0.0};
                rec.set_face_normal(r, outward_normal);
            } else if (std::abs(rec.p.y() - maxY) < NORM_EPS) {
                vec3 outward_normal{0.0, 1.0, 0.0};
                rec.set_face_normal(r, outward_normal);
            } else if (std::abs(rec.p.z() - minZ) < NORM_EPS) {
                vec3 outward_normal{0.0, 0.0, -1.0};
                rec.set_face_normal(r, outward_normal);
            } else if (std::abs(rec.p.z() - maxZ) < NORM_EPS) {
                vec3 outward_normal{0.0, 0.0, 1.0};
                rec.set_face_normal(r, outward_normal);
            } else {
                // Fallback: compute which t was responsible
                if (std::abs(rec.t - tminX) < NORM_EPS || std::abs(rec.t - tmaxX) < NORM_EPS) {
                    vec3 outward_normal{(rec.t == tminX) ? -1.0 : 1.0, 0.0, 0.0};
                    rec.set_face_normal(r, outward_normal);
                } else if (std::abs(rec.t - tminY) < NORM_EPS || std::abs(rec.t - tmaxY) < NORM_EPS) {
                    vec3 outward_normal{0.0, (rec.t == tminY) ? -1.0 : 1.0, 0.0};
                    rec.set_face_normal(r, outward_normal);
                } else {
                    vec3 outward_normal{0.0, 0.0, (rec.t == tminZ) ? -1.0 : 1.0};
                    rec.set_face_normal(r, outward_normal);
                }
            }

            rec.mat = mat;

            return true;
        }

    private:
        point3 center;
        double edgeL;
    
        double minX;
        double minY;
        double minZ;
        double maxX;
        double maxY;
        double maxZ;

        std::shared_ptr<material> mat;
};

#endif