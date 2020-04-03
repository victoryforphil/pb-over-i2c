# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "all",
    deps = [":nucleo_144"],
    
    visibility = ['//visibility:public']
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "startup",
    srcs = ["CMSIS/Device/ST/STM32F7xx/Source/Templates/gcc/startup_stm32f767xx.s"],
    linkstatic = 1,

)
cc_library(
    name = "nucleo_144",
    srcs = glob(["BSP/STM32F7xx_Nucleo_144/*.c"]),
    hdrs = glob(["BSP/STM32F7xx_Nucleo_144/*.h"]),
    copts =["-Icubemx/BSP/STM32F7xx_Nucleo_144"],
    strip_include_prefix = "BSP/STM32F7xx_Nucleo_144",
    visibility = ['//visibility:public'],
    deps=[":hal_driver"]
)

cc_library(
    name = "hal_driver",
    srcs = glob(["STM32F7xx_HAL_Driver/Src/*.c"]),
    hdrs = glob(["STM32F7xx_HAL_Driver/Inc/*.h",  "STM32F7xx_HAL_Driver/Inc/Legacy/*.h"]),
    copts =["-Icubemx/STM32F7xx_HAL_Driver/Inc"],
    strip_include_prefix = "STM32F7xx_HAL_Driver/Inc/",
    deps=[":cmsis_device"],
    visibility = ['//visibility:public']
)

cc_library(
    name = "cmsis_device",
    srcs = ["CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.c"],
    hdrs = glob(["CMSIS/Device/ST/STM32F7xx/Include/*.h"]),
    copts =["-Icubemx/CMSIS/Device/ST/STM32F7xx/Include"],
    deps = ["//cubemx/CMSIS/Include:cmsis_includes", ":startup"],
    strip_include_prefix = "CMSIS/Device/ST/STM32F7xx/Include",
    visibility = ['//visibility:public'],
    linkstatic = 1
)




