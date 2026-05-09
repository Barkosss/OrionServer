from aiohttp import ClientSession

from config import ClientConfig


class MSBackendClient:
    """API client for MSBackend"""

    def __init__(self, base_url: str | None = None):
        self.base_url = base_url or ClientConfig().SERVER_IP
        self._session: ClientSession | None = None

    async def __aenter__(self):
        self._session = ClientSession()
        await self._session.__aenter__()
        return self

    async def __aexit__(self, *args):
        await self._session.__aexit__(*args)

    @property
    async def session(self) -> ClientSession:
        if self._session is None:
            self._session = ClientSession()
        return self._session

    async def _request(self, method: str, endpoint: str, **kwargs) -> tuple[int, dict]:
        """
        Base method for request
        """
        session = await self.session
        url = f"{self.base_url}{endpoint}"

        async with session.request(method, url, **kwargs) as resp:
            status = resp.status
            try:
                data = await resp.json()
            except:
                data = {"message": await resp.text()}
            return status, data

    async def manifest(self) -> tuple[int, dict]:
        """
        GET /manifest
        """
        return await self._request("GET", "/manifest")

    async def health(self) -> tuple[int, dict]:
        """
        GET /health
        """
        return await self._request("GET", "/health")

    async def sync(self, files: dict[str, str]) -> tuple[int, dict]:
        """
        GET /sync
        """
        payload = {"files": files}
        return await self._request("GET", "/sync", json=payload)

    async def download_zip(self, filenames: list[str]) -> bytes:
        """
        GET /file (ZIP)
        """
        session = await self.session
        url = f"{self.base_url}/file"
        payload = {"files": filenames}

        async with session.get(url, json=payload) as resp:
            if resp.status != 200:
                raise Exception(f"Download failed: {resp.status}")
            return await resp.read()
