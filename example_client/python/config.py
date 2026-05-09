from pydantic_settings import BaseSettings


class ServerConfig(BaseSettings):
    HOST_ADDRESS: str = "localhost"
    MEMORY_LIMIT: int = 1024  # Byte

class ClientConfig(BaseSettings):
    SERVER_IP: str = "http://localhost:8080"
