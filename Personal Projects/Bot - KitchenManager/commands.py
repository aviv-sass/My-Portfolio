from telegram import ReplyKeyboardMarkup, ReplyKeyboardRemove, Update
from telegram.ext import ContextTypes, ConversationHandler, CommandHandler
from Kitchen import *
from exceptions import *
import settings


async def start_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    try:
        Kitchen()
    except SingletonAlreadyExistError as e:
        await update.message.reply_text(settings.replies['kitchenExist'] + settings.replies['wantToSetupFromScratch'],
                                        reply_markup=ReplyKeyboardMarkup(
                                            [['/deleteKitchen'] + settings.casual_commands],
                                            one_time_keyboard=True,
                                            resize_keyboard=True))
        return ConversationHandler.END
    await update.message.reply_text(settings.replies['start'])
    await update.message.reply_text(settings.replies['setBaseInventory'] + settings.replies['bucketPatternGuide'],
                                    reply_markup=(ReplyKeyboardRemove()))
    return settings.INIT_BASE_INVENTORY_EXECUTE


async def delete_kitchen_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    Kitchen.get_instance().delete_instance()
    await update.message.reply_text(settings.replies['deleteKitchen'])


async def init_name_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text: str = update.message.text
    try:
        # set name to the kitchen
        Kitchen.get_instance().name = text
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.INIT_NAME_EXECUTE
    await update.message.reply_text(settings.replies['setPasscode'])
    return settings.INIT_PASSCODE_EXECUTE


async def init_passcode_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    # if passcode is already set, return to the user to set the Base Inventory
    if Kitchen.get_instance().passcode is None:
        text: str = update.message.text
        try:
            Kitchen.get_instance().passcode = text
        except InvalidInputError as e:
            await update.message.reply_text(settings.replies['invalidInput'])
            return settings.INIT_PASSCODE_EXECUTE
    await update.message.reply_text(settings.replies['setBaseInventory'] + settings.replies['bucketPatternGuide'])
    return settings.INIT_BASE_INVENTORY_EXECUTE


async def init_base_inventory_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = update.message.text
    try:
        Kitchen.get_instance().base_inventory = text
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.INIT_BASE_INVENTORY_EXECUTE
    if len(Kitchen.get_instance().inventory.items) == 0:
        await update.message.reply_text(settings.replies['setInventory'] + settings.replies['bucketPatternGuide'])
        return settings.INIT_INVENTORY_EXECUTE
    await update.message.reply_text(settings.replies['actionComplete'] + f'{Kitchen.get_instance().__str__()}',
                                    reply_markup=ReplyKeyboardMarkup([settings.casual_commands],
                                                                     one_time_keyboard=True,
                                                                     input_field_placeholder=settings.replies[
                                                                         'boringMessage'],
                                                                     resize_keyboard=True))
    return ConversationHandler.END


async def set_base_inventory(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        settings.replies['setBaseInventory'] + settings.replies['bucketPatternGuide'] + settings.replies['aboutCancel'])
    return settings.INIT_BASE_INVENTORY_EXECUTE


async def init_inventory_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = update.message.text
    try:
        Kitchen.get_instance().inventory = text
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.INIT_INVENTORY_EXECUTE
    await update.message.reply_text(settings.replies['actionComplete'] + f'{Kitchen.get_instance().__str__()}',
                                    reply_markup=ReplyKeyboardMarkup([settings.casual_commands],
                                                                     one_time_keyboard=True,
                                                                     input_field_placeholder=settings.replies[
                                                                         'boringMessage'],
                                                                     resize_keyboard=True))
    return ConversationHandler.END


async def insert_items_base_inventory_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = update.message.text
    try:
        Kitchen.get_instance().insert_items_base_inventory(text)
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.INSERT_ITEMS_BASE_INVENTORY_EXECUTE
    await update.message.reply_text(settings.replies['actionComplete'] + f'{Kitchen.get_instance().__str__()}',
                                    reply_markup=ReplyKeyboardMarkup([settings.casual_commands],
                                                                     one_time_keyboard=True,
                                                                     input_field_placeholder=settings.replies[
                                                                         'boringMessage'],
                                                                     resize_keyboard=True))
    return ConversationHandler.END


