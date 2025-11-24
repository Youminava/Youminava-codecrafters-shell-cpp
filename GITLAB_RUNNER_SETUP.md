# GitLab Runner Configuration for FUSE Support

## Problem

FUSE (Filesystem in Userspace) requires access to `/dev/fuse` device and special privileges. 
By default, GitLab Runner does not grant these privileges to Docker containers.

## Solution

Configure your GitLab Runner to run containers in **privileged mode**.

### Step 1: Find your runner configuration

On the machine running GitLab Runner:
```bash
sudo nano /etc/gitlab-runner/config.toml
```

Or if running as a service:
```bash
sudo systemctl stop gitlab-runner
sudo nano /etc/gitlab-runner/config.toml
sudo systemctl start gitlab-runner
```

### Step 2: Add privileged mode

Find the `[[runners]]` section for your runner (look for `name = "my-local-runner"`) and add `privileged = true`:

```toml
[[runners]]
  name = "my-local-runner"
  url = "https://gitlab.com"
  id = ...
  token = "..."
  executor = "docker"
  
  [runners.docker]
    privileged = true        # ← ADD THIS LINE
    tls_verify = false
    image = "alpine:latest"
    volumes = ["/cache"]
```

### Step 3: Restart GitLab Runner

```bash
sudo gitlab-runner restart
```

Or if using systemd:
```bash
sudo systemctl restart gitlab-runner
```

### Step 4: Verify

Re-run the pipeline. In the test stage logs, you should see:
```
✓ FUSE device available - all tests will run
```

Instead of:
```
✗ FUSE device NOT available - VFS tests will fail
```

## Alternative: Test locally with privileged mode

You can always test with FUSE locally using:
```bash
make clean
make
docker run --rm --privileged -v $(pwd):/app tyvik/kubsh_test:master /bin/bash -c "cd /app && export PATH=/app:\$PATH && pytest -v"
```

## Security Note

`privileged = true` gives containers almost the same access as processes running on the host.
Only enable this on runners you trust and control (like your local development runner).

Do NOT enable this on shared/public runners.
