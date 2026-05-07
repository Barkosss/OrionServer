import requests
from typing import Optional, Dict, Any

class BaseEndpoint:
    def __init__(self, base_url: str):
        self.base_url = base_url.rstrip('/')
    
    def _get(self, path: str, **kwargs) -> requests.Response:
        url = f"{self.base_url}{path}"
        return requests.get(url, **kwargs)
    
    def _post(self, path: str, data: Optional[Dict] = None, **kwargs) -> requests.Response:
        url = f"{self.base_url}{path}"
        return requests.post(url, json=data, **kwargs)
    
    def _check_response(self, response: requests.Response) -> Dict[str, Any]:
        response.raise_for_status()
        return response.json() if response.text else {}