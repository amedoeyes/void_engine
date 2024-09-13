---@diagnostic disable: undefined-global, undefined-field

set_project("void_engine")
set_version("0.1.0")
set_languages("c++26")
set_warnings("allextra", "pedantic", "error")

add_rules("mode.debug", "mode.release", "mode.releasedbg", "mode.check", "mode.profile")
add_rules("plugin.compile_commands.autoupdate", { lsp = "clangd", outputdir = "build" })

if is_mode("debug") then
	add_defines("DEBUG")
end

add_defines("GLM_ENABLE_EXPERIMENTAL")

add_requireconfs("*", { system = false })
add_requires({
	"glm ^1.0.1",
	"glfw ^3.4",
	"glad ^0.1.36",
	"libpng ^1.6.43",
})
add_requireconfs("glad", {
	configs = { profile = "core" },
})

target("void_engine", function()
	set_kind("static")
	add_rules("utils.glsl2spv", { outputdir = "build/shaders", targetenv = "opengl", bin2c = true })
	add_files({
		"src/**.cpp",
		"resources/shaders/**.vert",
		"resources/shaders/**.frag",
	})
	add_includedirs("include")
	add_packages({ "glfw", "glm", "glad", "libpng" })
end)

option("tests", {
	description = "Build the test suite",
	showmenu = true,
	default = false,
	type = "boolean",
})

option("examples", {
	description = "Build the examples",
	showmenu = true,
	default = false,
	type = "boolean",
})

if has_config("examples") then
	for _, example in ipairs(os.files("examples/*.cpp")) do
		local name = path.basename(example)
		target(name, {
			kind = "binary",
			files = example,
			includedirs = "include",
			deps = "void_engine",
			packages = { "glfw", "glm", "glad", "libpng" },
		})
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
