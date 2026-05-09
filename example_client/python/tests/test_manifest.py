from http import HTTPStatus

import pytest


@pytest.mark.asyncio
async def test_manifest_endpoint_returns_ok(client):
    """
    Check endpoint /manifest
    """
    status, data = await client.manifest()

    assert status == HTTPStatus.OK
    assert "files" in data


@pytest.mark.asyncio
async def test_manifest_returns_list(client):
    """
    Check response list of file /manifest
    """
    _, data = await client.manifest()

    assert isinstance(data["files"], list)


@pytest.mark.asyncio
async def test_manifest_each_file_has_name_and_hash(client):
    """
    Check structure of file in /manifest
    """
    _, data = await client.manifest()

    for file_info in data["files"]:
        assert "name" in file_info
        assert "hash" in file_info
        assert isinstance(file_info["name"], str)
        assert isinstance(file_info["hash"], str)
