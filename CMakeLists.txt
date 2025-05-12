# 최소 CMake 버전 지정
cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 지정
project(ConsoleTetrisGame VERSION 1.0)

# C++ 표준 지정 (예: C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# 실행 파일 이름 지정 및 소스 파일 추가
# 여기에 프로젝트의 모든 .cpp 파일을 나열해야 합니다.
add_executable(${PROJECT_NAME}
    main.cpp
    # 필요한 다른 .cpp 파일을 여기에 추가...
)

# 헤더 파일 경로 지정 (컴파일러가 .h 파일을 찾을 경로)
# src 폴더와 하위 모델, 뷰, 컨트롤러 폴더를 포함하도록 설정합니다.
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/Model
    ${PROJECT_SOURCE_DIR}/src/View
    ${PROJECT_SOURCE_DIR}/src/Controller
)

# (선택 사항) 라이브러리 연결
# 만약 ncurses (콘솔 그래픽/입력 라이브러리) 등을 사용한다면 여기에 링크합니다.
# 예: find_package(ncurses REQUIRED)
#     target_link_libraries(${PROJECT_NAME} PRIVATE ncurses)

# (선택 사항) 빌드 결과 파일이 생성될 디렉토리 설정
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)