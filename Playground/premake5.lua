project("Playground")
	language("C++")
	cppdialect("C++17")
	staticruntime("Off")

	targetdir("%{wks.location}/Build/%{prj.name}/Binary/%{cfg.buildcfg}/")
	objdir("%{wks.location}/Build/%{prj.name}/Intermediate/%{cfg.buildcfg}/")

	debugdir("%{wks.location}/Build/%{prj.name}/Binary/%{cfg.buildcfg}/")

	floatingpoint("Fast")

	files{
		"Source/**.h",
		"Source/**.cpp"
	}

	includedirs{
		"%{wks.location}/Cader/Include/",
		"%{Glm.Include}"
	}

	links{
		"Cader"
	}

	filter("configurations:Debug")
		kind("ConsoleApp")
		optimize("Off")
		symbols("On")
		runtime("Debug")
		defines{
			"_DEBUG",
			"CDR_DEBUG"
		}

	filter("configurations:Release")
		kind("ConsoleApp")
		optimize("On")
		symbols("Off")
		runtime("Release")
		defines{
			"NDEBUG",
			"CDR_RELEASE"
		}

	filter("configurations:Final")
		kind("WindowedApp")
		optimize("Full")
		symbols("Off")
		runtime("Release")
		defines{
			"NDEBUG",
			"CDR_FINAL"
		}