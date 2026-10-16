# Technical Documentation

## 1. Overview

The Scratch-Arduino Bridge connects a Scratch project to an Arduino Mega through a Python application. It enables Scratch to control physical hardware and receive input states from the Arduino.

The project was developed for an interactive STEM workshop in which children played a cable-and-pin identification game. Participants had to connect a cable to a specified Arduino pin as quickly as possible. Throughout the workshop, the Scratch game was iteratively improved while the Python bridge and Arduino firmware remained unchanged.

## 2. System Architecture

The system consists of three main components:

1. **Scratch:** provides the interactive game and communicates through cloud variables.
2. **Python bridge:** listens for Scratch cloud-variable updates and exchanges messages with the Arduino over serial communication.
3. **Arduino Mega:** reads digital inputs and controls its built-in LED.

### Communication Flow

**Scratch to Arduino**

Scratch cloud variable `ARDUINO` → Python bridge → USB serial → Arduino built-in LED.

**Arduino to Scratch**

Digital input change → Arduino serial message → Python bridge → Scratch cloud variable.

The bridge uses the `scratchcloud` Python package for Scratch cloud communication and `pyserial` for serial communication.

## 3. Hardware Requirements

- Arduino Mega
- USB cable compatible with the Arduino board
- Computer capable of running Python 3
- Digital input components connected to Arduino pins D7, D8, D9 and D10
- Scratch project configured with the required cloud variables
- Internet connection for Scratch cloud communication

### Pin Mapping

| Arduino pin | Function | Scratch cloud variable |
|---|---|---|
| D7 | First digital input | `SENSOR` and `INPUT1` |
| D8 | Second digital input | `INPUT2` |
| D9 | Third digital input | `INPUT3` |
| D10 | Fourth digital input | `INPUT4` |
| Built-in LED | Output controlled by Scratch | `ARDUINO` |

The four digital inputs use `INPUT_PULLUP`. An input normally reads HIGH and reads LOW when connected to GND. The firmware converts these states into `0` and `1` values for Scratch.

**Wiring safety:** use suitable switches, buttons, or contact components to connect the input pins to GND. Avoid wiring that directly shorts the power supply.

## 4. Software Requirements

- Python 3
- Arduino IDE
- `pyserial`
- `scratchcloud`
- A Scratch account and a project with the required cloud variables

Install the Python dependencies from the repository root:

```bash
python -m pip install -r bridge/requirements.txt
```

The dependencies are listed in `bridge/requirements.txt`.

## 5. Arduino Firmware Setup

1. Connect the Arduino Mega to the computer using USB.
2. Open `arduino/scratch_bridge.ino` in the Arduino IDE.
3. Select the Arduino Mega board and the correct serial port.
4. Upload the sketch to the board.
5. Close the Arduino IDE Serial Monitor before starting the Python bridge, since the serial port should not be occupied by another application.

The Arduino firmware uses a baud rate of **9600**.

### Firmware Behaviour

- Reads digital input pins D7–D10 using `INPUT_PULLUP`.
- Detects changes in each input's state.
- Sends serial messages such as `SENSOR:1` and `INPUT2:0`.
- Uses D7 for both `SENSOR` and `INPUT1`.
- Receives the characters `1` and `0` from Python to turn the built-in LED on and off.
- Uses a short delay to control the main loop's execution rate.

## 6. Python Bridge Configuration

Open `bridge/bridge.py` and configure the following values for your environment:

```python
PORT = "COM7"
BAUD = 9600

USERNAME = "YOUR_SCRATCH_USERNAME"
PROJECT_ID = "YOUR_PROJECT_ID"
```

Replace the example values with your own settings.

- `PORT` must match the serial port assigned to the Arduino. On Windows, this is typically a name such as `COM7`.
- `BAUD` must match the firmware's serial baud rate.
- `USERNAME` identifies the Scratch account.
- `PROJECT_ID` identifies the Scratch project whose cloud variables are used.

The script requests the Scratch password at runtime. Do not hardcode your password or commit credentials to a public repository.

## 7. Scratch Cloud Variables

The Python bridge expects the following cloud variables:

