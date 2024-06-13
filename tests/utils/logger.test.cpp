#include "void_engine/utils/logger.hpp"

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>

using namespace void_engine::utils;

TEST_CASE("Logger", "[utils][logger]") {
	const std::ostringstream oss_out;
	const std::ostringstream oss_err;
	const auto old_cout = std::cout.rdbuf(oss_out.rdbuf());
	const auto old_cerr = std::cerr.rdbuf(oss_err.rdbuf());
	Logger::set_log_level(LogLevel::debug);

	SECTION("Debug") {
		Logger::debug("debug message");
		REQUIRE(oss_out.str() == "[DEBUG]: debug message\n");
		REQUIRE(oss_err.str() == "");
	}

	SECTION("Info") {
		Logger::info("info message");
		REQUIRE(oss_out.str() == "[INFO]: info message\n");
		REQUIRE(oss_err.str() == "");
	}

	SECTION("Warning") {
		Logger::warning("warning message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "[WARNING]: warning message\n");
	}

	SECTION("Error") {
		Logger::error("error message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "[ERROR]: error message\n");
	}

	SECTION("Debug with arguments") {
		Logger::debug("debug message {}", 1);
		REQUIRE(oss_out.str() == "[DEBUG]: debug message 1\n");
		REQUIRE(oss_err.str() == "");
	}

	SECTION("Info with arguments") {
		Logger::info("info message {}", 2);
		REQUIRE(oss_out.str() == "[INFO]: info message 2\n");
		REQUIRE(oss_err.str() == "");
	}

	SECTION("Warning with arguments") {
		Logger::warning("warning message {}", 3);
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "[WARNING]: warning message 3\n");
	}

	SECTION("Error with arguments") {
		Logger::error("error message {}", 4);
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "[ERROR]: error message 4\n");
	}

	SECTION("Level none") {
		Logger::set_log_level(LogLevel::none);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "");
	}

	SECTION("Level debug") {
		Logger::set_log_level(LogLevel::debug);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(
			oss_out.str() == "[DEBUG]: debug message\n[INFO]: info message\n"
		);
		REQUIRE(
			oss_err.str() ==
			"[WARNING]: warning message\n[ERROR]: error message\n"
		);
	}

	SECTION("Level info") {
		Logger::set_log_level(LogLevel::info);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(oss_out.str() == "[INFO]: info message\n");
		REQUIRE(
			oss_err.str() ==
			"[WARNING]: warning message\n[ERROR]: error message\n"
		);
	}

	SECTION("Level warning") {
		Logger::set_log_level(LogLevel::warning);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(
			oss_err.str() ==
			"[WARNING]: warning message\n[ERROR]: error message\n"
		);
	}

	SECTION("Level error") {
		Logger::set_log_level(LogLevel::error);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "[ERROR]: error message\n");
	}

	std::cout.rdbuf(old_cout);
	std::cerr.rdbuf(old_cerr);
}
