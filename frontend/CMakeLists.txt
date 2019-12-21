aux_source_directory(. FRONT_SRC)
include_directories(../utils/include)
add_library(frontend ${FRONT_SRC})
