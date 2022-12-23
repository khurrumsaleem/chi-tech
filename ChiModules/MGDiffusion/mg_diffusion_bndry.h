#ifndef MG_DIFFUSION_BOUNDARY_H
#define MG_DIFFUSION_BOUNDARY_H

#include "array"

namespace mg_diffusion
{
  class Boundary;
  
  enum class BoundaryType : int
  {
    Reflecting = 1,
    Dirichlet  = 2,
    Neumann    = 3,
    Robin      = 4,
    Vacuum     = 5
  };
}

//###################################################################
/**Parent class for diffusion boundaries*/
class mg_diffusion::Boundary
{
  public :
  BoundaryType type = BoundaryType::Dirichlet;

  // std::array<std::vector<double>, 3> mg_values2;
  std::array<double, 3> mg_values = {0.,0.,0.};

};


// //###################################################################
// /**Robin boundary condition is a natural (i.e., weak) boundary condition of
// // the form
//  *
// \f[
// a \phi + b D \hat{n}\cdot \nabla \phi = f
// \f]
// When \f$ a=0\f$ the boundary condition is equivalent to a <B>Neumann</B>
// boundary condition.
// \f[
// b D\hat{n}\cdot \nabla \phi = f
// \f]
//  When \f$ a=\frac{1}{4} \f$, \f$ b=\frac{1}{2} \f$
// and \f$ f=0 \f$ then the boundary condition is equivalent to a
// <B>Vacuum</B> boundary condition.
// \f[
// \frac{1}{4}\phi + \frac{1}{2}D\hat{n}\cdot \nabla \phi = 0
// \f]
//  */
// However, one should not set \f$b=0$\f in the hopes of obtaining a
// <B>Dirichlet</B> boundary condition as this type of boundary condition is
// strongly imposed in a different implementation.

#endif //MG_DIFFUSION_BOUNDARY_H