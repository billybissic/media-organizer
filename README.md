# Media Organizer

## Linux
```
make clean
make
./bin/media_organizer sort-albums --sort-directory "/path/to/directory/to/sort" --destination "/path/to/storage/directory/" --dry-run false
```

** Note by default --dry-run is set to false so it is not required.

If you have a specific folder naming convention it must be added to the naming convention.cpp file.
