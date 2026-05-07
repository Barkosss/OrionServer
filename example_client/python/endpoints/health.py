from .base import BaseEndpoint

class HealthEndpoint(BaseEndpoint):
    def check(self) -> bool:
        """GET /health"""
        try:
            response = self._get("/health", timeout=5)
            return response.status_code == 200
        except:
            return False

def health_check(base_url: str) -> bool:
    return HealthEndpoint(base_url).check()