---@diagnostic disable: undefined-global

add_requires("catch2 ^3.6.0")

target("tests", {
	kind = { "binary" },
	files = { "./**/*.cpp" },
	includedirs = { "../include" },
	deps = { "void_engine" },
	packages = { "catch2" },
})
