from Item import Item
from exceptions import *
from abc import ABC, abstractmethod
from ItemsDict import *
from Singleton import Singleton


class Bucket(Singleton, ABC):

    def __init__(self, items: dict[str, [Item, float]] = None):
        super().__init__()
        self.__items = items

    @abstractmethod
    def __str__(self):
        string = ''
        for item in self.__items.keys():
            string += f'{str(item)} - {self.__items[item][1]}\n'
        return string

    @property
    def items(self) -> dict[str, list[Item, float]]:
        return self.__items

    # insert item to the bucket

    def insert_item(self, item: Item, quantity: float) -> None:
        if item.name in self.__items:
            self.__items[item.name][1] += quantity
        else:
            self.__items[item.name] = [item, quantity]

    # remove item from the bucket

    def remove_item(self, name: str, quantity: float) -> None:
        if name not in self.__items:
            raise ItemNotExistError(f'Item {name} does not exist!')
        self.__items[name][1] -= quantity
        if self.__items[name][1] <= 0:
            del self.__items[name]

    # remove all items from the bucket

    def remove_bucket(self) -> None:
        self.__items.clear()

    # get the quantity of the item in the bucket

    def get_item_quantity_by_name(self, name: str) -> float:
        if name not in self.__items:
            raise ItemNotExistError(f'Item {name} does not exist!')
        return self.__items[name][1]

    def delete_instance(cls):
        cls.__items.clear()
        super().delete_instance()