async def insert_items_inventory_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = update.message.text
    try:
        Kitchen.get_instance().insert_items_inventory(text)
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.INSERT_ITEMS_INVENTORY_EXECUTE
    await update.message.reply_text(settings.replies['actionComplete'] + f'{Kitchen.get_instance().__str__()}',
                                    reply_markup=ReplyKeyboardMarkup([settings.casual_commands],
                                                                     one_time_keyboard=True,
                                                                     input_field_placeholder=settings.replies[
                                                                         'boringMessage'],
                                                                     resize_keyboard=True))
    return ConversationHandler.END


async def set_inventory(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        settings.replies['setInventory'] + settings.replies['bucketPatternGuide'] + settings.replies['aboutCancel'])
    return settings.INIT_INVENTORY_EXECUTE


async def insert_items_base_inventory(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        settings.replies['insertItemsBaseInventory'] + settings.replies['bucketPatternGuide'] + settings.replies[
            'aboutCancel'])
    return settings.INSERT_ITEMS_BASE_INVENTORY_EXECUTE


async def insert_items_inventory(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        settings.replies['insertItemsInventory'] + settings.replies['bucketPatternGuide'] + settings.replies[
            'aboutCancel'])
    return settings.INSERT_ITEMS_INVENTORY_EXECUTE


async def remove_items_base_inventory(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        settings.replies['removeItemsBaseInventory'] + settings.replies['bucketPatternGuide'] + settings.replies[
            'aboutCancel'])
    return settings.REMOVE_ITEMS_BASE_INVENTORY_EXECUTE


async def remove_items_inventory(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    await update.message.reply_text(
        settings.replies['removeItemsInventory'] + settings.replies['bucketPatternGuide'] + settings.replies[
            'aboutCancel'])
    return settings.REMOVE_ITEMS_INVENTORY_EXECUTE


async def remove_items_base_inventory_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = update.message.text
    try:
        Kitchen.get_instance().remove_items_base_inventory(text)
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.REMOVE_ITEMS_BASE_INVENTORY_EXECUTE
    await update.message.reply_text(settings.replies['actionComplete'] + f'{Kitchen.get_instance().__str__()}',
                                    reply_markup=ReplyKeyboardMarkup([settings.casual_commands],
                                                                     one_time_keyboard=True,
                                                                     input_field_placeholder=settings.replies[
                                                                         'boringMessage'],
                                                                     resize_keyboard=True))
    return ConversationHandler.END


async def remove_items_inventory_execute(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    text = update.message.text
    try:
        Kitchen.get_instance().remove_items_inventory(text)
    except InvalidInputError as e:
        await update.message.reply_text(settings.replies['invalidInput'])
        return settings.REMOVE_ITEMS_INVENTORY_EXECUTE
    await update.message.reply_text(settings.replies['actionComplete'] + f'{Kitchen.get_instance().__str__()}',
                                    reply_markup=ReplyKeyboardMarkup([settings.casual_commands],
                                                                     one_time_keyboard=True,
                                                                     input_field_placeholder=settings.replies[
                                                                         'boringMessage'],
                                                                     resize_keyboard=True))
    return ConversationHandler.END


async def help_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(settings.replies['help'])


async def show_inventory_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(f'{str(Kitchen.get_instance().inventory)}')


async def show_base_inventory_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(f'{str(Kitchen.get_instance().base_inventory)}')


async def show_grocery_list_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    await update.message.reply_text(f'{str(Kitchen.get_instance().grocery_list)}')


async def cancel_init_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    user = update.message.from_user
    Kitchen.get_instance().delete_instance()
    await update.message.reply_text(settings.replies['cancel'])
    return ConversationHandler.END


async def silent_cancel_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> int:
    user = update.message.from_user
    await update.message.reply_text(settings.replies['cancel'])
    return ConversationHandler.END


# commands - create a handler for each command
help_handler = CommandHandler("help", help_command)
base_inventory_handler = CommandHandler("setBaseInventory", set_base_inventory)
show_base_inventory_handler = CommandHandler("showBaseInventory", show_base_inventory_command)
inventory_handler = CommandHandler("setInventory", set_inventory)
show_inventory_handler = CommandHandler("showInventory", show_inventory_command)
show_grocery_list_handler = CommandHandler("showGroceryList", show_grocery_list_command)
delete_kitchen_handler = CommandHandler("deleteKitchen", delete_kitchen_command)