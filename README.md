# todot
------

Little todo application.

# Features
------

- We can save notes or tasks, the tasks can have a date which can be used as a limit.
- Uses a .txt file to save data.

# Installation
------

    gcc -std=c99 -o todo main.c src/commands.c src/list.c src/date.c src/readin.c src/saveload.c

# Commands / Usage

- add task
- add note
- print notes
- print tasks
- print all
- delete note
- delete task
- help or ?
- todo
- quit

# Side notes that may be not important
---

- C99 compliance
- Warning free (not yet)
- Did this while listening to [ZUN](http://en.wikipedia.org/wiki/Team_Shanghai_Alice)
