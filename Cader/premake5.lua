include("external")

project("Cader")
	kind("StaticLib")
	language("C++")
	cppdialect("C++17")
	staticruntime("Off")

	targetdir("%{wks.location}/Build/%{prj.name}/Binary/%{cfg.buildcfg}/")
	objdir("%{wks.location}/Build/%{prj.name}/Intermediate/%{cfg.buildcfg}/")

	debugdir("%{wks.location}/Build/%{prj.name}/Binary/%{cfg.buildcfg}/")

	floatingpoint("Fast")

	files{
		"Include/**.h",
		"Source/**.h",
		"Source/**.cpp"
	}

	removefiles{
		"Source/**/Platform/**.h",
		"Source/**/Platform/**.cpp"
	}

	includedirs{
		"Include/",
		"%{Glm.Include}",
		"%{Entt.Include}",
		"%{Glfw.Include}",
		"%{Vulkan.Include}"
	}

	links{
		"%{Glfw.Lib}",
		"%{Vulkan.Lib}"
	}

	filter("configurations:Debug")
		optimize("Off")
		symbols("On")
		runtime("Debug")
		defines{
			"_DEBUG",
			"CDR_DEBUG"
		}

	filter("configurations:Release")
		optimize("On")
		symbols("Off")
		runtime("Release")
		defines{
			"NDEBUG",
			"CDR_RELEASE"
		}

	filter("configurations:Final")
		optimize("Full")
		symbols("Off")
		runtime("Release")
		defines{
			"NDEBUG",
			"CDR_FINAL"
		}

	filter("system:Windows")
		files{
			"Source/**/Platform/Win/**.h",
			"Source/**/Platform/Win/**.cpp"
		}