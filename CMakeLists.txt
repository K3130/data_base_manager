add_library(data_base_manager
  include/data_base_common.h
  include/data_base_file_solution.h
  include/data_base_log_solution.h
  include/data_base_manage_solution.h
  include/data_base_request_solution.h
  src/data_base_file_solution.cpp
  src/data_base_log_solution.cpp
  src/data_base_manage_solution.cpp
  src/data_base_request_solution.cpp
)

target_link_libraries(data_base_manager Qt${QT_VERSION_MAJOR}::Sql)

