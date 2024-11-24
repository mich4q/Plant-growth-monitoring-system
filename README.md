# Optimization of plant growing conditions with ESP32

A system for controlling plant growth conditions in a home greenhouse based on ESP32 with a network interface 

# Functionality
An asynchronous server is created on the ESP32, which starts in access point mode with the name GREENHOUSE. To connect to it, you need to provide a password and then access the webpage at the address greenhouse.local within the local network.

# File structure
```
|
|-- includes
|   |- main.hpp
|   |- network.hpp
|   |- networkPreferences.hpp
|   |- SDcard.hpp
|   |- web.hpp
|
|-- src
|   |
|   |- main.cpp
|   |- network.cpp
|   |- networkPreferences.cpp
|   |- SDcard.cpp
|   |- web.cpp
|
|-- data
|   |
|   |- index.html
|   |- css
|   |   |- main.css
|   |- js
|   |   |- main.js
|   |   |- update.js

|- LICENSE
|- platformio.ini
|- README.md --> This file
```
# Pinout

| MicroSD card       | ESP32         |
|--------------------|---------------|
| CLK                | GPIO 14       |
| CMD                | GPIO 15       |
| DATA0              | GPIO 2        |
| DATA1 / flashlight | GPIO 4        |
| DATA2              | GPIO 12       |
| DATA3              | GPIO 13       |
