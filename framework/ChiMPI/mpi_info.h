#ifndef CHITECH_MPI_INFO_H
#define CHITECH_MPI_INFO_H

#include <mpi.h>
#include <set>

class chi;

namespace chi_objects
{

//################################################################### Class def
/**An object for storing various MPI states.*/
class MPI_Info
{
  friend class ::chi;
private:
  int location_id_ = 0;
  int process_count_ = 1;

  bool location_id_set_ = false;
  bool process_count_set_ = false;

public:
  const int& location_id = location_id_;     ///< Current process rank.
  const int& process_count = process_count_; ///< Total number of processes.

private:
  MPI_Info() = default;
public:
  static MPI_Info& GetInstance() noexcept;

public:
  MPI_Info(const MPI_Info&) = delete;           //Deleted copy constructor
  MPI_Info operator=(const MPI_Info&) = delete; //Deleted assigment operator

protected:
  void SetLocationID(int in_location_id);
  void SetProcessCount(int in_process_count);

};

}//namespace chi_objects

#endif //CHITECH_MPI_INFO_H