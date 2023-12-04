from typing import Dict, List, Any

from Singleton import Singleton
from exceptions import *
import parser
from BaseInventory import BaseInventory
from Inventory import Inventory
from GroceryList import GroceryList
from ItemsDict import ItemsDict
from Item import Item


class Kitchen(Singleton):

    def __init__(self):
        super().__init__()
        self.__name = None
        self.__passcode = None
        self.__base_inventory = BaseInventory('מלאי בסיס', dict())
        self.__inventory = Inventory('מלאי נוכחי', dict())
        self.__grocery_list = GroceryList('רשימת קניות', dict())

    @staticmethod
    def get_instance() -> 'Kitchen':
        if Kitchen._instance is None:
            raise KitchenNotExistError('Kitchen is not exist!')
        return Kitchen._instance

    # getters
    @property
    def base_inventory(self) -> BaseInventory:
        return self.__base_inventory

    @property
    def inventory(self) -> Inventory:
        return self.__inventory

    @property
    def grocery_list(self) -> 'GroceryList':
        self.__grocery_list.remove_bucket()
        for item in self.__base_inventory.items.keys():
            if item not in self.__inventory.items.keys():
                self.__grocery_list.insert_item(self.__base_inventory.items[item][0],
                                                float(self.__base_inventory.items[item][1]))
            elif self.__base_inventory.items[item][1] > self.__inventory.items[item][1]:
                self.__grocery_list.insert_item(self.__base_inventory.items[item][0],
                                                self.__base_inventory.items[item][1] - self.__inventory.items[item][1])
        return self.__grocery_list

    @property
    def name(self) -> str:
        return self.__name

    @property
    def passcode(self) -> str:
        return self.__passcode

    # setters
    @inventory.setter
    def inventory(self, kitchen_inventory: str or None) -> None:
        try:
            processed: dict = parser.parse_bucket(kitchen_inventory)
        except InvalidInputError as e:
            raise InvalidInputError(f'Caught an error: {e} - Invalid kitchen inventory!')
        self.__inventory.remove_bucket()
        if processed is None:
            return
        for item in processed.keys():
            try:
                self.__inventory.insert_item(Item(item), processed[item])
            except ItemAlreadyExistError:
                self.__inventory.insert_item(ItemsDict.get_instance().items[item], processed[item])

    def insert_items_inventory(self, kitchen_inventory: str or None) -> None:
        try:
            processed: dict = parser.parse_bucket(kitchen_inventory)
        except InvalidInputError as e:
            raise InvalidInputError(f'Caught an error: {e} - Invalid kitchen inventory!')
        if len(processed) == 0:
            return
        for item in processed.keys():
            try:
                self.__inventory.insert_item(Item(item), processed[item])
            except ItemAlreadyExistError:
                self.__inventory.insert_item(ItemsDict.get_instance().items[item], processed[item])

    @base_inventory.setter
    def base_inventory(self, kitchen_basic_inventory: str or None) -> None:
        try:
            processed: dict = parser.parse_bucket(kitchen_basic_inventory)
        except InvalidInputError as e:
            raise InvalidInputError(f'Caught an error: {e} - Invalid kitchen basic inventory!')
        self.__base_inventory.remove_bucket()
        if len(processed) == 0:
            return
        for item in processed.keys():
            try:
                self.__base_inventory.insert_item(Item(item), processed[item])
            except ItemAlreadyExistError:
                self.__base_inventory.insert_item(ItemsDict.get_instance().items[item], processed[item])

    def insert_items_base_inventory(self, kitchen_basic_inventory: str or None) -> None:
        try:
            processed: dict = parser.parse_bucket(kitchen_basic_inventory)
        except InvalidInputError as e:
            raise InvalidInputError(f'Caught an error: {e} - Invalid kitchen basic inventory!')
        if len(processed) == 0:
            return
        for item in processed.keys():
            try:
                self.__base_inventory.insert_item(Item(item), processed[item])
            except ItemAlreadyExistError:
                self.__base_inventory.insert_item(ItemsDict.get_instance().items[item], processed[item])

    def remove_items_base_inventory(self, kitchen_basic_inventory: str or None) -> None:
        try:
            processed: dict = parser.parse_bucket(kitchen_basic_inventory)
        except InvalidInputError as e:
            raise InvalidInputError(f'Caught an error: {e} - Invalid kitchen basic inventory!')
        if len(processed) == 0:
            return
        for item in processed.keys():
            try:
                self.__base_inventory.remove_item(item, processed[item])
            except ItemNotExistError:
                pass

    def remove_items_inventory(self, kitchen_inventory: str or None) -> None:
        try:
            processed: dict = parser.parse_bucket(kitchen_inventory)
        except InvalidInputError as e:
            raise InvalidInputError(f'Caught an error: {e} - Invalid kitchen inventory!')
        if len(processed) == 0:
            return
        for item in processed.keys():
            try:
                self.__inventory.remove_item(item, processed[item])
            except ItemNotExistError:
                pass

    @name.setter
    def name(self, kitchen_name: str) -> None:
        # check if name is valid
        if not kitchen_name.isalnum() or len(kitchen_name) > 20 or len(kitchen_name) < 4:
            raise InvalidInputError('Invalid kitchen name!')
        self.__name = kitchen_name

    @passcode.setter
    def passcode(self, kitchen_passcode: str) -> None:
        if len(kitchen_passcode) != 4 or not kitchen_passcode.isdigit():
            raise InvalidInputError('Invalid kitchen passcode!')
        self.__passcode = kitchen_passcode

    # methods
    def __str__(self) -> str:
        string = f'נתוני המטבח שלך:\n'
        # string += f'שם המטבח: {self.__name}\n'
        # string += f'קוד: {self.__passcode}\n'
        string += f'{str(self.__base_inventory)}'
        string += f'{str(self.__inventory)}'
        return string

    def delete_instance(cls) -> None:
        cls.__name = None
        cls.__passcode = None
        BaseInventory.get_instance().delete_instance()
        Inventory.get_instance().delete_instance()
        GroceryList.get_instance().delete_instance()
        super().delete_instance()
