# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

# idf_component_register(SRCS ${app_sources})

idf_component_register(SRCS "main.c"
							"bsp/bsp.c"
							"bsp/audio_mem.c"
							"bsp/audio_mutex.c"
							"bsp/i2c_bus.c"
							"bsp/bsp_lsm6dsox.c"
							"components/lsm6dsox/lsm_driver.c"
							"components/lsm6dsox/lsm_configuration.c"
                    		INCLUDE_DIRS "." "./bsp" "./components" "./components/lsm6dsox")
