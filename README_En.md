# TFT Touch Menu with Buttons

This project is designed to manage a menu on a TFT display using touch inputs. You can navigate through the menu and select different items using touch interactions.

## Installation and Setup

### Required Hardware:
- Arduino (e.g., ESP32)
- TFT display with touch capability
- Touch sensor

### Connections:
- TFT display connected to the appropriate SPI or parallel pins
- Touch sensor connected to SDA (pin 39), SCL (pin 42), INT (pin 40), and optional RST

### Libraries:
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [bb_captouch](https://github.com/someone/bb_captouch) (replace with actual link if available)
- Wire (included with Arduino IDE)

## How to Use

1. Upload the code to your Arduino.
2. Make the hardware connections as described above.
3. The menu will be displayed on the TFT screen, and you can navigate through it using touch inputs.

## Main Functions

### setup()

- Initializes the TFT display and sets up the touch sensor.
- Displays the initial menu and buttons on the screen.

### loop()

- Continuously checks for touch inputs.
- Updates the display based on touch interactions.

### handleTouch(int x, int y)

- Handles touch events and updates the button states based on the touch coordinates.

### TextShow()

- Displays static text on the TFT screen.

### buttonShow()

- Displays a circular button on the TFT screen, indicating the power state.

### MenuShow(int num)

- Displays the menu buttons on the TFT screen.
- Updates the menu button colors based on their states.

### drawSmoothRoundRect(int x, int y, int w, int h, int r, uint16_t color1, uint16_t color2)

- Draws a smooth rounded rectangle with a gradient effect.

## Author

This project was created by [mobinAlijani](https://github.com/mobinAlijani).

## License

This project is licensed under the MIT License. For more information, see the [LICENSE](LICENSE) file.
