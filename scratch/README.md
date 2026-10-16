# Scratch Game

## Overview

This directory documents the Scratch game developed for an interactive STEM workshop using the Scratch-Arduino Bridge.

The initial activity challenged children to connect a cable to a specified Arduino pin as quickly as possible. The game was progressively improved by modifying the Scratch code throughout the workshop, without changing the Python bridge or Arduino firmware.

## Integration

The Scratch game communicates with the Arduino Mega through Scratch cloud variables and the Python bridge.

| Cloud variable | Purpose |
|---|---|
| `ARDUINO` | Sends commands to control the Arduino's built-in LED |
| `SENSOR` | Receives input updates from pin D7 |
| `INPUT1` | Mirrors the state of pin D7 |
| `INPUT2` | Receives input updates from pin D8 |
| `INPUT3` | Receives input updates from pin D9 |
| `INPUT4` | Receives input updates from pin D10 |

## Running the Game

1. Configure the Scratch username and project ID in `bridge/bridge.py`.
2. Upload the Arduino firmware.
3. Start the Python bridge using the instructions in the main README.
4. Open the Scratch project and interact with the game.

## Project File

The original Scratch project can be included in this directory as an `.sb3` file when available.

## Related Documentation

- Main repository README: installation and quick start
- `docs/README.md`: system architecture, pin mapping, and troubleshooting
