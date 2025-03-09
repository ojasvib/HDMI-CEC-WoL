# HDMI-CEC-WoL
HDMI-CEC to Wake-on-LAN (WoL)

This project listens for HDMI-CEC power-on signals and triggers Wake-on-LAN (WoL) to automatically wake a connected device, such as a PC or media server.
Features

    Detects TV power-on events using HDMI-CEC
    Sends a Wake-on-LAN (WoL) packet to a predefined MAC address
    Runs on Linux-based devices, including Raspberry Pi
    Uses libcec for HDMI-CEC interaction and raw sockets for WoL transmission

Requirements

    Raspberry Pi / Linux Machine
    libcec (HDMI-CEC library)
    C++ Compiler (g++)
    Wake-on-LAN enabled on the target device

Installation

    Install libcec if not already installed:

sudo apt-get install libcec-dev

Clone the repository:

git clone https://github.com/yourusername/hdmi-cec-wol.git
cd hdmi-cec-wol

Compile the program:

    g++ -o hdmi_cec_wol src/main.cpp -lcec

Usage

    Run the program:

    sudo ./hdmi_cec_wol

    Turn on the TV. The system will detect the HDMI-CEC event and send a Wake-on-LAN packet to wake the target machine.

Configuration

    Update the MAC address in main.cpp inside the sendWOL function.
    Modify the HDMI device name in main.cpp to match your setup.

Architecture

The system consists of:

    An HDMI-CEC listener that detects when the TV is powered on.
    A Wake-on-LAN sender that broadcasts a magic packet to wake a specific device.

Why This Matters

This implementation enables automated device wake-up, optimizing energy efficiency and enhancing smart home integration. It is particularly useful for media setups where a PC or server should turn on when the TV is powered up.
