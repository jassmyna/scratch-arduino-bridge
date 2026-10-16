from scratchcloud import CloudClient, CloudChange
import serial
import asyncio
import time

PORT = "COM7"
BAUD = 9600

USERNAME = "username"
PROJECT_ID = "YOUR_PROJECT_ID"

arduino = serial.Serial(
    PORT,
    BAUD,
    timeout=0.1
)

time.sleep(2)

print("Arduino conectat pe COM7")

client = CloudClient(
    USERNAME,
    PROJECT_ID
)

last_values = {}


async def update_cloud(name, value):

    if last_values.get(name) != value:

        print(
            f"Arduino -> Scratch: "
            f"{name} = {value}"
        )

        await client.set_cloud(
            name,
            value
        )

        last_values[name] = value


async def read_arduino():

    while True:

        if arduino.in_waiting > 0:

            message = (
                arduino.readline()
                .decode(errors="ignore")
                .strip()
            )

            if ":" in message:

                name, value = message.split(
                    ":",
                    1
                )

                if name in (
                    "SENSOR",
                    "INPUT1",
                    "INPUT2",
                    "INPUT3",
                    "INPUT4"
                ):

                    await update_cloud(
                        name,
                        value
                    )

        await asyncio.sleep(0.02)


@client.event
async def on_connect():

    print()
    print("Conectat la Scratch!")
    print("============================")
    print("WORKSHOP BRIDGE READY")
    print("============================")
    print("D7  -> SENSOR + INPUT1")
    print("D8  -> INPUT2")
    print("D9  -> INPUT3")
    print("D10 -> INPUT4")
    print("============================")
    print()

    asyncio.create_task(
        read_arduino()
    )


@client.event
async def on_message(
    cloud: CloudChange
):

    if cloud.name == "ARDUINO":

        value = str(cloud.value)

        print(
            f"Scratch -> Arduino: "
            f"ARDUINO = {value}"
        )

        if value == "1":
            arduino.write(b"1")

        elif value == "0":
            arduino.write(b"0")


password = input("Parola Scratch: ")

client.run(password)

scratch_bridge.ino idk which would be it
