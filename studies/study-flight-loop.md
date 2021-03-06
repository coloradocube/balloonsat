# Study: Flight Loop

The purpose is to understand how they manage the number of tasks that need to be performed during operation. 

## 1. SOTA

### 1.1. OreSat

1. OreSat uses a lot of small processors to perform local tasks on their boards.
2. OreSat uses Linux daemons to run high-level processes.

## 2. Requirements

### 2.1. Power and system

1. Headless start with WiFi AP for admin.
2. Graceful power-down on low-battery.
3. Monitor and manage the lifecycle of sub-processes/threads.
4. Monitor telemetry for critical conditions (e.g. motion vs rest).
5. Monitor power level.
6. Monitor available memory.
7. Monitor Iridium channel for uplink availability and commands.
8. Monitor temperature.
9. Log telemetry and events.
10. Pack and send selected telemetry and events over RockBLOCK.

### 2.2. GPS

1. Set and verify Flight Mode.

### 2.3. RockBLOCK

1. Buffer and queue messages.
2. Callback for commands.

### 2.4. Web service

1. In the domain `msusat.org`.
2. Setup up RockBLOCK msgs forward.
3. Live visualization of flight path, telemetry, and health.

### 2.5. Cameras

1. Separate storage partition on SD card.
2. Stream through WiFi (Ground Mode) or record to SD card (Flight Mode).

### 2.6. Sensorium

1. Log sensorium with current timestamp.
2. Flag "interesting" log lines to send over Iridium.

### 2.7. Telemetry

## Givens

1. 4-core processor (Broadcom BCM2711 SoC with a 1.5 GHz 64-bit quad-core ARM Cortex-A72 processor, with 1 MB shared L2 cache).
2.  

