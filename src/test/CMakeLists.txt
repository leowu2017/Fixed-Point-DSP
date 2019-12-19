cmake_minimum_required(VERSION 3.6.3)

enable_testing()
find_package(GTest REQUIRED)

add_executable(
	imfp_test
	${CMAKE_CURRENT_LIST_DIR}/number_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/conversion_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/dsp_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/main.cpp
)
target_link_libraries(imfp_test GTest::GTest GTest::Main)
#target_include_directories(imfp_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

set_property(TARGET imfp_test PROPERTY CXX_STANDARD 17)

add_test(all_tests imfp_test)
