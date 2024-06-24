"""

Convert a list of boards into separate files:
    
        1. Read the file `t.txt` which contains a list of boards.
        2. Split the file into a list of boards.
        3. Write each board into a separate file.
    
        Example:

        Grid 01
        003020600
        900305001
        001806400
        008102900
        700000008
        006708200
        ...

        Grid 02
        200080300
        060070084
        030500209
        000105408
        000000000
        402706000
        ...
    



"""

data = open("t.txt", "r").read()

boards = [data.split("\n")[i + 1 : i + 10] for i in range(0, len(data.split("\n")), 10)]


for e, board in enumerate(boards):
    open(f"board_{e}.txt", "w").write("".join(board))
