#include "shape.hpp"
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

/*Name: Daniel Park || NETID: danielp7 || Date: 12/6/19
Intro: I approached this project knowing what I learned from lecture. I made sure to use
the proper shape classes and to read which shape it was. Then I would do each command based
on the algorithms given by the .hpp class and the MP page.

 */
//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 
Shape::Shape (string name){ 
  name_ = name;
}
string Shape::getName() {
  return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length):Shape("Rectangle") {
  length_ = length;
  width_ = width;
}

double Rectangle::getArea()const {
  double area;
  area = width_ * length_;
  return area; 
 
}
double Rectangle::getVolume()const { 
  return 0;
}
Rectangle Rectangle::operator+(const Rectangle& rec) {
  double length, width;
  length = getLength() + rec.length_;
  width = getWidth() + rec.width_;
  return Rectangle(width,length);
}
Rectangle Rectangle::operator-(const Rectangle& rec) {
  double length, width;

  length = max(0.0, getLength() - rec.length_);
  
  width = max(0.0, getWidth() - rec.width_);
  
  return Rectangle(width, length);
}


double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}



//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle") {
  radius_ = radius;
}
double Circle::getArea()const {
  double area;
  double radius;
  radius = getRadius();
  area = M_PI * pow(radius, 2);
  return area;
}
double Circle::getVolume()const {
  return 0;
}
Circle Circle::operator+(const Circle& cir) {
  double radius;
  radius = getRadius() + cir.radius_;
  return Circle(radius);
}
Circle Circle::operator-(const Circle& cir) {
  double radius;
  radius = max(0.0, getRadius() - cir.radius_);
  return Circle(radius);
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius):Shape("Sphere"){
  radius_ = radius;
}
double Sphere::getArea()const {
  double area;
  double radius;
  radius = getRadius();
  area = 4*M_PI*pow(radius, 2);
  return area;
}
double Sphere::getVolume()const {
  double volume;
  double radius;
  radius = getRadius();
  volume = (4.0/3.0) * M_PI * pow(radius, 3);
  return volume;
}
Sphere Sphere::operator+(const Sphere& sph) {
  double radius;
  radius = getRadius() + sph.radius_;
  return radius;
}
Sphere Sphere::operator-(const Sphere& sph) {
  double radius;
  radius = max(0.0, getRadius() - sph.radius_);
  return Sphere(radius);
}

double Sphere::getRadius()const{return radius_;}



//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
  length_ = length;
  width_ = width;
  height_ = height;
}
double RectPrism::getArea()const {
  double area, width, height, length;
  width = getWidth();
  height = getHeight();
  length = getLength();
  area = 2* ((length*width) + (length*height) + (width*height));
  return area;
}
double RectPrism::getVolume()const {
  double volume, height, width, length;
   width = getWidth();
  height = getHeight();
  length = getLength();
  volume = length*width*height;
  return volume;
}
RectPrism RectPrism::operator+(const RectPrism& rectp) {
  double width, length, height;
  width = getWidth() + rectp.width_;
  length = getLength() + rectp.length_;
  height = getHeight() + rectp.height_;
  return RectPrism(width,length, height);
}
RectPrism RectPrism::operator-(const RectPrism& rectp) {
  double width, length, height;
  length = max(0.0, getLength() - rectp.length_);
  width = max(0.0, getWidth() - rectp.width_);
  height = max(0.0, getHeight() - rectp.height_);
  return RectPrism(width,length, height);
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
  int i,j;
  double a,b,c;
  string name;
  std::ifstream infile(file_name);
  infile >> j;
  std::vector<Shape*> vectorArray(j);
  for (i = 0; i < j; i++) {
    infile >> name;
    if (name == "Circle") {
      infile >> a;
      vectorArray[i] = new Circle(a);
    } else if (name == "Rectangle") {
      infile >> a >> b;
      vectorArray[i] = new Rectangle(a,b);
    } else if (name == "RectPrism") {
      infile >> a >> b >> c;
      vectorArray[i] = new RectPrism(a,b,c);
    } else if (name == "Sphere") {
      infile >> a;
      vectorArray[i] = new Sphere(a);
    }
  }
  infile.close();

  
  return vectorArray; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	int i;
	for (i = 0; i < shapes.size(); i++) {
	  if (shapes[i]->getArea() > max_area) {
	    max_area = shapes[i]->getArea();
	  }
	}
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
	int i;
	for (i = 0; i < shapes.size(); i++) {
	  if (shapes[i]->getVolume() > max_volume) {
	    max_volume = shapes[i]->getVolume();
	  }
	}
	
	return max_volume;
}

