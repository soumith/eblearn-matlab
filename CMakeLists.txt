project(eblearn_matlab_wrapper)

add_executable(eblearn_matlab_example main.cpp)
target_link_libraries(eblearn_matlab_example idx matio)
