#ifndef CONF_H_
#define CONF_H_

#include <cstdint>
#include <string>
#include <chrono>

using namespace std::chrono_literals;
using namespace std::chrono;

namespace fablabbg
{
  namespace conf::whitelist
  {
    static constexpr uint8_t LEN = 10U;         /* Maximum number of whitelisted cards */
    static constexpr uint8_t UID_BYTE_LEN = 4U; /* Number of bytes in RFID cards UID */
    static constexpr uint8_t CACHE_LEN = 10U;   /* Number of bytes in RFID cards UID */
  }
  namespace conf::lcd
  {
    static constexpr uint8_t ROWS = 2U;  /* Number of rows for LCD display */
    static constexpr uint8_t COLS = 16U; /* Number of cols for LCD display */
  }
  namespace conf::machine
  {
    static constexpr auto DEFAULT_AUTO_LOGOFF_DELAY = 8h; /* User will be log out after this delay. If 0h, no auto-logout. This may be overriden by backend data */
    static constexpr auto BEEP_PERIOD = 1min;             /* Device will beep before auto-poweroff. If 0min, no beeping.  */
    static constexpr auto POWEROFF_GRACE_PERIOD = 1min;   /* Idle time before poweroff. If 0min, machine will stay on. */
    static constexpr auto DELAY_BETWEEN_BEEPS = 30s;      /* Beeps will be heard every 30s when the machine is about to shutdown */
    static constexpr bool MAINTENANCE_BLOCK = true;       /* If true, machine needing maintenance will be blocked for normal users */

    static constexpr bool USE_MQTT_RELAY = true; /* If true, the machine will use MQTT relay to control the machine */
    static constexpr bool USE_RELAY = false;     /* If true, the machine will use relay to control the machine */

    static_assert(USE_MQTT_RELAY ^ USE_RELAY);
    static_assert(BEEP_PERIOD <= POWEROFF_GRACE_PERIOD);
    static_assert(DELAY_BETWEEN_BEEPS < BEEP_PERIOD);
  }

  namespace conf::debug
  {
    static constexpr bool ENABLE_LOGS = true;                 /* True to add logs */
    static constexpr bool ENABLE_TASK_LOGS = false;           /* True to add logs */
    static constexpr unsigned long SERIAL_SPEED_BDS = 115200; /* Serial speed in bauds */
  }
  namespace conf::buzzer
  {
    static constexpr unsigned short LEDC_PWM_CHANNEL = 0U; /* Esp32 pwm channel for beep generation */
    static constexpr auto STANDARD_BEEP_DURATION = 200ms;  /* Beep duration, typical value 200ms */
    static constexpr unsigned int BEEP_HZ = 660U;
  }
  namespace conf::tasks
  {
    static constexpr auto RFID_CHECK_PERIOD = 150ms;  /* Task period to check for RFID badge (should be fast: 150ms) */
    static constexpr auto RFID_SELFTEST_PERIOD = 60s; /* Performs RFID self check and reset chip if necessary (default: 60s) */
    static constexpr auto MQTT_REFRESH_PERIOD = 30s;  /* Query the MQTT broker for machine state at given period (default: 30s) */
    static constexpr auto WATCHDOG_TIMEOUT = 30s;     /* Timeout for hardware watchdog set to 0s to disable (default: 30s) */
    static_assert(WATCHDOG_TIMEOUT == 0s || WATCHDOG_TIMEOUT > 10s);
  }

  namespace conf::mqtt
  {
    static constexpr std::string_view topic = "/machine";        /* Initial part of the topic, machine ID will be added */
    static constexpr std::string_view response_topic = "/reply"; /* Server reply (sub-topic of the full machine topic) */
  }
} // namespace fablabbg
#endif // CONF_H_