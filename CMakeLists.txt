PROJECT(cad_project)

add_subdirectory(Render)
add_subdirectory(Common)
add_subdirectory(Test)
add_subdirectory(EularOperation)
add_subdirectory(Modeling)
add_subdirectory(Files)

set(LIBS RENDER COMMON EO MODELING FILES TEST ${GL_LIBS})

add_executable(test_1 Test/test.cpp)

target_link_libraries(test_1 ${LIBS})