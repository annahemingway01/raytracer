#include<stdio.h>
#include<math.h>
#include "shapes.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)<(b))?(b):(a))

float ray_hit_sphere(Ray *ray, Solid *solid, Vector *location);
float ray_hit_plane(Ray *ray, Solid *solid, Vector *location);


float ray_hit(Ray *ray, Solid *solid, Vector *location) {
    if (solid->type == SPHERE) {
        return ray_hit_sphere(ray, solid, location);
    } else if (solid->type == PLANE) {
        return ray_hit_plane(ray, solid, location);
    }
    return false;
}

float ray_hit_sphere(Ray *ray, Solid *solid, Vector *location) {
    /*
    First: we find parameterizations for the intersection coordinates
    
    i_x = (1 - t) * ray->origin.x + t * ray->direction.x;
    ... y and z as well...

    now plug into the equation for the sphere.

    ((1 - t) * ray->origin.x + t * ray->direction.x - solid.center.x)^2 + ...... = r^2
    
    */
    float a = pow(ray->direction.x - ray->origin.x, 2) + pow(ray->direction.y - ray->origin.y, 2) + pow(ray->direction.z - ray->origin.z, 2);
    float b = 2 * ((ray->direction.x - ray->origin.x)*(ray->origin.x - solid->location.x)
        + (ray->direction.y - ray->origin.y) * (ray->origin.y - solid->location.y)
        + (ray->direction.z - ray->origin.z) * (ray->origin.z - solid->location.z));
    float c = pow(ray->origin.x - solid->location.x, 2) + pow(ray->origin.y - solid->location.y, 2) + pow(ray->origin.z  - solid->location.z, 2) - pow(solid->data.sphere.radius, 2);

    //quadratic formula
    //first check if the square rooted bit is negative
    float d;
    if ((d = pow(b, 2) - 4* a * c) < 0) {
        //location = 0;
        return 0;
    } else {
        float t_1 = (-1 * b + sqrt(d)) / (2 * a);
        float t_2 = (-1 * b - sqrt(d)) / (2 * a);


        float t;
        //min of t_1 and t_2 is the preferred one
        //t can't be negative
        if (t_1 >= 0 && t_2 >= 0) {
            t = MIN(t_1, t_2);
        } else if (t_1 >= 0) {
            t = t_1;
        } else if (t_2 >= 0) {
            t = t_2;
        } else {
            //location = 0;
            return 0;
        }
        location->x = (1 - t) * ray->origin.x + t * ray->direction.x;
        location->y = (1 - t) * ray->origin.y + t * ray->direction.y;
        location->z = (1 - t) * ray->origin.z + t * ray->direction.z;
        return t;
    }
    return 0;
}



float ray_hit_plane(Ray *ray, Solid *solid, Vector *location) {
    /*
     n_x(d_x * t + o_x * (1 - t)- p_x) + ... for y and z = 0
     So we write the constant as n_x(o_x - p_x)
     The coefficient is the sum of all the n_i * d_i for i = x,y,z
     */
    float d = solid->data.plane.normal.x * (ray->origin.x - solid->data.plane.point.x)
        + solid->data.plane.normal.y * (ray->origin.y - solid->data.plane.point.y)
        + solid->data.plane.normal.z * (ray->origin.z - solid->data.plane.point.z);
    //t can't be negative but can it be less than 1??
    float t;
    if ((t = (-1) * d / (solid->data.plane.normal.x * (ray->direction.x - ray->origin.x)
                    + solid->data.plane.normal.y * (ray->direction.y - ray->origin.y)
                    + solid->data.plane.normal.z * (ray->direction.z - ray->origin.z))) < 0) {
        //location = 0;
        return 0;
    } else {
        location->x = ray->direction.x * t + ray->origin.x * (1 - t);
        location->y = ray->direction.y * t + ray->origin.y * (1 - t);
        location->z = ray->direction.z * t + ray->origin.z * (1 - t);
        return t;
    }

    return 0;
}

Vector get_normal_at(Solid solid, Vector point) {
    if (solid.type == SPHERE) {
        Vector to_normalize = {point.x - solid.location.x, point.y - solid.location.y,
            point.z - solid.location.z};
        return normalize(to_normalize);
    } else if (solid.type == PLANE) {
        return solid.data.plane.normal;
    }

    return point;
}


float diffuse_brightness(Solid solid, Vector point, Light light) {
    Vector normal_to_surface = get_normal_at(solid, point);
    Vector light_vec = subtract(light.location, point);
    float cos_btwn = cos_angle_between(normal_to_surface, light_vec);
    /*
     * I = Ip * Kd * cos(angle between light and surface normal
     */
    return light.intensity * solid.diffusion_coefficient * cos_btwn;

}


float specular_brightness(Solid solid, Vector point, Light light) {
    Vector light_vec = subtract(light.location, point);
    //Vector light_vec = subtract(point, light.location);
    Vector normal_to_surface = get_normal_at(solid, point);
    Vector vec_to_eye = reflect(light_vec, solid, point);
    Vector h = add(light_vec, vec_to_eye);
    h = multiply_vector_by_scalar(h, 1 / magnitude(h));
    return light.intensity * solid.specular_coefficient * MAX(0, dot(normal_to_surface, h));
}


Vector reflect(Vector input, Solid solid, Vector point) {
    Vector ret;
    Vector normal = get_normal_at(solid, point);
    float n = dot(normal, input);
    n = n * -2;
    ret = multiply_vector_by_scalar(normal, n);
    ret = subtract(input, ret);
    return ret;
}

bool is_shadow(Light light, Solid solids[], int num_solids, Vector point) {
    //vector from light to point
    //Vector direction = subtract(point, light.location);
    Vector direction = subtract(light.location, point);
    float distance = magnitude(direction);
    Vector dummy = {0, 0, 0};
    float new_dist = 0;
    Ray light_ray = {point, direction};
    for (int k = 0; k < num_solids; k++) {
        new_dist = ray_hit(&light_ray, &solids[k], &dummy);
        if (new_dist > 0.1 && new_dist < distance) {
            printf("Light:%f, Hit:%f\n", distance, new_dist); 
            return true;
        }
    }
    return false;
}
