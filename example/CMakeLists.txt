cmake_minimum_required(VERSION 3.8)


add_executable(example-basic "example.basic.cpp")
target_link_libraries(example-basic PRIVATE "${NAME_LIB_MAIN}")


add_executable(example-struct "example.struct.cpp")
target_link_libraries(example-struct PRIVATE "${NAME_LIB_MAIN}")


add_executable(example-struct_nodefctor "example.struct_nodefctor.cpp")
target_link_libraries(example-struct_nodefctor PRIVATE "${NAME_LIB_MAIN}")


add_executable(example-std-string "example.std.string.cpp")
target_link_libraries(example-std-string PRIVATE "${NAME_LIB_MAIN}")


add_executable(example-std "example.std.cpp")
target_link_libraries(example-std PRIVATE "${NAME_LIB_MAIN}")


add_executable(example-exception_handling "example.exception_handling.cpp")
target_link_libraries(example-exception_handling PRIVATE "${NAME_LIB_MAIN}")


add_executable(test-kurisu-exception "test.kurisu.exception.cpp")
target_link_libraries(test-kurisu-exception PRIVATE "${NAME_LIB_MAIN}")
