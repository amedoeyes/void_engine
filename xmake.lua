---@diagnostic disable: undefined-global

set_project("void_engine")
set_version("0.1.0")
set_languages("c++20")
set_warnings("allextra", "pedantic", "error")

add_rules("plugin.compile_commands.autoupdate", { lsp = "clangd", outputdir = "build" })
add_rules("mode.release", "mode.debug")

if is_mode("debug") then
	add_defines("DEBUG")
end

add_requireconfs("*", { system = false })
add_requires("glm ^1.0.1", "glfw ^3.4", "glad 0.1.36", "libpng ^1.6.43")
add_requireconfs("glad", { configs = { profile = "core" } })

target("void_engine", {
	kind = "static",
	files = "src/**.cpp",
	includedirs = "include",
	add_packages = { "glfw", "glm", "glad", "libpng" },
})

option("tests", {
	description = "Build the test suite",
	showmenu = true,
	default = false,
	type = "boolean",
})

if has_config("tests") then
	add_requires("catch2 ^3.6.0")

	target("tests", {
		kind = "binary",
		files = "tests/**.cpp",
		includedirs = "include",
		deps = "void_engine",
		packages = "catch2",
	})
end
