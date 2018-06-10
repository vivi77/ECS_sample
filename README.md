# ECS Sample

This repository shows how can be used the library ECS
[https://github.com/vivi77/ECS].

## Content

#Systems

  * CoreCommands: This system serves as an interface between Core class and
    other system. It handles its own Event that other Systems can use to
    communicate commands to the Core.
  * CLI: Command Line Interface system which get the input from user the on a
    terminal and send it through an Event. (Use CoreCommands Event)
  * Debug: A debug system that logs any information it can get into a file.
    Very specific to the program developped but completely non invasive on other
    Systems. However it helps more on debugging inter-Systems communication than
    debugging a System.
  * NCurses: A graphic system using NCurses. Can display texts and polygons. Can
    get user input and send it through an Event. (Use CoreCommands Event)
  * TextInputUpdater: A system that handles entities that has the
    characteristics of an graphical text input. It keeps the data and the
    visual updated at all time.

    It can be compared to a Controller in a MVC pattern. The Model would be the
    TextInput Component and the View would be the Text Component that would be
    displayed by a graphic System.

#Components

  * Polygon: A Component template designed to be used for either 2D or 3D
    software.
  * Text: A Component template designed to be used for either on terminal or in
    a more evolved graphical software.
  * TerminalComponents: Template Components that use the Component template
    'Polygon' and 'Text'.
  * TextInput: Component that store all user input before being sended.
  * TextInputState: Component that gives the state of a text input Entity.
  * Transform: Component that keeps information about the position, rotation and
    scale of a Entity in a graphical program.

#Events

  * CLISystemEvent: CLI System event. It gives some control on CLI System such
    as enable and disable this system.
  * CoreCommandsEvent: CoreCommands System event. It requests the system to
    execute a command in relation with Core class.
  * TextInputUpdaterEvent(In/Out): TextInputUpdater System events. It transfers
    event that happened on a TextInput Component (In) and transfer the component
    data when requested (Out).
