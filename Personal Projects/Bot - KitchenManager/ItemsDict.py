from Singleton import Singleton
from exceptions import *
from Item import Item


class ItemsDict(Singleton):

    def __init__(self):
        super().__init__()
        self.__items = {}

    @staticmethod
    def get_instance() -> 'ItemsDict':
        if ItemsDict._instance is None:
            raise ItemDictNotExistError('ItemDict is not exist!')
        return ItemsDict._instance

    @property
    def items(self) -> dict[str, Item]:
        return self.__items

    def insert_item(self, item: 'Item'):
        if item.name in self.__items:
            raise ItemAlreadyExistError(f'Item {item.name} already exists!')
        try:
            self.__items[item.name] = item
        except ItemNotExistError:
            raise ItemNotExistError(f'Item {item.name} does not exist!')

    def delete_instance(cls):
        cls.__items.clear()
        super().delete_instance()
