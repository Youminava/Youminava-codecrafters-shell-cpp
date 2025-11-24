# FUSE-based VFS Implementation

`kubsh` uses **FUSE** (Filesystem in Userspace) to implement the VFS user management feature.

## How it works

- `users_mkdir()` intercepts directory creation in `~/users/`
- When you do `mkdir users/newuser`, the kernel calls our code **synchronously**
- User is created via `useradd` before `mkdir` returns
- VFS files (`id`, `home`, `shell`) are automatically available through FUSE

## Building

```bash
make clean
make
```

The binary is always built with FUSE support.

## Testing Locally

### With Docker (privileged mode required):
```bash
docker run --rm --privileged -v $(pwd):/app tyvik/kubsh_test:master /bin/bash -c "cd /app && export PATH=/app:\$PATH && pytest -v"
```

### Running the shell manually:
```bash
./kubsh
```

The `users/` directory will be mounted as a FUSE filesystem. Try:
```bash
$ mkdir users/testuser
$ ls users/testuser/
id  home  shell
$ cat users/testuser/id
1001
```

## CI/CD Configuration

For all tests to pass in GitLab CI, the runner must be configured with `privileged = true`.

See **GITLAB_RUNNER_SETUP.md** for detailed instructions.

## Test Results

- **With FUSE enabled (privileged runner):** 9/9 tests pass ✓
- **Without FUSE:** 7/9 tests pass (basic shell tests), 2/9 fail (VFS tests) ✗
