//
//  Sphere.cpp
//  Papaya
//
//  Created by Guo Chen on 6/19/17.
//  Copyright © 2017 Guo Chen. All rights reserved.
//

#include "Sphere.hpp"

Sphere::Sphere(const Vec3D &center, double radius, Material *material):
	center(center), radius(radius), material(material) {}

bool Sphere::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Vec3D oc = ray.origin - center;
	double a = ray.direction.norm2();
	double b = dot(oc, ray.direction);
	double c = oc.norm2() - radius * radius;
	double discriminant = b * b - a * c;
	if (discriminant > 0) {
		double temp = (-b - sqrt(discriminant)) / a;
		if (tmin < temp && temp < tmax) {
			record.t = temp;
			record.p = ray.pointAt(record.t);
			record.normal = (record.p - center) / radius;
			record.material = material;
			double phi = atan2(record.normal.z, record.normal.x);
			double theta = asin(record.normal.y);
			record.u = 1 - (phi + PI) / (2 * PI);
			record.v = (theta + PI / 2) / PI;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (tmin < temp && temp < tmax) {
			record.t = temp;
			record.p = ray.pointAt(record.t);
			record.normal = (record.p - center) / radius;
			record.material = material;
			double phi = atan2(record.normal.z, record.normal.x);
			double theta = asin(record.normal.y);
			record.u = 1 - (phi + PI) / (2 * PI);
			record.v = (theta + PI / 2) / PI;
			return true;
		}
	}
	return false;
}

bool Sphere::boundingBox(double t0, double t1, BBox &box) const {
	box = BBox(center - radius, center + radius);
	return true;
}

MovingSphere::MovingSphere(const Vec3D &center0, const Vec3D &center1, double t0, double t1,
	double radius, Material *material): center0(center0),center1(center1),
	time0(t0), time1(t1), radius(radius), material(material) {}

bool MovingSphere::hit(const Ray &ray, double tmin, double tmax, HitRecord &record) const {
	Vec3D oc = ray.origin - center(ray.time);
	double a = dot(ray.direction, ray.direction);
	double b = dot(oc, ray.direction);
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - a * c;
	if (discriminant > 0) {
		double temp = (-b - sqrt(discriminant)) / a;
		if (tmin < temp && temp < tmax) {
			record.t = temp;
			record.p = ray.pointAt(record.t);
			record.normal = (record.p - center(ray.time)) / radius;
			record.material = material;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (tmin < temp && temp < tmax) {
			record.t = temp;
			record.p = ray.pointAt(record.t);
			record.normal = (record.p - center(ray.time)) / radius;
			record.material = material;
			return true;
		}
	}
	return false;
}

bool MovingSphere::boundingBox(double t0, double t1, BBox &box) const {
	BBox box0(center0 - radius, center0 + radius);
	BBox box1(center1 - radius, center1 + radius);
	box = surroundBox(box0, box1);
	return true;
}
