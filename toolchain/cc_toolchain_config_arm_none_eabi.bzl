load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)
def _impl(ctx):
    tool_paths = [
        tool_path(
            name = "gcc",
            path = "/usr/bin/arm-none-eabi-gcc",
        ),
  
        tool_path(
            name = "ld",
            path = "/usr/bin/arm-none-eabi-ld",
        ),
        tool_path(
            name = "ar",
            path = "/usr/bin/arm-none-eabi-ar",
        ),
        tool_path(
            name = "cpp",
            path = "/usr/bin/arm-none-eabi-cpp",
        ),
        tool_path(
            name = "gcov",
            path = "/usr/bin/arm-none-eabi-gcov",
        ),
        tool_path(
            name = "nm",
            path = "/usr/bin/arm-none-eabi-nm",
        ),
        tool_path(
            name = "objdump",
            path = "/usr/bin/arm-none-eabi-objdump",
        ),
        tool_path(
            name = "strip",
            path = "/usr/bin/arm-none-eabi-strip",
        ),
    ]
    toolchain_compile_features = feature(
        name = "toolchain_mcu_features",
        enabled = True,

        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.assemble,
                    ACTION_NAMES.preprocess_assemble,
                    ACTION_NAMES.linkstamp_compile,
                    ACTION_NAMES.c_compile,
                    ACTION_NAMES.cpp_compile,
                    ACTION_NAMES.cpp_header_parsing,
                    ACTION_NAMES.cpp_module_compile,
                    ACTION_NAMES.cpp_module_codegen,
                    ACTION_NAMES.lto_backend,
                    ACTION_NAMES.clif_match,
                ],
                flag_groups = [
                    flag_group(
                        flags = [

                            "-mcpu=cortex-m4",
                            "-mthumb",
                            "-mfloat-abi=hard",
                            "-mfpu=fpv4-sp-d16",
                            "-fdata-sections",
                            "-ffunction-sections",
                            "-DHEAP_SIZE=0x400",
                            "-DSTM32",
                            "-DSTM32F7",
                            "-DSTM32F767xx",
                            "-specs=nosys.specs",
                        ],
                    ),
                ],
            ),
        ],
    )

    toolchain_link_features = feature(
        name = "toolchain_link_features",
        enabled = True,

        flag_sets = [
            flag_set(
                actions = [
                    ACTION_NAMES.cpp_link_executable ,
                    ACTION_NAMES.cpp_link_dynamic_library  ,
                    ACTION_NAMES.cpp_link_nodeps_dynamic_library  ,
                ],
                flag_groups = [
                    flag_group(
                        flags = [
                            
                            "-mcpu=cortex-m4",
                            "-mthumb",
                            "-mfloat-abi=hard",
                            "-mfpu=fpv4-sp-d16",
                            "-specs=nano.specs",
                            "-specs=nosys.specs",
                            "-Wl,--gc-sections",
                            "-L /home/alex/stm32/stm32f7-bazel/STM32F767ZI-Nucleo/Demonstrations/SW4STM32/STM32767ZI_Nucleo/ -T STM32F767ZITx_FLASH.ld", "-lc", "-lm", "-lnosys"
                        ],
                    ),
                ],
            ),
        ],
    )

    cxx_builtin_include_directories = [
        "/usr/arm-none-eabi/include/",
        "/usr/lib/gcc/arm-none-eabi/6.3.1/include/",
        "/usr/lib/gcc/arm-none-eabi/6.3.1/include-fixed/",
        "/usr/include",
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = "arm-none-eabi-toolchain",
        cxx_builtin_include_directories = cxx_builtin_include_directories,
        host_system_name = "i686-unknown-linux-gnu",
        target_system_name = "arm-none-eabi",
        target_cpu = "stm32f7",
        target_libc = "unknown",
        compiler = "gcc-arm-none-eabi",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,

        features = [toolchain_compile_features, toolchain_link_features],
    )

cc_toolchain_config_eabi = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)