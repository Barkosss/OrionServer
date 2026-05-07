import endpoints
from config import Config

class MSBackendClient:
    def __init__(self):
        self.config = Config()
        self.base_url = self.config.server_url
    
    def get_manifest(self) -> dict:
        return endpoints.get_manifest(self.base_url)
    
    def sync(self, client_files: dict) -> dict:
        return endpoints.sync_files(self.base_url, client_files, self.config.strategy)
    
    def download_file(self, filepath: str, save_to: str) -> bool:
        return endpoints.download_file(self.base_url, filepath, save_to)
    
    def download_patch(self, patch_path: str, save_to: str) -> bool:
        return endpoints.download_patch(self.base_url, patch_path, save_to)
    
    def health_check(self) -> bool:
        return endpoints.health_check(self.base_url)
    
    def ping(self) -> dict:
        return endpoints.ping(self.base_url)