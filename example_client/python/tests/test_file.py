import io
import zipfile

import pytest


@pytest.mark.asyncio
async def test_download_zip_returns_valid_zip(client, sample_filenames):
    """
    Check to download valid zip /file
    """
    data = await client.download_zip(sample_filenames)

    assert len(data) > 0
    assert data[:4] == b"PK\x03\x04"

    try:
        with zipfile.ZipFile(io.BytesIO(data)) as zf:
            namelist = zf.namelist()
            assert len(namelist) == len(sample_filenames)
    except zipfile.BadZipFile:
        pytest.fail("Downloaded file is not a valid ZIP archive")
