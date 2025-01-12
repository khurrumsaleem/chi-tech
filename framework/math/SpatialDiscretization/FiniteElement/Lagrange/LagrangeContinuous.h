#ifndef CHITECH_LAGRANGECONTINUOUS_H
#define CHITECH_LAGRANGECONTINUOUS_H

#include "LagrangeBase.h"

namespace chi_math::spatial_discretization
{

/**Generalization of the Galerkin Finite Element Method
 * with Lagrange basis functions
 * for use by a Continues Finite Element Method (CFEM).
 * \ingroup doc_SpatialDiscretization*/
class LagrangeContinuous : public LagrangeBase
{
public:
  // prevent anything else other than a shared pointer
  static std::shared_ptr<LagrangeContinuous>
  New(const chi_mesh::MeshContinuum& grid,
      QuadratureOrder q_order = QuadratureOrder::SECOND,
      CoordinateSystemType cs_type = CoordinateSystemType::CARTESIAN);

  // 03
  void
  BuildSparsityPattern(std::vector<int64_t>& nodal_nnz_in_diag,
                       std::vector<int64_t>& nodal_nnz_off_diag,
                       const UnknownManager& unknown_manager) const override;

  // 04 Mappings
  int64_t MapDOF(const chi_mesh::Cell& cell,
                 unsigned int node,
                 const UnknownManager& unknown_manager,
                 unsigned int unknown_id,
                 unsigned int component) const override;

  int64_t MapDOFLocal(const chi_mesh::Cell& cell,
                      unsigned int node,
                      const UnknownManager& unknown_manager,
                      unsigned int unknown_id,
                      unsigned int component) const override;

  int64_t MapDOF(const chi_mesh::Cell& cell, unsigned int node) const override
  {
    return MapDOF(cell, node, UNITARY_UNKNOWN_MANAGER, 0, 0);
  }
  int64_t MapDOFLocal(const chi_mesh::Cell& cell,
                      unsigned int node) const override
  {
    return MapDOFLocal(cell, node, UNITARY_UNKNOWN_MANAGER, 0, 0);
  }

  size_t GetNumGhostDOFs(const UnknownManager& unknown_manager) const override;

  std::vector<int64_t>
  GetGhostDOFIndices(const UnknownManager& unknown_manager) const override;

protected:
  // 02
  void OrderNodes();

  std::map<uint64_t, int64_t> node_mapping_;
  std::map<uint64_t, int64_t> ghost_node_mapping_;

private:
  // 00
  explicit LagrangeContinuous(const chi_mesh::MeshContinuum& grid,
                              QuadratureOrder q_order,
                              CoordinateSystemType cs_type);
};

} // namespace chi_math::spatial_discretization

#endif // CHITECH_LAGRANGECONTINUOUS_H
