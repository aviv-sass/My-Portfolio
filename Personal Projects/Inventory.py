from Bucket import *


class Inventory(Bucket):

    def __init__(self, name: str, items: dict[str, [Item, float]]):
        super().__init__(items)
        self.__name = name

    def __str__(self):
        if len(self.items) == 0:
            return f'{self.name}:\n' + 'ריק!\n'
        return f'{self.__name}:\n' + super().__str__()

    @property
    def name(self) -> str:
        return self.__name

    @name.setter
    def name(self, name: str) -> None:
        self.__name = name

    def delete_instance(self):
        self.__name = None
        self.items.clear()
        super().delete_instance()