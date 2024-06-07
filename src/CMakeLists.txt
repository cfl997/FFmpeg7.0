cmake_minimum_required(VERSION 3.18)


include_directories(
	"${ffmpeg_ROOT_DIR}/include"
)

link_directories(
	${ffmpeg_ROOT_DIR}/lib/win64/
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	${ffmpeg_ROOT_DIR}/third/ffmpeg7.0/Debug/
else()
	${ffmpeg_ROOT_DIR}/third/ffmpeg7.0/Release/
endif()
)

set(common_header
	${ffmpeg_ROOT_DIR}/include/ffmpeg.h
)

set(common_src
	01-FFmpeg_information.cpp
	02-Video_Information.cpp
	03-Decode_video_stream.cpp
)


#SET_PROPERTY(TARGET ${PROJECT_NAME} PROPERTY FOLDER "gTest")


# 遍历每个源文件，生成相应的可执行文件
foreach(src ${common_src})
    # 获取源文件的文件名（不带扩展名）
    get_filename_component(exe_name ${src} NAME_WE)
    
    # 添加可执行文件
    add_executable(${exe_name} ${src})
    
   # 获取所有Debug库文件
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    file(GLOB DEBUG_LIBS "${ffmpeg_ROOT_DIR}/third/ffmpeg7.0/Debug/*.lib")
    target_link_libraries(${exe_name} ${DEBUG_LIBS})
else()
    # 获取所有Release库文件
    file(GLOB RELEASE_LIBS "${ffmpeg_ROOT_DIR}/third/ffmpeg7.0/Release/*.lib")
    target_link_libraries(${exe_name} ${RELEASE_LIBS})
endif()
endforeach()