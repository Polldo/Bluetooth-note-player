# Bluetooth-note-player
While the firmware for this project is completed, the hardware part is still under development. Also a mobile application has to be developed in order to control the device via bluetooth. Actually it can be controlled using other generic applications on the android store, but a specific application would be the best solution.

This device is a note-player that can be controlled via bluetooth. <br >
There are 4 operative modes: <br >
1- PLAY_MODE: the device is just playing the sequence of note contained in its ROM or EEPROM depending on its configuration. By default the device is configured to play ROM notes. Initially EEPROM doesn't contain notes, while the ROM contains a simple happy-birthday song. <br >
2- BLUETOOTH_MODE: this mode can be accessed by pressing the only button connected to the mcu. From here the device is waiting for a request via bluetooth. If the button is pressed another time, the device will go again to the PLAY_MODE. Else if a bluetooth request is received the device will enter the BL_COMMAND_MODE. <br >
3- BL_COMMAND_MODE: here the device waits for commands to execute. The next mode transition will depend on the command received. <br >
Available commands: <br > 
-CMD_Esc, the next mode will be again the PLAY_MODE.  <br >
-CMD_Play, the next mode will be the TRANSFER_PLAY_MODE. <br >
-CMD_Trans, the next mode will be the TRANSFER_NOTE_MODE. <br >
-CMD_DISABLE_EEPROM/CMD_ENABLE_EEPROM, this command configures the PLAY_MODE. It decides which sequence of note has to be played. <br >
4- TRANSFER_PLAY_MODE: the device becomes a kind of musical instrument, it will play the notes it's receiving in real time through the bluetooth. The escape command 0xFFFF will cause the mode changing to the previous one. <br >
5- TRANSFER_NOTE_MODE: the device is ready to rewrite the sequence of note contained in the EEPROM. The new notes have to be sent through bluetooth now. To indicate that the sequence of notes to store is finished an escape note is used "0xFFFF".
