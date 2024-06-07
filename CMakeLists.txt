cmake_minimum_required(VERSION 3.18)

project(ffmpeg7.0)

set(CMAKE_CXX_STANDARD 17)

set(ffmpeg_ROOT_DIR ${PROJECT_SOURCE_DIR})

message("ffmpeg_ROOT_DIR " ${ffmpeg_ROOT_DIR})
message ("cmake_build_type : " ${CMAKE_BUILD_TYPE})


#list(APPEND CMAKE_MODULE_PATH "${XCG_ROOT_DIR}/cmake/")

set(CMAKE_DEBUG_POSTFIX "D") 

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(CG_MODULE_SUFFIX ${CMAKE_DEBUG_POSTFIX})
	add_definitions("-D_DEBUG")
	add_definitions("-DDEBUG")
else()
	set(CG_MODULE_SUFFIX "")
endif()


SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${ffmpeg_ROOT_DIR}/bin64/")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${ffmpeg_ROOT_DIR}/lib/win64/")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${ffmpeg_ROOT_DIR}/bin64/")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${ffmpeg_ROOT_DIR}/lib/win64/")

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${ffmpeg_ROOT_DIR}/bin64/")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${ffmpeg_ROOT_DIR}/lib/win64/")

add_definitions("-DUNICODE -D_UNICODE") #定义后,字符串使用wchar_t类型

include_directories(
	${ffmpeg_ROOT_DIR}/third/ffmpeg7.0/include
)

#Filter
SET(CG_HEADER_FILES "HeaderFiles")
SET(CG_SOURCE_FILES "SourceFiles")


add_subdirectory ("src")



