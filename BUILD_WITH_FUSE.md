# Building with FUSE Support

By default, `kubsh` is built **without** FUSE support for CI compatibility.

## Requirements for FUSE build

```bash
sudo apt-get install libfuse3-dev pkg-config
```

## Build with FUSE

```bash
make clean
make ENABLE_FUSE=1
```

## Test with FUSE

```bash
docker run --rm -v $(pwd):/app --privileged tyvik/kubsh_test:master /bin/bash -c "cd /app && export PATH=/app:\$PATH && pytest -v"
```

## How it works

With FUSE enabled:
- `users_mkdir()` intercepts directory creation in `~/users/`
- When you do `mkdir users/newuser`, the kernel calls our code **synchronously**
- User is created via `useradd` before `mkdir` returns
- VFS files (`id`, `home`, `shell`) are automatically available

Without FUSE:
- VFS features are disabled
- All other shell features work normally
- Tests in `test_basic.py` pass
- Tests in `test_vfs.py` will fail (expected)
