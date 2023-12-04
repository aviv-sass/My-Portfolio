from ItemsDict import *


def parse_bucket(text) -> dict[str: float]:
    inventory = {}
    processed: [str] = text.split('\n')
    for line in processed:
        line = line.split()
        if len(line) == 1 and line[0] == 'ריקה':
            return inventory
        if len(line) < 2:
            raise InvalidInputError('Invalid input!')
        line[0] = line[0].strip()
        # remove spaces from the beginning and end until the end of array line.
        for i in range(1, len(line)):
            line[i] = line[i].strip()
        # union the item name to one string with spaces and remove the rest of the array
        line[1] = ' '.join(line[1:])
        line = line[:2]
        # check if the quantity is a number from type float
        try:
            line[0] = float(line[0])
        except ValueError:
            raise InvalidInputError('Invalid input!')
        if line[0] <= 0:
            raise InvalidInputError('Invalid input!')
        # remove spaces from the beginning and end of the item name
        line[1] = line[1].strip()
        # check if there is item with the same name, insert the quantity to the existing item
        if line[1] in inventory.keys():
            inventory[line[1]] += float(line[0])
        else:
            inventory[line[1]] = float(line[0])
    return inventory
