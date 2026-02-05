# KEALint UNIX Hook

## Introduction

This repository provides a layer of compatibility between KEA DHCP and KEALint, which allows you to verify the correctness of configurations when configuration settings change. The hook sends new KEA server configurations to the UNIX socket when they are changed.

## Service Info
The hook is implemented for `kea-dhcp4`, `kea-dhcp-ddns` and `kea-ctrl-agent` services.

> [!WARNING]  
> The `kea-dhcp4` and `kea-dhcp-ddns` services send configuration updates to the UNIX socket when they are changed. But the `kea-ctrl-agent` configuration sends configuration changes only when the 'config-write' event occurs. These are limitations of the algorithm implementation.

## Parameters

### Required
`enabled` - Boolean type. Determines whether data will be sent to KEALint for verification.

`scoket-path` -  String type. Defines the path to the UNIX socket to which the KEA server configurations will be sent when they are changed.

## Example configuration
```json
{
  "enabled": true,
  "socket-path":  "/tmp/kealint_unix.sock"
}
```

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
