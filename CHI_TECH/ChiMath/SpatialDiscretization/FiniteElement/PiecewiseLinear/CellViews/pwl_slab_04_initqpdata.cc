#include "pwl_slab.h"

void SlabPWLFEView::InitializeQuadraturePointData(
  chi_math::finite_element::InternalQuadraturePointData& internal_data,
  std::vector<chi_math::finite_element::FaceQuadraturePointData>& faces_qp_data)
{
  auto& vol_quadrature = default_volume_quadrature;

  //=================================== Determine number of internal qpoints
  size_t ttl_num_vol_qpoints = vol_quadrature.qpoints.size();

  //=================================== Init volumetric quadrature
  internal_data.quadrature_point_indices.reserve(ttl_num_vol_qpoints);
  for (unsigned int qp=0; qp<ttl_num_vol_qpoints; ++qp)
    internal_data.quadrature_point_indices.push_back(qp);

  internal_data.m_shape_value.reserve(num_nodes);
  internal_data.m_shape_grad.reserve(num_nodes);
  internal_data.m_JxW.reserve(num_nodes);
  for (size_t i=0; i < num_nodes; i++)
  {
    VecDbl  node_shape_value;
    VecVec3 node_shape_grad;

    node_shape_value.reserve(ttl_num_vol_qpoints);
    node_shape_grad.reserve(ttl_num_vol_qpoints);

    for (size_t qp=0; qp<ttl_num_vol_qpoints; ++qp)
    {
      node_shape_value.push_back(SlabShape(i,qp));
      node_shape_grad.emplace_back(0.0,                //x
                                   0.0,                //y
                                   SlabGradShape(i));  //z
    }//for qp

    internal_data.m_shape_value.push_back(node_shape_value);
    internal_data.m_shape_grad.push_back(node_shape_grad);
  }//for i

  internal_data.m_JxW.reserve(ttl_num_vol_qpoints);
  double J = h/2.0;
  for (size_t qp=0; qp<ttl_num_vol_qpoints; ++qp)
  {
    double w = vol_quadrature.weights[qp];
    internal_data.m_JxW.push_back(J * w);
  }//for qp
  internal_data.face_dof_mappings = face_dof_mappings;
  internal_data.num_nodes = num_nodes;
  internal_data.initialized = true;

  //=================================== Init surface quadrature
  size_t num_srf_qpoints = 1;
  faces_qp_data.resize(2);

  for (unsigned int f=0; f<2; ++f)
  {
    auto& face_qp_data = faces_qp_data[f];

    size_t ttl_num_face_qpoints = num_srf_qpoints;

    face_qp_data.quadrature_point_indices.reserve(ttl_num_face_qpoints);
    for (unsigned int qp=0; qp<ttl_num_face_qpoints; ++qp)
      face_qp_data.quadrature_point_indices.push_back(qp);

    for (size_t qp=0; qp<ttl_num_face_qpoints; ++qp)
      face_qp_data.m_normals.push_back(normals[f]);

    face_qp_data.m_shape_value.reserve(num_nodes);
    face_qp_data.m_shape_grad.reserve(num_nodes);
    for (size_t i=0; i < num_nodes; i++)
    {
      VecDbl  node_shape_value;
      VecVec3 node_shape_grad;

      node_shape_value.reserve(ttl_num_face_qpoints);
      node_shape_grad.reserve(ttl_num_face_qpoints);

      for (size_t qp=0; qp<num_srf_qpoints; ++qp)
      {
        node_shape_value.push_back(SlabShape(i,qp,true));
        node_shape_grad.emplace_back(0.0,                //x
                                     0.0,                //y
                                     SlabGradShape(i));  //z
      }//for qp
      face_qp_data.m_shape_value.push_back(node_shape_value);
      face_qp_data.m_shape_grad.push_back(node_shape_grad);
    }//for i

    face_qp_data.m_JxW.reserve(ttl_num_face_qpoints);
    for (size_t qp=0; qp<num_srf_qpoints; ++qp)
    {
      double w = 1.0;
      face_qp_data.m_JxW.push_back(1.0 * w);
    }
    face_qp_data.face_dof_mappings = face_dof_mappings;
    face_qp_data.num_nodes = 1;
    face_qp_data.initialized = true;
  }//for face
}