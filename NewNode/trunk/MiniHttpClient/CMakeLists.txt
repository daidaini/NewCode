cmake_minimum_required(VERSION 2.8)

#工程名
SET(PROJECT_NAME "MiniHttpClient")
project(${PROJECT_NAME})

#宏定义，添加一个包
#soure_name：是一个不带双引号的字符
#soure_dir：是一个不带引号的路径
macro(add_source soure_name soure_dir)
    include_directories(${soure_dir})
    set(hfind ${ARGV1})
    string(APPEND hfind "/*.h")
    set(hppfind ${ARGV1})
    string(APPEND hppfind "/*.hpp")
    set(cppfind ${ARGV1})
    string(APPEND cppfind "/*.cpp")
    set(cfind ${ARGV1})
    string(APPEND cfind "/*.c")
    file(GLOB name_header ${hfind})
    file(GLOB name_hpp ${hppfind})
    file(GLOB name_cpp ${cppfind})
    file(GLOB name_c ${cfind})
    set(all_file ${all_file} ${name_hpp} ${name_header} ${name_cpp} ${name_c})
    source_group(${ARGV0} FILES ${name_hpp} ${name_header} ${name_cpp} ${name_c})
endmacro(add_source)

#定义变量BIT 32位还是64位
if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	SET(BIT 64)
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
	SET(BIT 32)
endif ( CMAKE_SIZEOF_VOID_P EQUAL 8 )


if(WIN32)
    #windows上使用静态编译
    set(CompilerFlags
    CMAKE_CXX_FLAGS
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE)
    foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach()
endif(WIN32)

#添加包
add_source(${PROJECT_NAME} ./src)
add_source(mongoose ../../source/mongoose)


#添加库目录
#link_directories(${PROJECT_NAME} /curl/lib)

#添加资源文件
#set(rc_file ${rc_file} "./src/MDLL_API.rc")

#添加宏
#add_definitions("-D#define")


#添加工程
#add_library(${PROJECT_NAME} SHARED ${rc_file} ${all_file})
add_executable(${PROJECT_NAME} ${all_file})

#链接库
#target_link_libraries(${PROJECT_NAME} **.lib)