import os
from .base import BaseEndpoint

class FileEndpoint(BaseEndpoint):
    def download(self, filepath: str, save_to: str, stream: bool = True) -> bool:
        """GET /file/{filepath}"""
        response = self._get(f"/file/{filepath}", stream=stream)
        
        if response.status_code == 404:
            return False
        
        response.raise_for_status()
        
        os.makedirs(os.path.dirname(save_to), exist_ok=True)
        
        with open(save_to, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                f.write(chunk)
        
        return True
    
    def download_patch(self, patch_path: str, save_to: str) -> bool:
        """GET {patch_path} (for bsdiff)"""
        return self.download(patch_path, save_to)

def download_file(base_url: str, filepath: str, save_to: str) -> bool:
    return FileEndpoint(base_url).download(filepath, save_to)

def download_patch(base_url: str, patch_path: str, save_to: str) -> bool:
    return FileEndpoint(base_url).download_patch(patch_path, save_to)