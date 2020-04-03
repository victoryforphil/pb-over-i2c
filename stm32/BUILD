cc_binary(
    name = "main",
    srcs = ["main.c"],
    linkopts = ["-L /home/alex/stm32/stm32f7-bazel/STM32F767ZI-Nucleo/Demonstrations/SW4STM32/STM32767ZI_Nucleo/ -T STM32F767ZITx_FLASH.ld", "-lc", "-lm", "-lnosys"],
    deps=[ "//sys:sym32_sys","//cubemx:all", ],
    linkstatic=1
)