| Variable | Direction | Purpose |
|---|---|---|
| `ARDUINO` | Scratch → Arduino | Sends `1` or `0` to control the built-in LED |
| `SENSOR` | Arduino → Scratch | Reports changes on pin D7 |
| `INPUT1` | Arduino → Scratch | Mirrors the state of pin D7 |
| `INPUT2` | Arduino → Scratch | Reports changes on pin D8 |
| `INPUT3` | Arduino → Scratch | Reports changes on pin D9 |
| `INPUT4` | Arduino → Scratch | Reports changes on pin D10 |

The names must match the variables used in `bridge.py` and the Scratch project.

### Scratch-to-Arduino Commands

When the Scratch cloud variable `ARDUINO` changes:

- `1` is sent to the Arduino to turn on the built-in LED.
- `0` is sent to the Arduino to turn off the built-in LED.

### Arduino-to-Scratch Updates

When an input changes state, the Arduino sends a text message over serial. The Python bridge parses the message and updates the corresponding cloud variable.

Repeated updates with an unchanged value are suppressed by the Python bridge.

## 8. Running the Project

1. Connect the Arduino Mega.
2. Upload `arduino/scratch_bridge.ino`.
3. Verify the serial port configured in `bridge/bridge.py`.
4. Install the dependencies.
5. From the repository root, run:

   ```bash
   python bridge/bridge.py
   ```

6. Enter the Scratch password when prompted.
7. Wait for the connection confirmation in the terminal.
8. Open the Scratch project and test the LED and digital inputs.

Keep the Python bridge running while using the Scratch game.

## 9. Testing and Validation

The bridge was tested successfully with an Arduino Mega and a Scratch project before being used in an interactive STEM workshop.

Testing confirmed the following behaviours:

- **Scratch-to-Arduino communication:** changes to the `ARDUINO` cloud variable sent `1` and `0` commands through Python and controlled the Arduino's built-in LED.
- **Arduino-to-Scratch communication:** changes on digital pin D7 were transmitted through the Python bridge and reflected in the `SENSOR` cloud variable.
- **Serial communication:** the Python bridge connected to the Arduino at 9600 baud and processed incoming serial messages.
- **Terminal feedback:** the bridge displayed connection information and logged cloud-variable updates, making it possible to observe communication during testing.
- **Workshop use:** the bridge supported an interactive cable-and-pin identification game for children.

During the workshop, the Scratch code was progressively improved while the underlying Python bridge and Arduino firmware remained unchanged.

## 10. Troubleshooting

### The Python script cannot open the serial port

- Verify that `PORT` matches the port assigned to the Arduino.
- Check that the Arduino is connected and recognised by the operating system.
- Close the Arduino IDE Serial Monitor and any other program using the same serial port.

### The Scratch connection fails

- Verify the Scratch username and project ID.
- Check the internet connection.
- Confirm that the required cloud variables exist in the Scratch project.
- Ensure that the installed `scratchcloud` package is available and compatible with the script.

### The LED does not respond

- Confirm that the Arduino sketch has been uploaded successfully.
- Check that the Python bridge is running and connected.
- Verify that the Scratch project updates `ARDUINO` with `1` and `0`.
- Inspect the terminal for connection messages and incoming cloud-variable events.

### Input values do not update

- Check the wiring on D7–D10.
- Ensure that the input component connects the relevant pin to GND when activated.
- Confirm that the Arduino is sending serial messages.
- Verify that the message names match the expected cloud-variable names.

### No initial input values appear

The firmware initialises its previous-state variables during startup. It sends updates when it detects a change, rather than automatically publishing every input's initial state.

## 11. Implementation Details and Limitations

- Serial communication uses a fixed baud rate of 9600.
- The current firmware supports four digital inputs.
- D7 is intentionally mapped to both `SENSOR` and `INPUT1`.
- Input updates are event-driven and sent when the firmware detects a state change.
- The Python bridge suppresses duplicate cloud updates when a variable's value has not changed.
- Scratch cloud communication requires an internet connection and a correctly configured project.
- The current implementation controls the Arduino's built-in LED through single-character serial commands.

These details describe the current implementation and should be considered when adapting the bridge to different hardware or Scratch projects.

## 12. Repository Structure

```text
scratch-arduino-bridge/
├── arduino/
│   └── scratch_bridge.ino
├── bridge/
│   ├── bridge.py
│   └── requirements.txt
├── docs/
│   └── README.md
├── media/
│   └── README.md
├── scratch/
│   └── README.md
├── .gitignore
├── LICENSE
└── README.md
```

## License

This project is distributed under the MIT License. See the repository's `LICENSE` file for the full terms.
