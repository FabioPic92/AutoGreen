import asyncio
from aiomqtt import Client

async def main():
    async with Client("localhost") as client:
        while True:
            msg = input("Messaggio per Arduino > ").strip()
            if msg.lower() in ['exit', 'quit']:
                break
            await client.publish("arduino/camera", msg.encode())

if __name__ == "__main__":
    asyncio.run(main())