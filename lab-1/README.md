# Event-Driven Programming Laboratory Work #1

## Title

Window. Window handling. Basic window’s form elements

## Contents

* Win32 API
* `git`
* Programming Style Guidelines
* Window
* Button
* Text Input
* Text

## Completed Mandatory Objectives:

* Choose a _Programming Style Guideline_ that you'll follow
* Create a `Windows application`
* Add 2 `buttons` to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
* Add 2 `text` elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size) *[one of them should be something funny]*
* On windows resize, one of the `text`s should "reflow" and be in window's center (vertically and horizontally)

## Completed Objectives with additional points:

* Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size) `(1pt)`
* Make elements to fit window on resize `(1 pt)`
* Change behavior of different window actions (at least 3). For ex.: on clicking close button, move window to a random location on display's working space `(1 pt)`

## The application creation stepts

For creating this app I've read the chapters that where specified in the task of the lab and also the [www.MSDN.com](http://msdn.microsoft.com/en-US/) website for and advance look. 

For developing the project, I've used the CodeBlocks IDE. The project can be simply compiled having the ** *.cbp ** file and the resource ** *.cpp **.  

![The app](./images/App.jpg)

The Window has a minimal size which was set using the [WM_GETMINMAXINFO](http://msdn.microsoft.com/en-us/library/windows/desktop/ms632626(v=vs.85).aspx) message processing. 

The font and the size (which is a parameter of the CreateFont function) are stored in a two dimensional array. The rows represent different fonts, the columns different sizes of the font. 

The color of the text of the Input Edit Box is changed accordng to [WM_CTLCOLOREDIT](http://msdn.microsoft.com/en-us/library/windows/desktop/bb761691(v=vs.85).aspx) message processing. This message allows us to change the color only for the Edit Boxes which don't have the style **ES_READONLY**. That's why processing this message we can't change the color of the text of the Output Edit Box.

If you type the word 'MOVE' then the window will be Maximized.
