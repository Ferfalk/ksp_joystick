# ksp_joystick

## USB Joystick for Kerbal Space Program (KSP) using D400B-M4 and Arduino Pro Micro

This project allows you to use a custom-built USB joystick for **Kerbal Space Program** (KSP) by interfacing a **D400B-M4** joystick with an **Arduino Pro Micro**. The joystick can be mapped to control various in-game axes (such as pitch, yaw, and roll) along with a button for quick commands.

### Key Features:

- Uses an **Arduino Pro Micro** for USB HID support.
- Interfaces with the **D400B-M4** joystick for analog input axes (X, Y, Rz) and a button.
- Includes deadzone handling for smoother controls.
- Fully configurable for other games or applications using HID joystick input.

### Installation:

1. Upload the provided Arduino sketch to your Arduino Pro Micro.
2. Connect the **D400B-M4** joystick to the appropriate analog and digital pins on the Arduino:
   - X-axis to A0
   - Y-axis to A1
   - Rz-axis to A2
   - Button to 2
3. Launch **Kerbal Space Program** and configure your joystick through the game’s settings.
