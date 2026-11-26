# SheSecure

A desktop women's-safety app built with C++17 and Qt 6 (Widgets). You save a list of emergency contacts, and with one click on the SOS button the app generates an emergency message for every saved contact and shows it in an activity log.

**Important:** SheSecure is currently a simulation. It does not send SMS, calls, emails or any network traffic. Pressing SOS only writes simulated messages to the on-screen log.

## Features

- Add emergency contacts (name + phone number)
- Remove a selected contact
- Contacts are saved to a local text file and reloaded on startup
- One-click SOS button with a confirmation dialog (defaults to "No" to avoid accidental triggers)
- Timestamped emergency activity log
- Fully offline, no GPS or location tracking
- Custom pink/red themed interface via a Qt stylesheet

## Project Structure

```
SheSecure/
  CMakeLists.txt
  src/
    main.cpp            Application entry point
    mainwindow.h/.cpp   GUI, layout, styling, button handlers, SOS logic
    contactstore.h/.cpp Contact data model, validation, file load/save
```

## Requirements

- CMake 3.16 or newer
- A C++17 compiler (GCC, Clang or MSVC)
- Qt 6 with the Widgets module

## Build and Run

```
mkdir build
cd build
cmake ..
cmake --build .
./SheSecure        (Windows: SheSecure.exe)
```

If CMake cannot find Qt, point it to your Qt install, for example:

```
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
```

## How to Use

1. Enter a name and phone number, then click Add Contact.
2. To delete someone, select them in the list and click Remove Selected Contact.
3. In an emergency, click SOS - I'M IN DANGER and confirm. A simulated message for each contact appears in the Emergency Activity Log.

## How It Works

**ContactStore** (contactstore.cpp) holds the contacts in memory and persists them to contacts.txt, located in the same folder as the executable. Each line is stored as `name|phone`.

- Name and phone must both be non-empty
- The characters `|` and newline are rejected, because `|` is the file delimiter
- Duplicate phone numbers are rejected
- If saving fails after an add or remove, the in-memory change is rolled back so the app and the file stay consistent

**MainWindow** (mainwindow.cpp) builds the interface in code, applies the stylesheet, and connects the buttons to the slots addContact(), removeSelectedContact() and triggerSOS().

## Known Limitations

- No real message delivery: triggerSOS() only logs simulated messages
- Phone numbers are not format-validated (any text without `|` or newline is accepted)
- contacts.txt is stored next to the executable, which may not be writable if installed in a protected folder (e.g. Program Files)
- The activity log is not saved; it clears when the app closes
- Contacts are stored as plain, unencrypted text

## Possible Future Work

- Real SMS delivery through a gateway such as Twilio
- Phone number format validation
- Saving the contacts file under QStandardPaths::AppDataLocation
- Persistent activity log
- Optional location sharing (opt-in)

## License

Not specified. Add one before sharing publicly.
