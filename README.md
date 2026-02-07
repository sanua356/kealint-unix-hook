# KEALint UNIX Hook

## Introduction

This repository provides a layer of compatibility between KEA DHCP and KEALint, which allows you to verify the correctness of configurations when configuration settings change. The hook sends new KEA server configurations to the UNIX socket when they are changed.

More information about [KEALint](https://github.com/sanua356/KEALint) can be found here.

## Service Info
The hook is implemented for `kea-dhcp4`, `kea-dhcp6`, `kea-dhcp-ddns` and `kea-ctrl-agent` services.

> [!WARNING]  
> The `kea-dhcp4`, `kea-dhcp6` and `kea-dhcp-ddns` services send configuration updates to the UNIX socket when they are changed. But the `kea-ctrl-agent` configuration sends configuration changes only when the 'config-write' event occurs. These are limitations of the algorithm implementation.

> [!WARNING]
> The sended to UNIX socket configuration is not redacted, i.e. it contains database passwords in plain text, if those were specified in the original configuration. Care should be taken not to expose the UNIX socket to unprivileged users.

## Parameters

`enabled` - Boolean type. Determines whether data will be sent to KEALint for verification.

`scoket-path` -  String type. Defines the path to the UNIX socket to which the KEA server configurations will be sent when they are changed.

## Example configuration
```json
{
  "enabled": true,
  "socket-path":  "/tmp/kealint_unix.sock"
}
```

## Instruction
1. Compile and place the hook `kealint_unix.so` to the directory where all the standard KEA hooks are stored. For example: `/usr/lib/kea/hooks/kealint_unix.so`.
2. Check the rights and the owner of the hook file based on [this article](https://kea.readthedocs.io/en/latest/arm/install.html). If they are incorrect, change them.
3. Determine the path where you will store the temporary UNIX socket file to which the KEA configurations will be sent when changing. For example, `/tmp/kealint_unix.sock`.
4. Open the configuration files that you want to check for. For example, `kea-dhcp4.conf`, find the `hooks-libraries` key there.
5. Use the example above to add the hook configuration there.
6. Restart the services for which you have activated the KEA hooks using `keactrl` or `systemd`. For example: `systemctl stop kea-dhcp4 && systemctl start kea-dhcp4`.
7. Run KEALint in `standalone` mode. For example: `./kealint --mode standalone --unix-socket-path /tmp/kealint_unix.sock --database-path testdb.sq3`.

When the configuration is changed, the test results will be recorded in the SQLite database.

## Build

### Build with G++
1. Install kea-dev package (In Arch it is part of the KEA package, in other distributions it may be a separate package).
2. Clone this repository `git clone https://github.com/sanua356/kealint-unix-hook.git`.
3. Go to the repository directory `cd ./kealint-unix-hook`.
4. Make the build script executable `chmod +x ./build.sh`.
5. Run build script `./build.sh` (sudo rights may be required).
6. Find ".so" library in current directory.

### Build with Meson
1. Clone KEA official repository: `git clone https://gitlab.isc.org/isc-projects/kea.git`.
2. Clone current repository in KEA repository path `/src/hooks/dhcp/`.
3. In file `meson.build` by path `/src/hooks/dhcp` paste new line `subdir('kealint-unix-hook')` .
4. Run `meson compile -C build` in terminal.
5. After compilation the library file is located at the path `/build/src/hooks/dhcp/kealint-unix-hook`.

## License

MIT
