workspace("Cader")
	architecture("x64")
	configurations{
		"Debug", "Release", "Final"
	}

	startproject("Playground")

include("external")

include("Cader")
include("Playground")