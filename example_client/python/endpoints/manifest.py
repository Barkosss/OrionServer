from .base import BaseEndpoint

class ManifestEndpoint(BaseEndpoint):
    def get(self) -> dict:
        """GET /manifest"""
        response = self._get("/manifest")
        return self._check_response(response)

# Удобная функция для прямого вызова
def get_manifest(base_url: str) -> dict:
    return ManifestEndpoint(base_url).get()