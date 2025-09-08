from inchi_tests.config_models import TestConfig
from pathlib import Path


config = TestConfig(
    name="regression",
    inchi_library_path=Path("CMake_build/full_build/INCHI-1-SRC/INCHI_API/libinchi/src/lib/libinchi.so"),
)
