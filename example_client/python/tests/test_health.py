from http import HTTPStatus

import pytest


@pytest.mark.asyncio
async def test_health_endpoint_returns_ok(client):
    """
    Check endpoint /health
    """
    status, data = await client.health()

    assert status == HTTPStatus.OK
    assert "status" in data
    assert data["status"] == "ok"


@pytest.mark.asyncio
async def test_health_response_format(client):
    """
    Check response format /health
    """
    _, data = await client.health()

    assert isinstance(data, dict[str, str])
    assert "status" in data
    assert isinstance(data["status"], str)
