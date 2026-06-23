# Smart Study Desk

An IoT device built on TivaC Launchpad that monitors the study environment, tracks focus sessions via Pomodoro, and uploads real-time analytics to ThingsBoard.

## 🚀 Features (Roadmap)
- **Environment Monitoring:** Temperature, Humidity, and Ambient Light tracking.
- **Focus Productivity:** Embedded Pomodoro Timer with Focus Score algorithm.
- **Cloud Connectivity:** Telemetry data streaming via MQTT over WiFi.
- **Remote Management:** Over-the-Air Firmware Updates (FOTA) support.

## 📂 Project Structure
- `/core`: Core application logic, finite state machines, and data structures (Platform-agnostic C code).
- `/drivers`: TivaC hardware-specific peripheral drivers (UART, ADC, I2C, Flash).

## 📅 Daily Changelog
- **Day 1:** Initialize repository, structure setup, and pointer-based sensor mockup.
- **Day 2:** Implement nested struct Environment_t and sensor update wrapper function
