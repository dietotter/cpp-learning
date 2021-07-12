# What is the "Named Constructor Idiom"?

A technique that provides more intuitive and/or safer construction operations for users of your class.
The problem is that constructors always have the same name as the class. Therefore the only way to differentiate between the various constructors of a class is by the parameter list. But if there are lots of constructors, the differences between them become somewhat subtle and error prone.
With the Named Constructor Idiom, you declare all the class's constructors in the private or protected sections, and you provide public static methods that return an object. These static methods are the so-called "Named Constructors." In general there is one such static method for each different way to construct an object.
For example, suppose we are building a Point class that represents a position on the X-Y plane. Turns out there are two common ways to specify a 2-space coordinate: rectangular coordinates (X+Y), polar coordinates (Radius+Angle). (Don't worry if you can't remember these; the point isn't the particulars of coordinate systems; the point is that there are several ways to create a Point object.) Unfortunately the parameters for these two coordinate systems are the same: two floats. This would create an ambiguity error in the overloaded constructors:
class Point {
public:
Point(float x, float y); // Rectangular coordinates
Point(float r, float a); // Polar coordinates (radius and angle) // ERROR: Overload is Ambiguous: Point::Point(float,float) };
int main()
{
Point p = Point(5.7, 1.2); // Ambiguous: Which coordinate system?
...
}
One way to solve this ambiguity is to use the Named Constructor Idiom:
#include // To get sin() and cos()
class Point {
public:
static Point rectangular(float x, float y); // Rectangular coord's static Point polar(float radius, float angle); // Polar coordinates // These static methods are the so-called "named constructors" ...
private:
Point(float x, float y); // Rectangular coordinates
float x_, y_;
};
inline Point::Point(float x, float y) : x_(x), y_(y) { }
inline Point Point::rectangular(float x, float y)

{ return Point(x, y); }
inline Point Point::polar(float radius, float angle)
{ return Point(radius*cos(angle), radius*sin(angle)); }
Now the users of Point have a clear and unambiguous syntax for creating Points in either coordinate system:
int main()
{
Point p1 = Point::rectangular(5.7, 1.2); // Obviously rectangular
Point p2 = Point::polar(5.7, 1.2); // Obviously polar
...
}
Make sure your constructors are in the protected section if you expect Point to have derived classes.
The Named Constructor Idiom can also be used to make sure your objects are always created via new.
Note that the Named Constructor Idiom, at least as implemented above, is just as fast as directly calling a constructor modern compilers will not make any extra copies of your object.