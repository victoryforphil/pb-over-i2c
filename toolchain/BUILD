package(default_visibility = ['//visibility:public'])


filegroup(name ="empty")
cc_toolchain_suite(
    name = "arm-none-eabi",
    toolchains = {
        "stm32f7": ":arm-none-eabi_toolchain",
    },
)

cc_toolchain(
    name = "arm-none-eabi_toolchain",
    toolchain_identifier = "arm-none-eabi-toolchain",
    toolchain_config = ":arm-none-eabi_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)

load(":cc_toolchain_config_arm_none_eabi.bzl", "cc_toolchain_config_eabi")
cc_toolchain_config_eabi(name = "arm-none-eabi_toolchain_config")



cc_toolchain_suite(
    name = "aarch64-linux-gnu",
    toolchains = {
        "arm64": ":aarch64-linux-gnu_toolchain",
    },
)

cc_toolchain(
    name = "aarch64-linux-gnu_toolchain",
    toolchain_identifier = "aarch64-linux-gnu-toolchain",
    toolchain_config = ":aarch64-linux-gnu_toolchain_config",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
)

load(":cc_toolchain_config_aarch64-linux-gnu.bzl", "cc_toolchain_config_aarch64")
cc_toolchain_config_aarch64(name = "aarch64-linux-gnu_toolchain_config")


