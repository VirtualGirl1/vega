import json


# command class
class Command:
    def __init__(self):
        self.regex = ""
        self.target = ""
        self.priority = 0

    def __str__(self):
        return (f"Class:\n"
                f"\tRegex: {self.regex}\n"
                f"\tTarget: {self.target}\n"
                f"\tPriority: {self.priority}")


# callback for loads
def as_dict(dct):
    return dct


def print_menu():
    print("Here are the command options:\n"
          "\tl. List commands\n"
          "\ta. Add another file\n"
          "\tq. Save and quit\n")
    return input("Choose an option: ")


def load_regex():
    regex = input("Enter the regex file: ")
    # load file
    rfile = open(regex, "r")
    content_raw = rfile.read()
    # just converts to dict
    content = json.loads(content_raw, object_hook=as_dict)
    rfile.close()

    comm_json = content["Commands"]
    comm_list = []
    for c in comm_json:
        comm = Command()
        comm.regex = c["CommandRegex"]
        comm.target = c["Target"]
        comm.priority = c["Priority"]
        comm_list.append(comm)

    return comm_list


def add_command():
    print("Add command")
    comm = Command()

    r = input("Enter the regex expression")
    t = input("Enter the target")
    p = int(input("Enter the priority"))

    comm.regex = r
    comm.target = t
    comm.priority = p

    return comm


def save_commands(comm_list):

    pass


if __name__ == "__main__":

    comms = load_regex()

    # program loop
    running = True
    while running:
        opt = print_menu()

        if opt.lower() == "l":
            for c in comms:
                print(c)
            print("\n")

        elif opt.lower() == "a":
            ncomm = add_command()
            comms.append(ncomm)

        elif opt.lower() == "q":
            # save file
            save_commands(comms)
