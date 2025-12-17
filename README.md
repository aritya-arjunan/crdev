# crdev - Character Device Manager

**crdev** is a system utility for macOS that creates persistent userspace character devices (named pipes) backed by a C driver. It allows for the creation of infinite stream devices similar to `/dev/zero`, but for specific characters.

## Features

- **Userspace Stability:** Runs as a system LaunchDaemon. Crashes do not panic the kernel.
- **Persistence:** Devices survive reboots.
- **SIP Compliance:** Uses `/var/run` for physical storage, mapped to `/nodes` via synthetic configuration.
- **High Performance:** Driver written in C, compiled with `-O3`.

## Installation via Homebrew

```bash
brew tap aritya-arjunan/fonts
brew install crdev
```

## Usage

### Create a Device
Creates a device outputting infinite 'a' characters.
```bash
sudo crdev create a
```

### Create via Binary
Creates a device named after the binary string `01100010` that outputs the corresponding ASCII character ('b').
```bash
sudo crdev create --binary 01100010
```

### List Devices
View active devices and their status.
```bash
crdev list
```

### Uninstall
Removes the device node and unloads the LaunchDaemon service.
```bash
sudo crdev uninstall a
```

## Architecture

1.  **Driver:** A compiled C binary (`crdev_driver`) acts as the data pump.
2.  **Service:** macOS `launchd` manages the driver lifecycle (start on boot, restart on failure).
3.  **Storage:** 
    - Physical: `/usr/local/var/crdev_nodes/`
    - Virtual: `/nodes/` (Configured via `/etc/synthetic.conf`)

## License
MIT
