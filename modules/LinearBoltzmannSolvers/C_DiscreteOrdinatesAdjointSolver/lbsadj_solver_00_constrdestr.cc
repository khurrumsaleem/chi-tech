#include "lbsadj_solver.h"

#include "ChiObject/object_maker.h"

namespace lbs
{

RegisterChiObject(lbs, DiscreteOrdinatesAdjointSolver);

// ##################################################################
/**Returns the input parameters.*/
chi_objects::InputParameters
DiscreteOrdinatesAdjointSolver::GetInputParameters()
{
  chi_objects::InputParameters params =
    DiscreteOrdinatesSolver::GetInputParameters();

  params.SetGeneralDescription("\\defgroup lbs__DiscreteOrdinatesAdjointSolver "
                               "DiscreteOrdinatesAdjointSolver\n"
                               "\\ingroup lbs__LBSSolver\n"
                               "Adjoint capability");

  params.ChangeExistingParamToOptional("name",
                                       "DiscreteOrdinatesAdjointSolver");

  return params;
}

// ###################################################################
/**Constructor.*/
DiscreteOrdinatesAdjointSolver::DiscreteOrdinatesAdjointSolver(
  const chi_objects::InputParameters& params)
  : lbs::DiscreteOrdinatesSolver(params)
{
  basic_options_.AddOption<std::string>("REFERENCE_RF", std::string());
}

// ###################################################################
/**Constructor.*/
lbs::DiscreteOrdinatesAdjointSolver::DiscreteOrdinatesAdjointSolver(
  const std::string& solver_name)
  : lbs::DiscreteOrdinatesSolver(solver_name)
{
  basic_options_.AddOption<std::string>("REFERENCE_RF", std::string());
}

/**Returns the list of volumetric response functions.*/
const std::vector<lbs::DiscreteOrdinatesAdjointSolver::RespFuncAndSubs>&
lbs::DiscreteOrdinatesAdjointSolver::GetResponseFunctions() const
{
  return response_functions_;
}

} // namespace lbs