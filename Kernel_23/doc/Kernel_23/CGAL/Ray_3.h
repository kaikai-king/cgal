namespace CGAL {

/*!
\ingroup PkgKernel23

An object `r` of the data type `Ray_3` is a directed 
straight ray in the three-dimensional Euclidean space \f$ \E^3\f$. It starts 
in a point called the <I>source</I> of `r` and it goes to infinity. 

\sa `Kernel::Ray_3` 

*/
template< typename Kernel >
class Ray_3 {
public:

/// \name Creation 
/// @{

/*! 
introduces a ray `r` 
with source \f$ p\f$ and passing through point \f$ q\f$. 
*/ 
Ray_3(const Point_3<Kernel> &p, const Point_3<Kernel> &q); 

/*! 
introduces a ray `r` with source \f$ p\f$ and with 
direction \f$ d\f$. 
*/ 
Ray_3(const Point_3<Kernel> &p, const Direction_3<Kernel> &d); 

/*! 
introduces a ray `r` with source \f$ p\f$ and with 
a direction given by \f$ v\f$. 
*/ 
Ray_3(const Point_3<Kernel> &p, const Vector_3<Kernel> &v); 

/*! 
introduces a ray `r` starting at source \f$ p\f$ with 
the same direction as \f$ l\f$. 
*/ 
Ray_3(const Point_3<Kernel> &p, const Line_3<Kernel> &l); 

/// @} 

/// \name Operations 
/// @{

/*! 
Test for equality: two rays are equal, iff they have the same 
source and the same direction. 
*/ 
bool operator==(const Ray_3<Kernel> &h) const; 

/*! 
Test for inequality. 
*/ 
bool operator!=(const Ray_3<Kernel> &h) const; 

/*! 
returns the source of `r` 
*/ 
Point_3<Kernel> source() const; 

/*! 
returns a point on `r`. `point(0)` is the source. 
`point(i)`, with \f$ i>0\f$, is different from the 
source. \pre \f$ i \geq0\f$. 
*/ 
Point_3<Kernel> point(int i) const; 

/*! 
returns the direction of `r`. 
*/ 
Direction_3<Kernel> direction() const; 

/*! 
returns a vector giving the direction of `r`. 
*/ 
Vector_3<Kernel> to_vector() const; 

/*! 
returns the line supporting `r` which has the same direction. 
*/ 
Line_3<Kernel> supporting_line() const; 

/*! 
returns the ray with the same source and the opposite direction. 
*/ 
Ray_3<Kernel> opposite() const; 

/*! 
ray `r` is degenerate, if the source and the second defining 
point fall together (that is if the direction is degenerate). 
*/ 
bool is_degenerate() const; 

/*! 
A point is on `r`, iff it is equal to the source 
of `r`, or if it is in the interior of `r`. 
*/ 
bool has_on(const Point_3<Kernel> &p) const; 

/*! 
returns the ray obtained by applying \f$ t\f$ on the source 
and on the direction of `r`. 
*/ 
Ray_3<Kernel> transform(const Aff_transformation_3<Kernel> &t) const; 

/// @}

}; /* end Ray_3 */
} /* end namespace CGAL */
