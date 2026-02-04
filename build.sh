g++ -I. -I /usr/include/kea -L /usr/lib/kea/lib -fpic -shared -o kealint_unix.so \
  version.cc load_unload.cc kealint_unix_messages.cc kealint_unix_log.cc callouts.cc  \
  -lkea-dhcpsrv -lkea-dhcp -lkea-hooks -lkea-log -lkea-util -lkea-exceptions -lcurl
