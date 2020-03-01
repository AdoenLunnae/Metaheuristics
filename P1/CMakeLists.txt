cmake_minimum_required(VERSION 3.10)

set(SRC_DIR "src")

include_directories(${SRC_DIR}/include)

set(SOURCE_NAMES seeds Timer MQKPInstance MQKPSolution MQKPSolGenerator MQKPEvaluator)

set(SOURCE_FILES "")

foreach(name ${SOURCE_NAMES})
	list(APPEND SOURCE_FILES ${SRC_DIR}/${name}.cpp)
endforeach(name)

add_executable(P1Metaheuristics ${SRC_DIR}/main.cpp ${SOURCE_FILES})
