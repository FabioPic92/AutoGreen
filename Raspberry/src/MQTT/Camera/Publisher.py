import asyncio
import json
from aiomqtt import Client

async def main():
    async with Client("localhost") as client:
        while True:
            payload = {
                "speed": speed,
                "duration": duration,
                "direction": direction
            }
            
            data = json.dumps(payload)

            await client.publish("arduino/camera", data)

if __name__ == "__main__":
    asyncio.run(main())