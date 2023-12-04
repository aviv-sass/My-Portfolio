from exceptions import *


class Item:
    def __init__(self, name: str):
        from ItemsDict import ItemsDict
        if name in ItemsDict.get_instance().items:
            raise ItemAlreadyExistError(f'Item {name} already exists!')
        self.__name = name
        ItemsDict.get_instance().insert_item(self)

    @property
    def name(self) -> str:
        return self.__name

    def __str__(self):
        return f'{self.name}'
