from http import HTTPStatus

import pytest


@pytest.mark.asyncio
async def test_sync_endpoint_accepts_post(client, sample_files):
    """
    Check GET /sync
    """
    status, data = await client.sync(sample_files)

    assert status == HTTPStatus.OK
    assert "files" in data or "to_delete" in data


@pytest.mark.asyncio
async def test_sync_with_empty_files(client):
    """
    Check of sync with empty list
    """
    status, _ = await client.sync({})

    assert status == HTTPStatus.BAD_REQUEST or status == HTTPStatus.OK


@pytest.mark.asyncio
async def test_sync_response_format(client, sample_files):
    """
    Check response format /sync
    """
    status, data = await client.sync(sample_files)

    if status == HTTPStatus.OK:
        assert isinstance(data, dict)

        if "files" in data:
            assert isinstance(data["files"], list)
        if "to_delete" in data:
            assert isinstance(data["to_delete"], list)
