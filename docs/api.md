# USBHost Library

## General

### `Task()`

#### Description
Task() polls connected usb devices for updates to their status.

NB : If there is no activity on a connected USB device, task() will block all other calls for 5 second intervals.

#### Syntax

```
usb.Task()
```

#### Parameters
usb : the name of the USB controller object


#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

## Mouse Controller

## `MouseController`

#### Description
MouseController is the class for all calls to the USBHost relating to an attached mouse.

#### Syntax

```
MouseController mouse(usb);
```

#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}

void mouseMoved() {
  Serial.print("Move: ");
  Serial.print(mouse.getXChange());
  Serial.print(", ");
  Serial.println(mouse.getYChange());
}
```

### `mouseMoved()`

#### Description
mouseMoved() is a function that is called whenever a connected USB mouse moves.

#### Syntax

```
void mouseMoved(){
//statements
}
```

#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

void mouseMoved() {
  Serial.print("Move: ");
  Serial.print(mouse.getXChange());
  Serial.print(", ");
  Serial.println(mouse.getYChange());
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

### `mouseDragged()`

#### Description
mouseDragged() is a function that is called whenever a connected USB mouse is dragged (movement while a mouse button is being pressed).

#### Syntax

```
void mouseDragged(){
//statements
}
```

#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

void mouseDragged() {
  Serial.print("DRAG: ");
  Serial.print(mouse.getXChange());
  Serial.print(", ");
  Serial.println(mouse.getYChange());
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

### `mousePressed()`

#### Description
mousePressed() is a function that is called whenever a button on a connected USB mouse is pressed.

#### Syntax

```
void mousePressed(){
//statements
}
```

#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

// This function intercepts mouse button press
void mousePressed() {
  Serial.print("Pressed: ");
  if (mouse.getButton(LEFT_BUTTON))
    Serial.print("L");
  if (mouse.getButton(MIDDLE_BUTTON))
    Serial.print("M");
  if (mouse.getButton(RIGHT_BUTTON))
    Serial.print("R");
  Serial.println();
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

### `mouseReleased()`

#### Description
mouseReleased() is a function that is called whenever a button on a connected USB mouse is released.

#### Syntax

```
void mouseReleased(){
//statements
}
```

#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

boolean left = false;
boolean middle = false;
boolean right = false;

void mousePressed() {
  if (mouse.getButton(LEFT_BUTTON))
    left = true;
  if (mouse.getButton(MIDDLE_BUTTON))
    middle = true;
  if (mouse.getButton(RIGHT_BUTTON))
    right = true;
}

// This function intercepts mouse button release
void mouseReleased() {
  Serial.print("Released: ");
  if (!mouse.getButton(LEFT_BUTTON) && left==true) {
    Serial.print("L");
    left = false;
  }
  if (!mouse.getButton(MIDDLE_BUTTON) && middle==true) {
    Serial.print("M");
    middle = false;
  }
  if (!mouse.getButton(RIGHT_BUTTON) && right==true) {
    Serial.print("R");
    right = false;
  }
  Serial.println();
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

### `getXChange()`

#### Description
Reports the relative amount of movement of a mouse on the X-axis since the last time polled. A positive number indicates movement to the right, a negative number indicates movement to the left.

#### Syntax

```
mouse.getXChange()
```

#### Parameters
none

#### Returns
int


#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

void mouseMoved() {
  Serial.print("Move: ");
  Serial.print(mouse.getXChange());
  Serial.print(", ");
  Serial.println(mouse.getYChange());
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

### `getYChange()`

#### Description
Reports the relative amount of movement of a mouse on the Y-axis since the last time polled. A positive number indicates downward movement, a negative number indicates upward movement.

#### Syntax

```
mouse.getYChange()
```

#### Parameters
none

#### Returns
int


#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

void mouseMoved() {
  Serial.print("Move: ");
  Serial.print(mouse.getXChange());
  Serial.print(", ");
  Serial.println(mouse.getYChange());
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

### `getButton()`

#### Description
Reports the status of the requested mouse button.

#### Syntax

```
mouse.getButton(button)
```

#### Parameters
button : which mouse button is being requested. Can be one of the following:

- LEFT_BUTTON
- RIGHT_BUTTON
- MIDDLE_BUTTON

#### Returns
boolean : true if the requested button is pressed, false if it is not pressed.


#### Example

```
#include <MouseController.h>

// Initialize USB Controller
USBHost usb;

// Attach mouse controller to USB
MouseController mouse(usb);

// This function intercepts mouse button press
void mousePressed() {
  Serial.print("Pressed: ");
  if (mouse.getButton(LEFT_BUTTON))
    Serial.print("L");
  if (mouse.getButton(MIDDLE_BUTTON))
    Serial.print("M");
  if (mouse.getButton(RIGHT_BUTTON))
    Serial.print("R");
  Serial.println();
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}
```

## Keyboard Controller

### `KeyboardController`

#### Description
KeyboardController is the class for all calls to the USBHost relating to an attached USB keyboard.

#### Syntax

```
KeyboardController keyboard(usb);
```


#### Example

```
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}

void keyPressed() {
  Serial.print("Pressed:  ");
  Serial.print(keyboard.getKey());
  Serial.println();
}
```

### `keyPressed()`

#### Description
keyPressed() is a function that is called whenever a key is pressed on a connected USB keyboard.

#### Syntax

```
void keyPressed(){
//statements
}
```

#### Example

```
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}

void keyPressed() {
  Serial.print("Pressed:  ");
  Serial.print(keyboard.getKey());
  Serial.println();
}
```

### `keyReleased()`

#### Description
keyReleased() is a function that is called whenever a pressed key is released on a connected USB keyboard.

#### Syntax

```
void keyReleased(){
//statements
}
```

#### Example

```
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}

void keyReleased() {
  Serial.print("Key is released");
}
```

### `getModifiers()`

#### Description
Reports any modifier keys pressed or released on an attached USB keyboard.

#### Syntax

```
keyboard.getModifiers()
```

#### Parameters
none

#### Returns
int : a numeric representation of the modifier keys being pressed. Values for the keys are below.

- LeftCtrl = 1
- LeftShift = 2
- Alt = 4
- LeftCmd = 8
- RightCtrl = 16
- RightShift = 32
- AltGr = 64
- RightCmd = 128

#### Example

```
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
  int mod = keyboard.getModifiers();
  Serial.print("mod: ");
  Serial.print(mod);
}
```

### `getKey()`

#### Description
Reports the ASCII value of a key being pressed or released on an attached USB keyboard.

#### Syntax

```
keyboard.getKey()
```

#### Parameters
none

#### Returns
int : the ASCII value of the key being pressed


#### Example

```
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void keyPressed(){
 Serial.write(keyboard.getKey());
 Serial.println();
}

void loop(){
  usb.Task();

}
```

### `getOemKey()`

#### Description
Reports the OEM-code associated with a key pressed or released on a connected USB keyboard.

#### Syntax

```
keyboard.getOemKey()
```

#### Parameters
none

#### Returns
int : the OEM-code associated with the key being pressed


#### Example

```
#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void keyPressed() {
 Serial.print("OEM key: ");
 Serial.println(keyboard.getOemKey());
}

void loop(){
  usb.Task();
}
```