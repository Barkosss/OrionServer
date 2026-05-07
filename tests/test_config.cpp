// tests/test_config.cpp
#include<gtest/gtest.h>
#include "../src/config/Config.h"
#include<fstream>
#include<nlohmann/json.hpp>

class ConfigTest : public ::testing::Test {
protected:
    void SetUp() override {
        nlohmann::json testConfig;
        testConfig["mode"] = "allowlist";
        testConfig["mods_directory"] = "./tests/fixtures/test_mods";
        testConfig["client_only"] = {"minimap.jar", "jei.jar"};
        testConfig["server_only"] = {"sponge.jar"};
        testConfig["blacklist"] = {"broken.jar"};
        
        std::ofstream file("test_config.json");
        file << testConfig.dump();
        file.close();
    }
    
    void TearDown() override {
        std::remove("test_config.json");
        //Config::reset();
    }
};

TEST_F(ConfigTest, LoadsConfigFromFile) {
    Config::getInstance().reload("test_config.json");
    
    EXPECT_EQ(Config::getInstance().getModsDir(), "./tests/fixtures/test_mods");
    EXPECT_TRUE(Config::getInstance().isAllowList());
    EXPECT_FALSE(Config::getInstance().isBlockList());
}

TEST_F(ConfigTest, FiltersClientOnlyFiles) {
    Config::getInstance().reload("test_config.json");
    
    EXPECT_TRUE(Config::getInstance().shouldSendToClient("minimap.jar"));
    EXPECT_TRUE(Config::getInstance().shouldSendToClient("jei.jar"));
}

TEST_F(ConfigTest, FiltersServerOnlyFiles) {
    Config::getInstance().reload("test_config.json");
    
    EXPECT_FALSE(Config::getInstance().shouldSendToClient("sponge.jar"));
}

TEST_F(ConfigTest, FiltersBlacklistedFiles) {
    Config::getInstance().reload("test_config.json");
    
    EXPECT_FALSE(Config::getInstance().shouldSendToClient("broken.jar"));
}

TEST_F(ConfigTest, DefaultModeWhenNotSpecified) {
    nlohmann::json minimal;
    minimal["mods_directory"] = "./mods";
    
    std::ofstream file("minimal_config.json");
    file << minimal.dump();
    file.close();
    
    Config::getInstance().reload("minimal_config.json");
    
    EXPECT_TRUE(Config::getInstance().isAllowList());
    
    std::remove("minimal_config.json");
}