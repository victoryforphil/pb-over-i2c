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
            path = "/usr/bin/aarch64-linux-gnu-gcc",
        ),
  
        tool_path(
            name = "ld",
            path = "/usr/bin/aarch64-linux-gnu-ld",
        ),
        tool_path(
            name = "ar",
            path = "/usr/bin/aarch64-linux-gnu-ar",
        ),
        tool_path(
            name = "cpp",
            path = "/usr/bin/aarch64-linux-gnu-cpp",
        ),
        tool_path(
            name = "gcov",
            path = "/usr/bin/aarch64-linux-gnu-gcov",
        ),
        tool_path(
            name = "nm",
            path = "/usr/bin/aarch64-linux-gnu-nm",
        ),
        tool_path(
            name = "objdump",
            path = "/usr/bin/aarch64-linux-gnu-objdump",
        ),
        tool_path(
            name = "strip",
            path = "/usr/bin/aarch64-linux-gnu-strip",
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

                            "-std=c++11",
                            "-lstdc++"
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
                            "-lstdc++",
                            "-Wl,--gc-sections"
                        ],
                    ),
                ],
            ),
        ],
    )

    cxx_builtin_include_directories = [
        "/usr/aarch64-linux-gnu/include/c++/5/",
        "/usr/aarch64-linux-gnu/include/c++/5/backward",
        "/usr/aarch64-linux-gnu/include/",
        "/usr/lib/gcc-cross/aarch64-linux-gnu/7/include",
        "/usr/lib/gcc-cross/aarch64-linux-gnu/7/include-fixed"
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = "aarch64-linux-gnu-toolchain",
        cxx_builtin_include_directories = cxx_builtin_include_directories,
        host_system_name = "i686-unknown-linux-gnu",
        target_system_name = "aarch64-linux-gnu",
        target_cpu = "arm64",
        target_libc = "unknown",
        compiler = "aarch64-linux-gnu",
        abi_version = "unknown",
        abi_libc_version = "unknown",
        tool_paths = tool_paths,

        features = [toolchain_compile_features, toolchain_link_features],
    )

cc_toolchain_config_aarch64 = rule(
    implementation = _impl,
    attrs = {},
    provides = [CcToolchainConfigInfo],
)