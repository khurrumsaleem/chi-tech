#include "lbs_solver.h"

#include "ChiMesh/MeshHandler/chi_meshhandler.h"

#include "ChiLog/chi_log.h"

//###################################################################
/**Performs general input checks before initialization continues.*/
void lbs::LBSSolver::PerformInputChecks()
{
  if (groups_.empty())
  {
    chi::log.LogAllError()
      << "LinearBoltzmann::SteadyStateSolver: No groups added to solver.";
    chi::Exit(EXIT_FAILURE);
  }

  num_groups_ = groups_.size();

  if (groupsets_.empty())
  {
    chi::log.LogAllError()
      << "LinearBoltzmann::SteadyStateSolver: No group-sets added to solver.";
    chi::Exit(EXIT_FAILURE);
  }
  int grpset_counter=0;
  for (auto& group_set : groupsets_)
  {
    if (group_set.groups_.empty())
    {
      chi::log.LogAllError()
        << "LinearBoltzmann::SteadyStateSolver: No groups added to groupset "
        << grpset_counter << ".";
      chi::Exit(EXIT_FAILURE);
    }
    ++grpset_counter;
  }
  if (options_.sd_type == chi_math::SpatialDiscretizationType::UNDEFINED)
  {
    chi::log.LogAllError()
      << "LinearBoltzmann::SteadyStateSolver: No discretization_ method set.";
    chi::Exit(EXIT_FAILURE);
  }

  grid_ptr_ = chi_mesh::GetCurrentHandler().GetGrid();

  if (grid_ptr_ == nullptr)
  {
    chi::log.LogAllError()
      << "LinearBoltzmann::SteadyStateSolver: No grid_ptr_ available from region.";
    chi::Exit(EXIT_FAILURE);
  }

  //======================================== Determine geometry type
  using namespace chi_mesh;
  const auto grid_attribs = grid_ptr_->Attributes();
  if (grid_attribs & DIMENSION_1)
    options_.geometry_type = GeometryType::ONED_SLAB;
  if (grid_attribs & DIMENSION_2)
    options_.geometry_type = GeometryType::TWOD_CARTESIAN;
  if (grid_attribs & DIMENSION_3)
    options_.geometry_type = GeometryType::THREED_CARTESIAN;

}