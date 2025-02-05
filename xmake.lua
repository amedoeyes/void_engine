set_project("void_engine")
set_version("0.1.0")
set_languages("cxx23")
set_warnings("allextra", "pedantic")

set_toolchains("clang")
set_runtimes("c++_shared")

add_rules("mode.debug", "mode.release", "mode.releasedbg", "mode.check", "mode.profile", "mode.valgrind")
add_rules("plugin.compile_commands.autoupdate", { lsp = "clangd", outputdir = "build" })

if is_mode("debug") or is_mode("check") then
	add_defines("DEBUG")
end

if is_mode("release") then
	set_policy("build.optimization.lto", true)
end

add_defines("GLM_ENABLE_EXPERIMENTAL")

add_requireconfs("*", { system = false })
add_requires("glfw", { version = "^3" })
add_requires("glad", { version = "0.1.36", configs = { profile = "core" } })
add_requires("glm", { version = "^1", configs = { modules = true } })
add_requires("freetype", { version = "^2" })
add_requires("harfbuzz", { version = "^9" }) -- TODO: update to v10
add_requires("libpng", { version = "^1" })

target("embed", function()
	set_kind("static")
	add_rules("utils.glsl2spv", { targetenv = "opengl", client = "opengl100", bin2c = true })
	add_rules("utils.bin2c", { extensions = { ".ttf" } })
	add_files(
		"./resources/embed.cpp",
		"./resources/shaders/**.vert",
		"./resources/shaders/**.frag",
		"./resources/fonts/**.ttf"
	)
	add_includedirs("./resources/", { public = true })
end)

target("void_engine", function()
	set_kind("static")
	add_files("./src/**.cpp")
	add_files("./src/**.cppm", { public = true })
	add_packages("glfw", "glad", "glm", "libpng", "freetype", "harfbuzz", { public = true })
	add_deps("embed")
end)

option("tests", {
	description = "Build test suite",
	showmenu = true,
	default = false,
	type = "boolean",
})

option("examples", {
	description = "Build examples",
	showmenu = true,
	default = false,
	type = "boolean",
})

if has_config("examples") then
	for _, example in ipairs(os.files("examples/*.cpp")) do
		target(path.basename(example), { files = example, deps = "void_engine" })
	end
end

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
