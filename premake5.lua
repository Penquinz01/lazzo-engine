workspace "Lazzo"
architecture "x64"

configurations {
    "Debug",
    "Release",
    "Dist"
}

SDL3_DIR = "Lazzo/vendor/SDL3"

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
    "%{prj.name}/src/**.cpp"
}

includedirs {
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{prj.name}/vendor/SDL3/include",
    "%{prj.name}/vendor/glad/include",
}
libdirs{
    "%{SDL3_DIR}/lib/x64",
}

links{
    "SDL3",
}

filter "system:windows"
    cppdialect "C++17"
    staticruntime "On"
    systemversion "latest"
    characterset ("Unicode")
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
        "Lazzo/src",
    }
    links{
        "Lazzo",
        "opengl32",
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "10.0.26100.0"
        characterset ("Unicode")
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
