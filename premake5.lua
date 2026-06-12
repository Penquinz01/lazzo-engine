workspace "Lazzo"
architecture "x64"

configurations {
    "Debug",
    "Release",
    "Dist"
}

SDL3_DIR = "Lazzo/vendor/SDL3"
Inc_Dir = {}
Inc_Dir["ImGui"] = "Lazzo/vendor/imgui"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project "Lazzo"
location "Lazzo"
kind "SharedLib"
language "C++"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "lzpch.h"
pchsource "Lazzo/src/lzpch.cpp"

files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",

    "%{prj.name}/vendor/glad/src/glad.c",

    "%{Inc_Dir.ImGui}/imgui.cpp",
    "%{Inc_Dir.ImGui}/imgui_draw.cpp",
    "%{Inc_Dir.ImGui}/imgui_tables.cpp",
    "%{Inc_Dir.ImGui}/imgui_widgets.cpp",
    "%{Inc_Dir.ImGui}/backends/imgui_impl_sdl3.cpp",
    "%{Inc_Dir.ImGui}/backends/imgui_impl_opengl3.cpp",

}
filter { "files:Lazzo/vendor/imgui/**.cpp" }
enablepch "Off"

filter { "files:Lazzo/vendor/glad/src/glad.c" }
enablepch "Off"

filter {}


includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{prj.name}/vendor/SDL3/include",
    "%{prj.name}/vendor/glad/include",
    "%{Inc_Dir.ImGui}/",
    "%{Inc_Dir.ImGui}/backends"

}
libdirs {
    "%{SDL3_DIR}/lib/x64",
}

links {
    "SDL3",
}

filter "system:windows"
cppdialect "C++17"
staticruntime "On"
systemversion "latest"
characterset("Unicode")
buildoptions { "/utf-8" }

defines {
    "LZ_PLATFORM_WINDOWS",
    "LZ_BUILD_DLL",
    "_WINDLL"
}

postbuildcommands {
    ('{COPY} "%{cfg.buildtarget.abspath}" "%{wks.location}/bin/' .. outputdir .. '/Sandbox"'),
    ('{COPY} "%{wks.location}/%{SDL3_DIR}/lib/x64/SDL3.dll" "%{wks.location}/bin/' .. outputdir .. '/Sandbox"')
}


filter "configurations:Debug"
defines "LZ_DEBUG"
symbols "On"
filter "configurations:Release"
defines "LZ_RELEASE"
optimize "On"
filter "configurations:Dist"
defines "LZ_DIST"
optimize "On"

filter {}
project "SandBox"
location "SandBox"
kind "ConsoleApp"
language "C++"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"
}

includedirs {
    "%{prj.name}/../Lazzo/vendor/spdlog/include",
    "%{prj.name}/../Lazzo/vendor/SDL3/include",
    "%{prj.name}/../Lazzo/vendor/glad/include",
    "%{Inc_Dir.ImGui}/",
    "%{Inc_Dir.ImGui}/backends",
    "Lazzo/src",
}
links {
    "Lazzo",
    "opengl32",
}

filter "system:windows"
cppdialect "C++17"
staticruntime "On"
systemversion "10.0.26100.0"
characterset("Unicode")
buildoptions { "/utf-8" }

defines {
    "LZ_PLATFORM_WINDOWS",
}



filter "configurations:Debug"
defines "LZ_DEBUG"
symbols "On"
filter "configurations:Release"
defines "LZ_RELEASE"
optimize "On"
filter "configurations:Dist"
defines "LZ_DIST"
optimize "On"
