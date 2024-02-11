#ifndef SAVEDCONFIG_HPP_
#define SAVEDCONFIG_HPP_

#include <cstdint>
#include <optional>
#include <string>

#include <EEPROM.h>

#include "MachineConfig.hpp"
#include "conf.hpp"

namespace fablabbg
{

  struct SavedConfig
  {
    static constexpr auto FIELD_LENGTH = 40;
    static constexpr auto INT_LENGTH = 5;      // Must save as string for WiFiManager
    static constexpr auto MAGIC_NUMBER = 0x45; // Increment when changing the struct

    // Magic number to check if the EEPROM is initialized
    mutable uint8_t magic_number{0};

    /// @brief WiFi SSID
    char ssid[FIELD_LENGTH]{0};

    /// @brief WiFi password
    char password[FIELD_LENGTH]{0};

    /// @brief MQTT server
    char mqtt_server[FIELD_LENGTH]{0};

    /// @brief MQTT username
    char mqtt_user[FIELD_LENGTH]{0};

    /// @brief MQTT password
    char mqtt_password[FIELD_LENGTH]{0};

    /// @brief MQTT topic for mqtt switch (if available)
    char machine_topic[FIELD_LENGTH]{0};

    /// @brief Machine ID connected to the board
    char machine_id[INT_LENGTH]{0};

    /// @brief Saves the configuration to EEPROM
    /// @return true if successful
    bool SaveToEEPROM() const;

    std::string toString() const;

    constexpr SavedConfig() = default;

    /// @brief Loads the configuration from EEPROM if available and matching revision number
    /// @return std::nullopt if not valid, SavedConfig otherwise
    static std::optional<SavedConfig> LoadFromEEPROM();

    /// @brief Returns the default configuration built from conf.hpp and secrets.hpp
    static SavedConfig DefaultConfig();
  };

} // namespace fablabbg
#endif // SAVEDCONFIG_HPP_