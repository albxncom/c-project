# Report

* **The database library** supports all basic features requested by the project guidelines. It provides its functionality in a API-like fashion. It's really basic, however it does the job for very basic tasks.

* **The \*nix-shell-like library** supports the basics of the shell commands notation that all \*nix systems use. It supports:
    * Simple arguments like `command arg1 arg2`
    * Options `command -s -t`
    * Arguments for options `command -s Hello "world !" -p`
    * Escaping works, too. `command "Hello \"SOP\" class!"`


Both folders `database` and `shell` provide a `basic_example.c` file, which demonstrates the core functionalities of each library. The folder `combined` provides a `terminal.c` file which uses both libraries combined: the database operations can me performed through the shell run by the nixshell library. All three folders provide a `Makefile`. 

# Documentations

Both libraries provide a documentation with example usages. 

* [Documentation for the database](./database/README.md)
* [Documentation for the nixshell](./shell/README.md)
