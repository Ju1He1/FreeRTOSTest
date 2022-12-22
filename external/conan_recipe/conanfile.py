from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout
from conan.tools.scm import Git


class FreeRTOSConan(ConanFile):
    name = "FreeRTOS"
    version = "0.3"

    # Optional metadata
    license = "Apache 2.0"
    author = "Julian Heni"
    url = "https://github.com/Ju1He1/FreeRTOSTest.git"
    description = "FreeRTOS as a conan 3rd party"
    topics = ("FreeRTOS", "c", "c++")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False],
               "fPIC": [True, False],
               "BUILD_TARGET": [True, False]
               }
    default_options = {"shared": False,
                       "fPIC": True,
                       "BUILD_TARGET": False}
    generators = "CMakeDeps"
    # build_policy = "always"  # for better debugging always build freertos

    def source(self):
        git = Git(self)
        # check out tagged version
        clone_args = ["-b main"]
        git.clone(url="https://github.com/Ju1He1/FreeRTOSTest.git", args=clone_args)

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        if self.options.BUILD_TARGET:
            print("Building target")
            tc.cache_variables["BUILD_TARGET"] = "ON"
            tc.cache_variables["BUILD_SIMULATION"] = "OFF"
            del self.options.fPIC

        else:
            print("Building simulation")
            tc.cache_variables["BUILD_TARGET"] = "OFF"
            tc.cache_variables["BUILD_SIMULATION"] = "ON"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_script_folder="freertos")
        cmake.build()
        cmake.test(build_type=self.settings.build_type, target="FreeRTOS")

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["FreeRTOS"]
        self.cpp_info.includedirs = ["include"]
