import pytest
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from client import MSBackendClient


@pytest.fixture
async def client():
    """
    Async fixture for MSBackendClient
    """
    async with MSBackendClient() as client:
        yield client

@pytest.fixture
async def client():
    """
    Fixture client
    """
    async with MSBackendClient() as client:
        yield client

@pytest.fixture
def sample_files() -> dict[str, str]:
    """
    Example with sample files for sync
    """

    return {"mod1.txt": "hash_123", "mod2.txt": "hash_456"}


@pytest.fixture
def sample_filenames() -> list[str]:
    """
    Example with sample files for download
    """

    return ["mod1.txt", "mod2.txt"]
