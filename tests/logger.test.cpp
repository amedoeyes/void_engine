#include "void_engine/logger.hpp"

#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace void_engine;

TEST_CASE("Logger", "[logger]") {
	std::ostringstream oss_out;
	std::ostringstream oss_err;

	auto old_cout = std::cout.rdbuf(oss_out.rdbuf());
	auto old_cerr = std::cerr.rdbuf(oss_err.rdbuf());

	Logger::set_log_level(Logger::LogLevel::debug);

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

	SECTION("Set level none") {
		Logger::set_log_level(Logger::LogLevel::none);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "");
	}

	SECTION("Set level debug") {
		Logger::set_log_level(Logger::LogLevel::debug);
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

	SECTION("Set level info") {
		Logger::set_log_level(Logger::LogLevel::info);
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

	SECTION("Set level warning") {
		Logger::set_log_level(Logger::LogLevel::warning);
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

	SECTION("Set level error") {
		Logger::set_log_level(Logger::LogLevel::error);
		Logger::debug("debug message");
		Logger::info("info message");
		Logger::warning("warning message");
		Logger::error("error message");
		REQUIRE(oss_out.str() == "");
		REQUIRE(oss_err.str() == "[ERROR]: error message\n");
	}

	Logger::set_log_level(Logger::LogLevel::debug);

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

	std::cout.rdbuf(old_cout);
	std::cerr.rdbuf(old_cerr);
}