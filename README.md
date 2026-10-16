# Scratch-Arduino Bridge

A Python bridge connecting Scratch cloud variables to an Arduino Mega over serial communication. Designed for interactive STEM workshops, this project lets Scratch control physical hardware while Arduino inputs send information back to Scratch.

## Features

- Bidirectional communication between Scratch and Arduino
- Scratch cloud-variable integration using `scratchcloud`
- Serial communication at 9600 baud
- Digital inputs on Arduino pins D7–D10
- Built-in LED control from Scratch
- Suitable for interactive educational demonstrations

## System Architecture

Scratch project ↔ Scratch cloud variables ↔ Python bridge ↔ USB serial ↔ Arduino Mega

## Hardware

- Arduino Mega
- USB cable
- Digital input components connected to pins D7, D8, D9 and D10
- Computer running Python

The inputs use `INPUT_PULLUP`. Connect each input pin to GND to activate it.

## Software Requirements

- Python 3
- Arduino IDE
- `pyserial`
- `scratchcloud`
- A Scratch project configured with the required cloud variables

## Installation

1. Clone or download this repository.
2. Install the Python dependencies:

   ```bash
   pip install -r bridge/requirements.txt
   ```

3. Open `arduino/scratch_bridge.ino` in the Arduino IDE.
4. Upload the sketch to your Arduino Mega.
5. Configure `bridge/bridge.py` with your Scratch username, project ID and Arduino serial port.
6. Ensure the Scratch project has the cloud variables required by the bridge.

## Running the Bridge

Run the Python script:

```bash
python bridge/bridge.py
```

Enter your Scratch password when prompted. Do not save your password in the source code or commit it to GitHub.

## Communication

| Arduino pin | Scratch cloud variable |
|---|---|
| D7 | `SENSOR` and `INPUT1` |
| D8 | `INPUT2` |
| D9 | `INPUT3` |
| D10 | `INPUT4` |

The Scratch cloud variable `ARDUINO` sends `1` or `0` commands to control the Arduino's built-in LED.

## Important Notes

- Update the serial port in `bridge/bridge.py` to match your computer.
- Scratch cloud variables must be configured in the Scratch project.
- Test the bridge with your hardware before using it in a workshop.
- Never commit account passwords or other secrets.

## License

This project is licensed under the MIT License.
