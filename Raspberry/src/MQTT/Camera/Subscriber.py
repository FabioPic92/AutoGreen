import asyncio
from aiomqtt import Client 

async def main():
    async with Client("localhost") as client:
        # Si sottoscrive al topic
        await client.subscribe("test/topic")
        print("In ascolto su 'test/topic'")

        # Itera sui messaggi ricevuti
        async for message in client.messages:
            print(f"Ricevuto: {message.payload.decode()}")

if __name__ == "__main__":
    asyncio.run(main())