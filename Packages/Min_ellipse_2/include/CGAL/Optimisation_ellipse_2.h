// Copyright (c) 1997-2001  Freie Universitaet Berlin (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Sven Schoenherr <sven@inf.ethz.ch>, Bernd Gaertner

#ifndef CGAL_OPTIMISATION_ELLIPSE_2_H
#define CGAL_OPTIMISATION_ELLIPSE_2_H

#include <CGAL/Conic_2.h>
#include <CGAL/Optimisation/assertions.h>

#ifndef CGAL_IO_FORWARD_DECL_WINDOW_STREAM_H
#  include <CGAL/IO/forward_decl_window_stream.h>
#endif

CGAL_BEGIN_NAMESPACE

// Class interface
// ===============
template < class K_ >
class Optimisation_ellipse_2 {
    /*
    friend  std::ostream&  operator << <> (
        std::ostream&, const Optimisation_ellipse_2<K_>&);
    friend  std::istream&  operator >> <> (
        std::istream&, Optimisation_ellipse_2<K_> &);
    friend  CGAL::Window_stream& operator << <> (
        CGAL::Window_stream&, const Optimisation_ellipse_2<K_>&);
    */
  public:
    // types
    typedef           K_                K;
    typedef  typename K_::RT            RT;
    typedef  typename K_::FT            FT;
    typedef  typename K::Point_2        Point;
    typedef  typename K::Conic_2        Conic;
    
    /**************************************************************************
    WORKAROUND: Some compilers are unable to match member functions defined
    outside the class template. Therefore, all member functions are implemented
    in the class interface.
    
    // creation
    Optimisation_ellipse_2( );
    
    void  set( );
    void  set( const Point& p);
    void  set( const Point& p,  const Point& q);
    void  set( const Point& p1, const Point& p2, const Point& p3);
    void  set( const Point& p1, const Point& p2,
               const Point& p3, const Point& p4);
    void  set( const Point& p1, const Point& p2,
               const Point& p3, const Point& p4, const Point& p5);
    
    // access functions
    int  number_of_boundary_points()
    
    // equality tests
    bool  operator == ( const Optimisation_ellipse_2<K>& e) const;
    bool  operator != ( const Optimisation_ellipse_2<K>& e) const;
    
    // predicates
    CGAL::Bounded_side  bounded_side( const Point& p) const;
    bool  has_on_bounded_side      ( const Point& p) const;
    bool  has_on_boundary          ( const Point& p) const;
    bool  has_on_unbounded_side    ( const Point& p) const;
    
    bool  is_empty     ( ) const;
    bool  is_degenerate( ) const;
    **************************************************************************/

  /* private: */
    // private data members
    int    n_boundary_points;                   // number of boundary points
    Point  boundary_point1, boundary_point2;    // two boundary points
    Conic  conic1, conic2;                      // two conics

    // this gradient vector has dr=0 and is used in testing the
    // position of a point relative to an ellipse through 4 points
    mutable RT     dr, ds, dt, du, dv, dw;  
    mutable bool   d_values_set; 
    
    // this gradient vector is just conic2 - conic1 and is used in
    // obtaining an explicit conic representing an ellipse through 4 poinnts
    mutable RT     er, es, et, eu, ev, ew;
    mutable bool e_values_set;

    // needed in bounded-side predicate over ellipse with 4 support points
    mutable Conic helper_ellipse; // needed in bounded-side predicate over 
    mutable bool helper_ellipse_set;

    mutable Conic helper_conic; // also needed in bounded-side test

// ============================================================================

// Class implementation
// ====================

  public:
    // Constructor
    // -----------
    inline
    Optimisation_ellipse_2( )
    { }

    // Set functions
    // -------------
    inline
    void
    set( )
    {
        n_boundary_points = 0;
    }
    
    inline
    void
    set( const Point& p)
    {
        n_boundary_points = 1;
        boundary_point1   = p;
    }
    
    inline
    void
    set( const Point& p, const Point& q)
    {
        n_boundary_points = 2;
        boundary_point1   = p;
        boundary_point2   = q;
    }
    
    inline
    void
    set( const Point& p1, const Point& p2, const Point& p3)
    {
        n_boundary_points = 3;
        conic1.set_ellipse( p1, p2, p3);
    }
    
    inline
    void
    set( const Point& p1, const Point& p2, const Point& p3, const Point& p4)
    {
        n_boundary_points = 4;
        Conic::set_two_linepairs( p1, p2, p3, p4, conic1, conic2);

	d_values_set = false;
	e_values_set = false;
	helper_ellipse_set = false;	
    }

    void
    set_d_values() const
    {
      if (!d_values_set) {
        dr = RT( 0);
        ds = conic1.r() * conic2.s() - conic2.r() * conic1.s(),
        dt = conic1.r() * conic2.t() - conic2.r() * conic1.t(),
        du = conic1.r() * conic2.u() - conic2.r() * conic1.u(),
        dv = conic1.r() * conic2.v() - conic2.r() * conic1.v(),
        dw = conic1.r() * conic2.w() - conic2.r() * conic1.w();
	d_values_set = true;
      }
    }

    void
    set_e_values() const
    {
      if (!e_values_set) {
       	er = conic2.r() - conic1.r();
	es = conic2.s() - conic1.s();
	et = conic2.t() - conic1.t();
	eu = conic2.u() - conic1.u();
	ev = conic2.v() - conic1.v();
	ew = conic2.w() - conic1.w();
	e_values_set = true;
      }
    }

