import asyncio
from aiomqtt import Client 

async def main():
    async with Client("localhost") as client:
        await client.subscribe("arduino/camera")
        print("In ascolto su 'test/topic'")

        async for message in client.messages:
            print(f"Ricevuto: {message.payload.decode()}")

if __name__ == "__main__":
    asyncio.run(main())