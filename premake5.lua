workspace("Cader")
	architecture("x64")
	configurations{
		"Debug", "Release", "Final"
	}

	startproject("Playground")

include("Cader")
include("Playground")