    void
    set_helper_ellipse () const
    {
      if (!helper_ellipse_set) {
        helper_ellipse.set_ellipse( conic1, conic2);
        helper_ellipse.analyse();
	CGAL_optimisation_assertion (helper_ellipse.is_ellipse());
	helper_ellipse_set= true;
      }
    }

//    inline
//     void
//     set( const Point&, const Point&,
//          const Point&, const Point&, const Point& p5)
//     {
//         n_boundary_points = 5;
//         conic1.set( conic1, conic2, p5);
//         conic1.analyse();
//     }

    void
    set( const Point&, const Point&,
         const Point&, const Point&, const Point& p5)
    {
        // uses the fact that the conic to be constructed has already
        // been computed in preceding bounded-side test over a 4-point
        // ellipse
        conic1 = helper_conic;
	n_boundary_points = 5;
    }

    // Access functions
    // ----------------
    inline
    int
    number_of_boundary_points( ) const
    {
        return( n_boundary_points);
    }
    
    template <typename DoubleConic_2>
    void
    double_conic(DoubleConic_2& e) const
    {
        CGAL_optimisation_precondition( ! is_degenerate());
    
        double t = 0.0;
    
        if ( n_boundary_points == 4) {
	  set_e_values();
          t = conic1.vol_minimum( er, es, et, eu, ev, ew);
	}
    
        e.set( CGAL::to_double( conic1.r()) + t*CGAL::to_double( er),
               CGAL::to_double( conic1.s()) + t*CGAL::to_double( es),
               CGAL::to_double( conic1.t()) + t*CGAL::to_double( et),
               CGAL::to_double( conic1.u()) + t*CGAL::to_double( eu),
               CGAL::to_double( conic1.v()) + t*CGAL::to_double( ev),
               CGAL::to_double( conic1.w()) + t*CGAL::to_double( ew));
	// actually, we would have to call e.analyse() now to get
	// a clean conic, but since this is only internal stuff
	// right now, the call is omitted to save time    
    }

    // Equality tests
    // --------------
    bool
    operator == ( const Optimisation_ellipse_2<K>& e) const
    {
        if ( n_boundary_points != e.n_boundary_points)
            return( false);
    
        switch ( n_boundary_points) {
          case 0:
            return( true);
          case 1:
            return( boundary_point1 == e.boundary_point1);
          case 2:
            return(    (    ( boundary_point1 == e.boundary_point1)
                         && ( boundary_point2 == e.boundary_point2))
                    || (    ( boundary_point1 == e.boundary_point2)
                         && ( boundary_point2 == e.boundary_point1)));
          case 3:
          case 5:
            return( conic1 == e.conic1);
          case 4:
            return(    (    ( conic1 == e.conic1)
                         && ( conic2 == e.conic2))
                    || (    ( conic1 == e.conic2)
                         && ( conic2 == e.conic1)));
          default:
            CGAL_optimisation_assertion(    ( n_boundary_points >= 0)
                                         && ( n_boundary_points <= 5)); }
        // keeps g++ happy
        return( false);
    }
    
    inline
    bool
    operator != ( const Optimisation_ellipse_2<K>& e) const
    {
        return( ! operator == ( e));
    }

    // Predicates
    // ----------
    inline
    CGAL::Bounded_side
    bounded_side( const Point& p) const
    {
        switch ( n_boundary_points) {
          case 0:
            return( CGAL::ON_UNBOUNDED_SIDE);
          case 1:
            return( ( p == boundary_point1) ?
                           CGAL::ON_BOUNDARY : CGAL::ON_UNBOUNDED_SIDE);
          case 2:
            return(    ( p == boundary_point1)
                    || ( p == boundary_point2)
                    || ( CGAL::are_ordered_along_line(
                             boundary_point1, p, boundary_point2)) ?
                         CGAL::ON_BOUNDARY : CGAL::ON_UNBOUNDED_SIDE);
          case 3:
          case 5:
            return( conic1.convex_side( p));
          case 4: {
            helper_conic.set( conic1, conic2, p);
            helper_conic.analyse();
            if ( !helper_conic.is_ellipse()) {
	        set_helper_ellipse();
                return( helper_ellipse.convex_side( p)); }
            else {
	        set_d_values();
                int tau_star = 
                  helper_conic.vol_derivative( dr, ds, dt, du, dv, dw);
                return( CGAL::Bounded_side( CGAL_NTS sign( tau_star))); } }
          default:
            CGAL_optimisation_assertion( ( n_boundary_points >= 0) &&
                                         ( n_boundary_points <= 5) ); }
        // keeps g++ happy
        return( CGAL::Bounded_side( 0));
    }
    
    inline
    bool
    has_on_bounded_side( const Point& p) const
    {
        return( bounded_side( p) == CGAL::ON_BOUNDED_SIDE);
    }
    
    inline
    bool
    has_on_boundary( const Point& p) const
    {
        return( bounded_side( p) == CGAL::ON_BOUNDARY);
    }
    
    inline
    bool
    has_on_unbounded_side( const Point& p) const
    {
        return( bounded_side( p) == CGAL::ON_UNBOUNDED_SIDE);
    }
    
    inline
    bool
    is_empty( ) const
    {
        return( n_boundary_points == 0);
    }
    
    inline
    bool
    is_degenerate( ) const
    {
        return( n_boundary_points < 3);
    }
};

// Function declarations
// =====================
// I/O
// ---
template < class K_ >
std::ostream&
operator << ( std::ostream&, const CGAL::Optimisation_ellipse_2<K_>&);

template < class K_ >
std::istream&
operator >> ( std::istream&, CGAL::Optimisation_ellipse_2<K_>&);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#  include <CGAL/Optimisation_ellipse_2.C>
#endif

#endif // CGAL_OPTIMISATION_ELLIPSE_2_H

// ===== EOF ==================================================================
