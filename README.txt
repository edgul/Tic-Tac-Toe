README.txt

Description:
A tcp client-server tic-tac-toe game written in C++ and Qt.

Future Features:
* Separate client-server processes and projects
* Add feedback for live connection and game states
* Add game metrics
* Add unit tests
* Custom widget buttons
* Draw win line when done

Architecture:
* improve gamecontroller player tracking

Bugs:
* Separate user message streams
* Server doesn't toss user data who exits by close button (user doesn't disconnect)
* Early quit should count as loss/win, not tie
