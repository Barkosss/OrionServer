from .base import BaseEndpoint

class SyncEndpoint(BaseEndpoint):
    def sync(self, client_files: dict, strategy: str = "full") -> dict:
        """POST /sync"""
        payload = {
            "files": client_files,
            "strategy": strategy
        }
        response = self._post("/sync", data=payload)
        return self._check_response(response)

def sync_files(base_url: str, client_files: dict, strategy: str = "full") -> dict:
    return SyncEndpoint(base_url).sync(client_files, strategy)