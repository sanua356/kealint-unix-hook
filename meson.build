kealint_unix_lib = shared_library(
    'dhcp_kealint_unix',
    'callouts.cc',
    'kealint_unix_log.cc',
    'kealint_unix_messages.cc',
    'load_unload.cc',
    'version.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: HOOKS_PATH,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
kealint_unix_archive = static_library(
    'kealint_unix',
    objects: kealint_unix_lib.extract_all_objects(recursive: false),
)
