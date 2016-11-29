 _   _       _  _     _
/ _ |_ |\ | |_ |_  | |_
\_/ |_ | \| |_  _| |  _|

/-----------------------\
| Ambience Sound Studio |
\-----------------------/


=== Version 1.2 ===

Rev 00 Beta (???)
-----------------

New Features:
- Implemented "Copy to Local" feature. Upon adding new imports, the user is prompted
  appropriately to copy them to the project's local folder. These local files are saved
  relatively in the project, so an entirely relative project can be easily ported to other
  systems. This feature is activated by a checkable menu item under the Imports menus.


=== Version 1.1 ===

Rev 05 Beta (r59)
-----------------

Bug Fixes:
- On a new project, or whenever there are no scenes created, the user was able to try and make
  new states, or delete the current scene. A crash was occurring on this nonsense event.
- Loading time was a little long.

New Features:
- Implemented a swapping feature to allow a user to move buttons around on the Sound Board.


Rev 04 Beta (r20)
-----------------

Bug Fixes:
- Pausing, saving, and reloading in the Random section was causing the sound to fail to start.
- Selecting a period less than the random sound length could cause it to be cut off.

New Features:
- Implemented second sound mode for Random where you select a multiple of the base sound length
  instead of a time in seconds.


Rev 03 Beta (r19)
-----------------

Bug Fixes:
- If you cancel during the naming phase of file import, it would import anyway.

New Features:
- The hidable sidebar now has vertical scroll. Accordingly, the application no longer enforces
  maximization, allowing normal window resizing.
- Added Rename and Reimport options. Imported files can be given a new title, or current titles
  can be reassigned to new import files.
- Mute has been renamed to Pause on all controls to avoid confusion.


Rev 02 Beta (r11)
-----------------

Bug Fixes:
- When trying to delete multiple items in Background or Random, some items were not being deleted.
- Upon creating new scenes, sometimes they would not appear in the drop-down list.
- If deleting the state currently being viewed, clicking Switch caused the program to crash.

New Features:
- Right-clicking on an assigned button in the Sound Board now gives a context menu for reassignment.
- The program now allows you to open a project file directly, and the installer associates the file
  extension .assp with Ambience.


Rev 01 Beta (r5)
----------------

Bug Fixes:
- Changing scenes and states in the dialog does not update the main drop-down menus.
